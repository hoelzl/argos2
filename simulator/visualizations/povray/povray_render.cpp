/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * @file <simulator/visualisations/text/text_render.cpp>
 *
 * @brief This file contains the implementation of a simple text renderer.
 *
 * This file contains the implementation of the povray renderer.
 *
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 */

#include <iomanip>

#include <iostream>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>

#include "povray_render.h"
#include <argos2/common/utility/math/ray.h>
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/string_utilities.h>
#include "simulator.h"
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/space/entities/entity.h>
#include <argos2/simulator/visitors/povray_render_visitor_draw.cpp>

#include <sys/types.h>
#include<cstring>
#include<libgen.h>
#include<stdlib.h>

/****************************************/
/****************************************/

namespace argos {

   /****************************************/
   /****************************************/

   void CPovrayRender::Init(TConfigurationNode& t_tree)
   {
      try {
         /* Call parent init */
         CRender::Init(t_tree);

         /* Create the visitor */
         m_pcVisitor = new CPovrayRenderVisitorDraw(m_cOutputFileStream);

         /* Get the output folder */
         GetNodeAttribute(t_tree, "output_folder", m_StrOutputFolder);

         /* Check whether the output folder exists */
         struct stat st;
         if(stat(m_StrOutputFolder.c_str(),&st) != 0) {
            THROW_ARGOSEXCEPTION("Could not find the output folder \"" <<
                                 m_StrOutputFolder << "\" required for the POVRay renderer");
         }

         // Create directory to write the POVRay sources to
         m_StrSourceFolderName  = m_StrOutputFolder + "/pov/";
         stat(m_StrSourceFolderName.c_str(), &st);

         // If the sources directory does not exist - create it
         if(stat(m_StrSourceFolderName.c_str(),&st) != 0) {
            LOG << "[INFO] Creating sources directory: "<<  m_StrSourceFolderName << std::endl ;
            // Create the new for for the sources
            SInt8 nStatus = mkdir( m_StrSourceFolderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
            if(nStatus != 0) {
               THROW_ARGOSEXCEPTION("Could not create the output folder \"" <<
                                    m_StrSourceFolderName << "\" required to save the POVRay renderer");
            }
         }

         // Now copy the helper files and folders into the output folder
         std::string strCopyCommand = "";
         std::string strTobeCopied = "";

         // Include
         strTobeCopied = "$ARGOSINSTALLDIR/simulator/visualizations/povray/include";
         strCopyCommand = "cp -r " + strTobeCopied + " " +  m_StrOutputFolder;
         system(strCopyCommand.c_str());

         // Ini
         strTobeCopied = "$ARGOSINSTALLDIR/simulator/visualizations/povray/ini";
         strCopyCommand = "cp -r " + strTobeCopied + " " +  m_StrOutputFolder;
         system(strCopyCommand.c_str());

         // Scripts
         strTobeCopied = "$ARGOSINSTALLDIR/simulator/visualizations/povray/scripts";
         strCopyCommand = "cp -r " + strTobeCopied + " " +  m_StrOutputFolder;
         system(strCopyCommand.c_str());

         // Textures
         strTobeCopied = "$ARGOSINSTALLDIR/simulator/visualizations/povray/textures";
         strCopyCommand = "cp -r " + strTobeCopied + " " +  m_StrOutputFolder;
         system(strCopyCommand.c_str());

         // File: render_single_frame_on_pc
         strTobeCopied = "$ARGOSINSTALLDIR/simulator/visualizations/povray/render_single_frame_on_pc.sh";
         strCopyCommand = "cp " + strTobeCopied + " " +  m_StrOutputFolder;
         system(strCopyCommand.c_str());

         // File: render_all_frames_on_pc
         strTobeCopied = "$ARGOSINSTALLDIR/simulator/visualizations/povray/render_all_frames_on_pc.sh";
         strCopyCommand = "cp " + strTobeCopied + " " +  m_StrOutputFolder;
         system(strCopyCommand.c_str());

         // File: render_all_frames_on_cluster
         strTobeCopied = "$ARGOSINSTALLDIR/simulator/visualizations/povray/render_all_frames_on_cluster.sh";
         strCopyCommand = "cp " + strTobeCopied + " " +  m_StrOutputFolder;
         system(strCopyCommand.c_str());

         /* Get environment node */
         if (NodeExists(t_tree,"environment") ) {
            InitEnvironment(GetNode(t_tree, "environment"));

            // Read in special box and cylinder definitions
            InitBoxesAndCylinders(GetNode(t_tree, "environment"));

            // See whether the user wants to ignore the rendering of certain entities
            InitEntityToIgnore(GetNode(t_tree, "environment"));

            // See whether the user wants add more lights
            InitLightSources(GetNode(t_tree, "environment"));

         }
         else {
            // Setting standard environment

            // Set standard floor
            m_StrFloorOutput = "plane { <0, 0, 1>, 0 texture { Aluminum } }";

            // Set standard sky
            std::string strSkyDefault = "$ARGOSINSTALLDIR/simulator/visualizations/povray/textures/sky/default.pov";
            m_StrSkyOutput = FileToString(strSkyDefault);
         }



         /* Check if at least one scene node exists*/
         if (NodeExists(t_tree,"scene") ) {
            /* Parse the entire tree for all scene nodes*/
            InitScene(t_tree);
         }
         else {
            // Set default scene
            m_StrCameraOutput = "camera { \n perspective \n location <0,0,3> \n look_at <0,0,0> \n sky<0,0,5> \n right  <0,1.33,0> }";
            LOGERR << "[WARNING] No \"scene\" node found for POVRay renderer. Using standard scene." << std::endl;
         }

         /* Set the standard light source properties*/
         m_StrLightOutput = "light_source{ <0,0,10> color rgb <1,1,1> parallel point_at<0, 0, 0>   shadowless }";
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize the POVRay renderer", ex);
      }
   }


   /****************************************/
   /****************************************/

   void CPovrayRender::Execute() {

      // Initial cycle

      // Open stream to a file
      std::ostringstream ossFileName;
      ossFileName << m_StrSourceFolderName << std::setfill('0') << std::setw(5) << ToString(m_cSpace.GetSimulationClock()) << ".pov";

      // Write out all information into the dile
      WriteOneFrame(ossFileName.str());


      /* Main cycle */

      while(!m_cSimulator.IsExperimentFinished()) {

         m_cSimulator.UpdateSpace();

         // Open stream to a file
         std::ostringstream ossFileName;
         ossFileName << m_StrSourceFolderName << std::setfill('0') << std::setw(5) << ToString(m_cSpace.GetSimulationClock()) << ".pov";

         // Write out all information into the dile
         WriteOneFrame(ossFileName.str());

      }
   }

   /****************************************/
   /****************************************/

   void CPovrayRender::WriteOneFrame(const std::string& str_path_to_file)
   {

      LOG << "[INFO] " << "Writing frame: " << str_path_to_file << std::endl;

      // See whether everything went fine with the file
      m_cOutputFileStream.open(str_path_to_file.c_str(), std::ios::out);
      if ( m_cOutputFileStream.bad( ) ) {
         THROW_ARGOSEXCEPTION("Error creating file \"" << str_path_to_file << "\" for POVRay rendering.");
      }

      // Write out the environment related stuff
      WriteEnvironment();

      // Write camera information
      WriteCamera();

      // Ask all entities to "draw" themselves into the file
      WriteEntities();

      // Close the stream to the file
      m_cOutputFileStream.close();
   }

   /****************************************/
   /****************************************/

   void CPovrayRender::WriteCamera( )
   {

      // See if the user has defined a scene for this frame
      TSceneStepCameraMap::iterator it = m_mapSceneStepCamera.find(m_cSpace.GetSimulationClock());

      // If yes, memorize it until a new definition is found
      if(it != m_mapSceneStepCamera.end()) {
         m_StrCameraOutput = (*it).second;
      }

      m_cOutputFileStream

         // The latest camera defined
         << m_StrCameraOutput << "\n\n"

         << std::endl    << std::flush;
   }

   /****************************************/
   /****************************************/

   void CPovrayRender::WriteEnvironment( )
   {

      m_cOutputFileStream
         // Include files
         << "#include \"colors.inc\"\n "
         "#include \"robots/led.inc\"\n"
         "#include \"robots/eyebot.pov\"\n"
         "#include \"robots/footbot.pov\"\n"
         "#include \"robots/handbot.pov\"\n"
         "#include \"stones.inc\"\n"
         "#include \"stones1.inc\"\n"
         "#include \"stones2.inc\"\n"
         "#include \"textures.inc\"\n"
         "#include \"finish.inc\"\n"
         "#include \"glass.inc\"\n"
         "#include \"glass_old.inc\"\n"
         "#include \"golds.inc\"\n"
         "#include \"rad_def.inc\"\n"
         "#include \"skies.inc\"\n"
         "#include \"stdinc.inc\"\n"
         "#include \"metals.inc\"\n"
         "#include \"shapesq.inc\"\n"
         "#include \"shapes.inc\"\n"
         "#include \"woods.inc\"\n"  << "\n\n"

         // Global setting
         << "global_settings { max_trace_level 5 } " << "\n\n"

         // The sky
         << m_StrSkyOutput << "\n\n"

         // The floor
         << m_StrFloorOutput << "\n\n"

         // The light to make things visible
         << "#if (RADIOSITY = 0) "
         << m_StrLightOutput
         << " #end\n\n"

         << std::endl    << std::flush;

   }

   /****************************************/
   /****************************************/

   void CPovrayRender::WriteEntities( )
   {
      /* call visitor to draw the entities */
      TEntityMap& entitiesMap = m_cSpace.GetAllEntities();
      for(TEntityMap::iterator it_entities = entitiesMap.begin();it_entities != entitiesMap.end();++it_entities) {
         (it_entities->second)->Accept(*m_pcVisitor);
      }

      /* call visitor to draw the extra light sources */
      m_pcVisitor->DrawLightSources();

   }

   /****************************************/
   /****************************************/

   void CPovrayRender::Destroy( )
   {
      if(m_cOutputFileStream.is_open())
         m_cOutputFileStream.close( );
      delete m_pcVisitor;
   }


   /****************************************/
   /****************************************/

   void CPovrayRender::InitLightSources(TConfigurationNode& t_tree) {
      /* Loop through all nodes */
      TConfigurationNodeIterator itScenes;

      for(itScenes = itScenes.begin(&t_tree); itScenes != itScenes.end(); ++itScenes) {

         if(itScenes->Value() == "light_source") {
            std::string strLightSourcePosition = "";
            std::string strLightSourceColor = "White";
            Real fLightSourceFadeDistance = 1;
            Real fLightSourceFadePower = 1;
            bool bLightSourceShadowless = true;
            std::string strLightSourceShadowlessString = "shadowless";

            GetNodeAttribute(*itScenes, "position", strLightSourcePosition);
            GetNodeAttributeOrDefault(*itScenes, "color", strLightSourceColor, strLightSourceColor);
            GetNodeAttributeOrDefault(*itScenes, "fade_distance", fLightSourceFadeDistance, fLightSourceFadeDistance);
            GetNodeAttributeOrDefault(*itScenes, "fade_power", fLightSourceFadePower, fLightSourceFadePower);
            GetNodeAttributeOrDefault(*itScenes, "shadowless", bLightSourceShadowless, bLightSourceShadowless);

            if(!bLightSourceShadowless) strLightSourceShadowlessString = "";

            m_pcVisitor->SetLightSource(strLightSourcePosition, strLightSourceColor, fLightSourceFadeDistance, fLightSourceFadePower, strLightSourceShadowlessString);
         }

      }
   }

   /****************************************/
   /****************************************/

   void CPovrayRender::InitEntityToIgnore(TConfigurationNode& t_tree) {
      /* Loop through all nodes */
      TConfigurationNodeIterator itScenes;

      for(itScenes = itScenes.begin(&t_tree); itScenes != itScenes.end(); ++itScenes) {

         if(itScenes->Value() == "ignore") {
            std::string strEntityID = "";
            GetNodeAttribute(*itScenes, "id", strEntityID);
            m_pcVisitor->SetEntityToIgnore(strEntityID);
         }

      }
   }

   /****************************************/
   /****************************************/

   void CPovrayRender::InitBoxesAndCylinders( TConfigurationNode& t_tree_environment )
   {
      /* Loop through all nodes */
      TConfigurationNodeIterator itScenes;
      for(itScenes = itScenes.begin(&t_tree_environment); itScenes != itScenes.end(); ++itScenes) {

         // If the current node is a redefinition of a box or cylinder
         if((itScenes->Value() == "box") || (itScenes->Value() == "cylinder")) {

            std::string strBoxOrCylinderID = "";
            std::string strBoxOrCylinderType = "";
            GetNodeAttributeOrDefault(*itScenes, "type", strBoxOrCylinderType, strBoxOrCylinderType);
            GetNodeAttribute(*itScenes, "id", strBoxOrCylinderID);

            // Check if the a valid type was asked
            if((strBoxOrCylinderType != "texture") && (strBoxOrCylinderType != "color")) {

               if(itScenes->Value() == "box") {
                  THROW_ARGOSEXCEPTION("No valid value [texture | color] was found in  attribute 'type' in node 'box'. ");
               }
               if(itScenes->Value() == "cylinder") {
                  THROW_ARGOSEXCEPTION("No valid value [texture | color] was found in  attribute 'type' in node 'cylinder'. ");
               }
            }

            // COLOR
            if(strBoxOrCylinderType == "color") {
               if (NodeExists(*itScenes,"color") ) {
                  std::string strPovrayColor = GetStandardPovrayOrPovrayRGBColor(*itScenes, "color");
                  strPovrayColor = "pigment {color " + strPovrayColor + "}";
                  m_pcVisitor->SetBoxOrCylinderColorRedefinition(strBoxOrCylinderID,strPovrayColor);
               }
               else {

                  if(itScenes->Value() == "box") {
                     THROW_ARGOSEXCEPTION("No subnode 'color' was found in node 'box'.");
                  }
                  if(itScenes->Value() == "cylinder") {
                     THROW_ARGOSEXCEPTION("No subnode 'color' was found in node 'cylinder'.");
                  }
               }
            }

            // TEXTURE
            if(strBoxOrCylinderType == "texture") {
               if (NodeExists(*itScenes,"standard") ) {

                  TConfigurationNode& t_tree_standard_texture = GetNode(*itScenes, "standard");

                  // The following two attribute must be given
                  std::string strStandardTexturePattern = "";
                  GetNodeAttributeOrDefault(t_tree_standard_texture, "pattern", strStandardTexturePattern, strStandardTexturePattern);

                  // Check if the attribute exists
                  if(strStandardTexturePattern == "") {
                     THROW_ARGOSEXCEPTION("The node 'standard' requires the attribute 'pattern'.");
                  }
                  else {
                     strStandardTexturePattern = "$ARGOSINSTALLDIR/simulator/visualizations/povray/textures/" + strStandardTexturePattern;
                     std::string strTextureOutput = FileToString(strStandardTexturePattern);
                     strStandardTexturePattern = "texture { " + strTextureOutput + " }";
                     m_pcVisitor->SetBoxOrCylinderTextureRedefinition(strBoxOrCylinderID,strStandardTexturePattern);
                  }
               }
               else if(NodeExists(*itScenes,"custom") ) {

                  TConfigurationNode& t_tree_custom_texture = GetNode(*itScenes, "custom");

                  // The following two attribute must be given
                  std::string strCustomTexturePattern = "";
                  GetNodeAttributeOrDefault(t_tree_custom_texture, "pattern", strCustomTexturePattern, strCustomTexturePattern);

                  // Check if the attribute exists
                  if(strCustomTexturePattern == "") {
                     THROW_ARGOSEXCEPTION("The node 'custom' requires the attribute 'pattern'.");
                  }
                  else {

                     strCustomTexturePattern =  ExpandARGoSInstallDir(strCustomTexturePattern) ;

                     std::ifstream cInfile;

                     cInfile.open(strCustomTexturePattern.c_str());
                     if (cInfile.is_open()) {

                        CopyTexture(strCustomTexturePattern);

                        Real nScale = 1;
                        GetNodeAttributeOrDefault(t_tree_custom_texture, "scale", nScale, nScale);

                        bool bRepeatTexture = true;
                        GetNodeAttributeOrDefault(t_tree_custom_texture, "repeat", bRepeatTexture, bRepeatTexture);
                        std::string strRepeatText = "";
                        if(!bRepeatTexture) strRepeatText = "once";

                        strCustomTexturePattern = GetBasename(strCustomTexturePattern);

                        strCustomTexturePattern =  "texture {  pigment { image_map { png \"textures/"  + strCustomTexturePattern + "\" " + strRepeatText +" } scale " + ToString(nScale) + "} }";
                        m_pcVisitor->SetBoxOrCylinderTextureRedefinition(strBoxOrCylinderID,strCustomTexturePattern);

                        cInfile.close();
                     }
                     else {
                        THROW_ARGOSEXCEPTION("Could not find the file \"" << strCustomTexturePattern << "\". Please give a complete path.");
                     }
                  }
               }
               else {

                  if(itScenes->Value() == "box") {
                     THROW_ARGOSEXCEPTION("No subnode 'standard' or 'custom' was found in node 'box type='texture''.");
                  }
                  if(itScenes->Value() == "cylinder") {
                     THROW_ARGOSEXCEPTION("No subnode 'standard' or 'custom' was found in node 'cylinder type='texture''.");
                  }
               }
            }

         }

      }
   }

   /****************************************/
   /****************************************/

   std::string CPovrayRender::GetBasename(std::string& str_filename){

      std::string strResult = "";

      // Strip of the path name and just get the filename
      char *filename = strdup(str_filename.c_str());
      strResult = basename(filename);
      free(filename);

      return strResult;
   }

   /****************************************/
   /****************************************/

   void CPovrayRender::CopyTexture(std::string& str_texture){

      std::ifstream cInfile;

      cInfile.open(str_texture.c_str());

      if (cInfile.is_open()) {
         std::string strCopyCommand = "cp " + str_texture + " " +  m_StrOutputFolder + "/textures";
         system(strCopyCommand.c_str());
      }
      else {
         THROW_ARGOSEXCEPTION("Could not copy file \"" << str_texture << "\". File does not exist.");
      }
   }


   /****************************************/
   /****************************************/

   void CPovrayRender::InitScene(TConfigurationNode& t_tree) {

      SInt16 unStep = -1;
      bool bFoundScene0 = false;


      // Init maps
      m_mapSceneStepCamera[-1] = "";
      m_mapCameraTypeDefinitions["normal"] =  "perspective \n sky <0,0,1> \n right  <0,-1.33,0> \n ";


      /* Loop through all nodes */
      TConfigurationNodeIterator itScenes;
      for(itScenes = itScenes.begin(&t_tree); itScenes != itScenes.end(); ++itScenes) {

         // If the current node is a scene
         if(itScenes->Value() == "scene") {

            // Get the step attribute
            GetNodeAttribute(*itScenes, "step", unStep);

            // Get the camera node
            TConfigurationNode t_camera = GetNode(*itScenes, "camera");

            // Get the camera attributes type, position, look_at
            std::string strCameraType, strCameraPositon, strCameraLookAt;
            Real fFocalLength = 20.0f; // default focal length in mm
            GetNodeAttribute(t_camera, "type", strCameraType);
            GetNodeAttribute(t_camera, "position", strCameraPositon);
            GetNodeAttribute(t_camera, "look_at", strCameraLookAt);
            GetNodeAttributeOrDefault(t_camera, "focal_length", fFocalLength, fFocalLength);
            CRadians cFieldOfView = ATan2(36.0f * 0.5f, fFocalLength) * 2.0f; // 35mm film by default => 36mm frame width


            // Check if the camera type is supported - and if yes, get the actual definition
            TSceneCameraTypeDefinitions::iterator it = m_mapCameraTypeDefinitions.find(strCameraType);
            if(it == m_mapCameraTypeDefinitions.end()) {
               THROW_ARGOSEXCEPTION("Unsupported camera type \"" << strCameraType << "\".");
            }
            else {
               strCameraType = (*it).second;
            }

            // Check if there is an initial scene setting
            if(unStep == 0) bFoundScene0 = true;

            // If everything went fine, put together the camera string for povray
            std::string strCameraOutput = "camera { \n " + strCameraType + " \n location <" + strCameraPositon + "> \n look_at <" + strCameraLookAt + "> \n angle " + ToString(ToDegrees(cFieldOfView).GetValue()) + "\n}";

            // Fill the map
            m_mapSceneStepCamera[unStep] = strCameraOutput;
         }
      }

      if(!bFoundScene0) {
    	   LOGERR << "[WARNING] Did not find initial scene setting (step=0) for POVRay." << std::endl;
      }


   }


   /****************************************/
   /****************************************/

   void CPovrayRender::InitEnvironment(TConfigurationNode& t_tree) {

      /* Get environment type attribute */
      std::string strEnvironmentType = "";
      GetNodeAttributeOrDefault(t_tree, "type", strEnvironmentType, strEnvironmentType);

      if(strEnvironmentType == "standard") {

      	 // Set default floor
      	 m_StrFloorOutput = "plane { <0, 0, 1>, 0 pigment { color White } }";

         // Set default sky
      	 std::string strSkyDefault = "$ARGOSINSTALLDIR/simulator/visualizations/povray/textures/sky/default.pov";
      	 m_StrSkyOutput = FileToString(strSkyDefault);

      }
      else {
         THROW_ARGOSEXCEPTION("No valid value [standard] was found in attribute 'type' in node 'environment': " << strEnvironmentType );
      }

      // Check for overriding declarations
      if (NodeExists(t_tree,"floor") ) {
    	   LOG  << "[INFO] Overriding floor" << std::endl;
         InitFloor(GetNode(t_tree, "floor"));
      }
      if (NodeExists(t_tree,"sky") ) {
    	   LOG  << "[INFO] Overriding sky" << std::endl;
         InitSky(GetNode(t_tree, "sky"));
      }
   }
   /****************************************/
   /****************************************/

   void CPovrayRender::InitSky(TConfigurationNode& t_tree) {

      /* Get sky type attribute */
      std::string strSkyType = "";
      GetNodeAttributeOrDefault(t_tree, "type", strSkyType, strSkyType);

      // Check if the a valid floor type was asked
      if((strSkyType != "plain") && (strSkyType != "texture")) {
         THROW_ARGOSEXCEPTION("No valid value [plain | standard] was found in  attribute 'type' in node 'sky'. ");
      }
      else {
         // PLAIN
         if(strSkyType == "plain") {

            if (NodeExists(t_tree,"color") ) {

               std::string strPovrayColor = GetStandardPovrayOrPovrayRGBColor(t_tree, "color");
               m_StrSkyOutput = "background { color " + strPovrayColor + " }";

            }
            else {
               THROW_ARGOSEXCEPTION("No subnode 'color' was found in node 'sky type='plain''.");
            }
         }


         // TEXTURE
         if(strSkyType == "texture") {

            if (NodeExists(t_tree,"standard") ) {

               TConfigurationNode& t_tree_sky_standard_texture = GetNode(t_tree, "standard");

               // The following two attribute must be given
               std::string strSkyStandardTexturePattern = "";
               GetNodeAttributeOrDefault(t_tree_sky_standard_texture, "pattern", strSkyStandardTexturePattern, strSkyStandardTexturePattern);

               // Check if the attribute exists
               if(strSkyStandardTexturePattern == "") {
                  THROW_ARGOSEXCEPTION("The node 'standard' requires the attribute 'pattern'.");
               }
               else {
                  std::string strSkyPattern = "$ARGOSINSTALLDIR/simulator/visualizations/povray/textures/sky/" + strSkyStandardTexturePattern;
                  m_StrSkyOutput = FileToString(strSkyPattern);
               }
            }
            else {
               THROW_ARGOSEXCEPTION("No subnode 'standard' was found in node 'sky type='texture''.");
            }
         }

      }

   }
   /****************************************/
   /****************************************/

   void CPovrayRender::InitFloor(TConfigurationNode& t_tree) {
      /* Get floor type attribute */
      std::string strFloorType = "";
      GetNodeAttributeOrDefault(t_tree, "type", strFloorType, strFloorType);


      // Check if the a valid floor type was asked
      if((strFloorType != "plain") && (strFloorType != "texture") && (strFloorType != "checker")) {
         THROW_ARGOSEXCEPTION("No valid value [plain | texture | checker] was found in  attribute 'type' in node 'floor'. ");
      }
      else {

         // PLAIN
         if(strFloorType == "plain") {

            if (NodeExists(t_tree,"color") ) {

               std::string strPovrayColor = GetStandardPovrayOrPovrayRGBColor(t_tree, "color");
               m_StrFloorOutput = "plane { <0, 0, 1>, 0 pigment { color " + strPovrayColor + " } }";
            }
            else {
               THROW_ARGOSEXCEPTION("No subnode 'color' was found in node 'floor'.");
            }
         }



         // TEXTURE
         if(strFloorType == "texture") {
            if (NodeExists(t_tree,"standard") ) {

               TConfigurationNode& t_tree_floor_standard_texture = GetNode(t_tree, "standard");

               // The following two attribute must be given
               std::string strFloorStandardTexturePattern = "";
               GetNodeAttributeOrDefault(t_tree_floor_standard_texture, "pattern", strFloorStandardTexturePattern, strFloorStandardTexturePattern);

               // Check if the attribute exists
               if(strFloorStandardTexturePattern == "") {
                  THROW_ARGOSEXCEPTION("The node 'standard' requires the attribute 'pattern'.");
               }
               else {
                  m_StrFloorOutput = "plane { <0, 0, 1>, 0 texture { " + strFloorStandardTexturePattern + " } }";
               }
            }
            else if(NodeExists(t_tree,"custom") ) {

               TConfigurationNode& t_tree_floor_custom_texture = GetNode(t_tree, "custom");

               // The following two attribute must be given
               std::string strFloorCustomTexturePattern = "";
               GetNodeAttributeOrDefault(t_tree_floor_custom_texture, "pattern", strFloorCustomTexturePattern, strFloorCustomTexturePattern);

               // Check if the attribute exists
               if(strFloorCustomTexturePattern == "") {
                  THROW_ARGOSEXCEPTION("The node 'custom' requires the attribute 'pattern'.");
               }
               else {

                  strFloorCustomTexturePattern =  ExpandARGoSInstallDir(strFloorCustomTexturePattern) ;

                  std::ifstream cInfile;

                  cInfile.open(strFloorCustomTexturePattern.c_str());
                  if (cInfile.is_open()) {

                     CopyTexture(strFloorCustomTexturePattern);

                     Real nScale = 1;
                     GetNodeAttributeOrDefault(t_tree_floor_custom_texture, "scale", nScale, nScale);

                     bool bRepeatTexture = true;
                     GetNodeAttributeOrDefault(t_tree_floor_custom_texture, "repeat", bRepeatTexture, bRepeatTexture);
                     std::string strRepeatText = "";
                     if(!bRepeatTexture) strRepeatText = "once";

                     strFloorCustomTexturePattern = GetBasename(strFloorCustomTexturePattern);

                     m_StrFloorOutput =  "plane { <0, 0, 1>, 0  pigment { image_map { png \"textures/" + strFloorCustomTexturePattern + "\" " + strRepeatText +" } scale " + ToString(nScale) + "} }";

                     cInfile.close();
                  }
                  else {
                     THROW_ARGOSEXCEPTION("Could not find the file \"" << strFloorCustomTexturePattern << "\". Please give a complete path.");
                  }
               }
            }
            else {
               THROW_ARGOSEXCEPTION("No subnode 'standard' or 'custom' was found in node 'floor type='texture''.");
            }
         }




         // CHECKER
         if(strFloorType == "checker") {
            if (NodeExists(t_tree,"color1") ) {
               if (NodeExists(t_tree,"color2") ) {

                  std::string strPovrayColor1 = GetStandardPovrayOrPovrayRGBColor(t_tree, "color1");
                  std::string strPovrayColor2 = GetStandardPovrayOrPovrayRGBColor(t_tree, "color2");

                  m_StrFloorOutput = "plane { <0, 0, 1>, 0 pigment { checker " + strPovrayColor1 + " " + strPovrayColor2 + " } }";
               }
               else {
                  THROW_ARGOSEXCEPTION("No subnode 'color2' was found in node 'floor'.");
               }
            }
            else {
               THROW_ARGOSEXCEPTION("No subnode 'color1' was found in node 'floor'.");
            }
         }


      }

   }


   /****************************************/
   /****************************************/


   std::string CPovrayRender::GetStandardPovrayOrPovrayRGBColor(TConfigurationNode& t_tree, const std::string& str_node_name) {
      std::string strResult = "";

      if (NodeExists(t_tree, str_node_name) ) {


         TConfigurationNode& t_color_node = GetNode(t_tree, str_node_name);

         // One of the following two attributes must be given
         std::string strFloorColorPovray = "";
         GetNodeAttributeOrDefault(t_color_node, "povray", strFloorColorPovray, strFloorColorPovray);

         std::string strFloorColorRGB = "";
         GetNodeAttributeOrDefault(t_color_node, "rgb", strFloorColorRGB, strFloorColorRGB);

         // Check if at least one of the two above attribute was given
         if((strFloorColorPovray == "") && (strFloorColorRGB == "") ) {
            LOG << strFloorColorPovray << strFloorColorRGB <<  std::endl;
            THROW_ARGOSEXCEPTION("The node '" + str_node_name + "' requires one of the following two attributes [povray | rgb]");
         }
         else if((strFloorColorPovray != "") && (strFloorColorRGB != "") ) {
            THROW_ARGOSEXCEPTION("The node '" + str_node_name + "' requires ONLY one of the following two attributes [povray | rgb]");
         }
         else {
            // User has input a predefined Povray color
            if(strFloorColorPovray != "") {

               // Make sure the first letter is a capital letter
               strFloorColorPovray[0] = toupper (strFloorColorPovray[0]);
               strResult = strFloorColorPovray;
            }
            // User has input a RGB color
            else {

               // Access each of the RGB value and calculate a percentage value (required by Povray)
               std::vector<std::string> vecRGB;
               Tokenize(strFloorColorRGB, vecRGB, ",");
               std::string strRGBPercentage[3];
               for (UInt8 i=0; i < vecRGB.size(); i++) {
                  UInt8 nRGBValue = atoi (ToString(vecRGB[i]).c_str());
                  Real fRGBValuePercentage = (Real) nRGBValue / 255;
                  strRGBPercentage[i] = ToString(fRGBValuePercentage);
               }

               strResult = "rgb<" + strRGBPercentage[0] + "," + strRGBPercentage[1]  + "," + strRGBPercentage[2] + ">";

            }

         }


      }
      else {
         THROW_ARGOSEXCEPTION("No subnode '" + str_node_name + "' was not found.");
      }

      return strResult;
   }


   /****************************************/
   /****************************************/

   std::string CPovrayRender::FileToString(std::string& str_path_to_file) {
      std::string strResult = "";
      str_path_to_file =  ExpandARGoSInstallDir(str_path_to_file) ;

      std::ifstream cInfile;

      cInfile.open(str_path_to_file.c_str());
      if (cInfile.is_open()) {

         std::string strLine = "";
         while (getline(cInfile, strLine))
         {
            strResult = strResult + strLine + "\n";
         }

         cInfile.close();
      }
      else {
         THROW_ARGOSEXCEPTION("Error opening the file \"" << str_path_to_file << "\" requested. Please give a complete path.");
      }
      return strResult;
   }

   /****************************************/
   /****************************************/

   REGISTER_RENDER(CPovrayRender,
                   "povray_render",
                   "A high-quality off-line graphical renderer based on POV-Ray",
                   "Nithin Mathews [nmathews@ulb.ac.be]",
                   "The POV-Ray renderer is a graphical renderer based on POV-Ray.\n"
                   "It allows the user to create high quality videos of experiments that have \n"
                   "been tested using the 'qtopengl_render' visualization. Remember -- this is an\n"
                   "off-line renderer! This means that this renderer merely outputs a folder \n"
                   "containing the following subfolders and files:\n"
                   "\t (1)\tinclude \t \n"
                   "\t (2)\tini \t \n"
                   "\t (3)\tpov \t \n"
                   "\t (4)\tscripts \t \n"
                   "\t (5)\ttextures \t \n"
                   "\t (6)\trender_all_frames_on_cluster.sh \t \n"
                   "\t (7)\trender_all_frames_on_pc.sh \t \n"
                   "\t (8)\trender_single_frame_on_pc.sh\t \n\n"
                   "TODO: Describe (1) - (8).\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <scene step=\"0\">\n"
                   "       <camera type=\"normal\" position=\"1,1,1\" look_at=\"0,0,0\"/>\n"
                   "      </scene>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "Be aware that only already existing folders are valid arguments for the\n"
                   "attribute 'output_folder'. The content of the node 'scene' can be copied\n"
                   "from the 'qtopengl_renderer'. To generate interesting videos, you may\n"
                   "want to consider having multipe 'scene' nodes with varying 'step' attribute\n"
                   "values and differing 'camera' options.\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "  <!-- A standard environment with new colors for 'floor' and 'sky'-->\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <environment type=\"standard\"> \n"
                   "        <floor type=\"plain\">\n"
                   "          <color povray=\"Red\" | rgb=\"250,0,0\"/>\n"
                   "        </floor>\n"
                   "        <sky type=\"plain\">\n"
                   "          <color rgb=\"250,0,0\"/>\n"
                   "        </sky>\n"
                   "      </environment>\n"
                   "      <scene step=\"0\">\n"
                   "       <camera type=\"normal\" position=\"1,1,1\" look_at=\"0,0,0\"/>\n"
                   "      </scene>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "  <!-- A standard environment with textures for 'floor' and 'sky'-->\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <environment type=\"standard\"> \n"
                   "        <floor type=\"plain\">\n"
                   "          <color povray=\"Red\"/>\n"
                   "        </floor>\n"
                   "        <sky type=\"texture\">\n"
                   "          <standard pattern=\"blue_sky.pov\"/>\n"
                   "        </sky>\n"
                   "      </environment>\n"
                   "      <scene step=\"0\">\n"
                   "       <camera type=\"normal\" position=\"1,1,1\" look_at=\"0,0,0\"/>\n"
                   "      </scene>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "  <!-- A standard environment with custom texture for 'floor''-->\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <environment type=\"standard\"> \n"
                   "        <floor type=\"texture\">\n"
                   "          <custom pattern=\"/home/user/Desktop/nice_tile.png\" \n"
                   "                                           repeat=\"true\" scale=\"5\" />\n"
                   "        </floor>\n"
                   "        <sky type=\"texture\">\n"
                   "          <standard pattern=\"planet_sun.pov\"/>\n"
                   "        </sky>\n"
                   "      </environment>\n"
                   "      <scene step=\"0\">\n"
                   "       <camera type=\"normal\" position=\"1,1,1\" look_at=\"0,0,0\"/>\n"
                   "      </scene>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "  <!-- A standard environment with a checker board on the 'floor''-->\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <environment type=\"standard\"> \n"
                   "        <floor type=\"checker\">\n"
                   "          <color1 povray=\"Red\"/>\n"
                   "          <color2 povray=\"Green\"/>\n"
                   "        </floor>\n"
                   "        <sky type=\"texture\">\n"
                   "          <color rgb=\"250,0,0\"/>\n"
                   "          <standard pattern=\"blue_sky_clouds.pov\"/>\n"
                   "        </sky>\n"
                   "      </environment>\n"
                   "      <scene step=\"0\">\n"
                   "       <camera type=\"normal\" position=\"1,1,1\" look_at=\"0,0,0\"/>\n"
                   "      </scene>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "  <!-- A standard environment with a redefinition of a 'box''-->\n"
                   "  <!-- (the same can be done for 'cylinder' entities)'-->\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <environment type=\"standard\"> \n"
                   "        <!-- Using a color -->\n"
                   "        <box id=\"b0\" type=\"color\">\n"
                   "          <color povray=\"Blue\"/>\n"
                   "        </box>\n"
                   "        <-- Or using a texture -->\n"
                   "        <box id=\"b0\" type=\"texture\">\n"
                   "          <standard pattern=\"Jade\"/>\n"
                   "          <!-- <custom pattern=\"/home/user/Desktop/nice_tile.png\" \n"
                   "                                        repeat=\"true\" scale=\"5\" />-->\n"
                   "        </box>\n"
                   "      </environment>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "  <!-- A standard environment does not render certain entities-->\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <environment type=\"standard\"> \n"
                   "        <!--The entity ids can be exact or a regexp as shown here-->\n"
                   "        <ignore id=\"light_[[:digit:]]*\"/>\n"
                   "      </environment>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "  <!-- A standard environment with a white, shadowless light source-->\n"
                   "  <visualization>\n"
                   "    <povray_render id=\"povray\" output_folder=\"/home/user/experiment1\">\n"
                   "      <environment type=\"standard\"> \n"
                   "        <light_source position=\"0,1,1\"/>\n"
                   "        <!--Another light source with further options-->\n"
                   "        <light_source position=\"0,0,2\" color=\"Green\" fade_distance=\"5\"\n"
                   "                                    fade_power=\"1\" shadowless=\"false\"/>\n"
                   "      </environment>\n"
                   "    </povray_render>\n"
                   "  </visualization>\n\n"
                   "A color can be input using standard the attribute 'povray' for standard  \n"
                   "POV-Ray colors or using the attribute 'rgb' for any RGB color (ex. rgb=.\n"
                   "\"50,100,20\")."
                   "Further textures for 'sky' can be found in  \n"
                   "$ARGOSINSTALLDIR/simulator/visualizations/povray/textures/sky/\n",
                   "Under development"




      );
}

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
 * @file <simulator/visualisations/text/text_render.h>
 *
 * @brief This file contains the definition of a simple text renderer.
 *
 * This file contains the definition of povray renderer that
 * writes out a POVRay source file per simulation step.
 *

 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 */

#ifndef POVRAY_RENDER_H
#define POVRAY_RENDER_H

/* To avoid dependency problems when including */
namespace argos {
   class CPovrayRender;
   class CSpace;
   class CSceneGraph;
   class CPovrayRenderVisitorDraw;
};

#include <argos2/simulator/visualizations/render.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <map>
#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace argos {

	typedef std::map<SInt32, std::string> TSceneStepCameraMap;
	typedef std::map<std::string, std::string> TSceneCameraTypeDefinitions;


   class CPovrayRender : public CRender {

   protected:

      /** File stream the renderer should write to. */
      std::ofstream m_cOutputFileStream;
      /** The path to the folder into which the POVRay renderer should write to */
      std::string m_StrOutputFolder;
      /* The path to the folder into which the POVRay sources (one per frame) will be saved to*/
      std::string m_StrSourceFolderName;
      /** Reference to the text render visitor that draws an entity */
      CPovrayRenderVisitorDraw* m_pcVisitor;
      std::string m_StrFloorOutput;
      /* Content of the sky texture file (default or user defined) */
      std::string m_StrSkyOutput;
      /* Camera out string */
      std::string m_StrCameraOutput;
      /* Camera out string */
      std::string m_StrLightOutput;
      /* Map that contains the camera for each step*/
      TSceneStepCameraMap m_mapSceneStepCamera;
      /* Map that maps the user camera definitions to POVRay camera settings */
      TSceneCameraTypeDefinitions m_mapCameraTypeDefinitions;

   public:

	   CPovrayRender() :
	     m_cOutputFileStream(NULL),
         m_StrOutputFolder(""),
         m_StrSourceFolderName(""),
         m_pcVisitor(NULL),
         m_StrFloorOutput(""),
         m_StrSkyOutput(""),
         m_StrCameraOutput(""),
         m_StrLightOutput(""){}


      virtual ~CPovrayRender() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Execute();
      virtual void Destroy();

      virtual void WriteOneFrame(const std::string& str_path_to_file);
   private:

	  void WriteEnvironment();
	  void WriteCamera();
      void WriteEntities();

      void CopyTexture(std::string& str_texture);
      std::string GetBasename(std::string& str_filename);

      void InitEnvironment(TConfigurationNode& t_tree);
      void InitFloor(TConfigurationNode& t_tree);
      void InitSky(TConfigurationNode& t_tree);
      void InitScene(TConfigurationNode& t_tree);
      void InitEntityToIgnore(TConfigurationNode& t_tree);
      void InitLightSources(TConfigurationNode& t_tree);
      void InitBoxesAndCylinders(TConfigurationNode& t_tree);
      std::string FileToString(std::string& str_path_to_file);
      std::string GetStandardPovrayOrPovrayRGBColor(TConfigurationNode& t_tree, const std::string& str_node_name);
   };

}

#endif

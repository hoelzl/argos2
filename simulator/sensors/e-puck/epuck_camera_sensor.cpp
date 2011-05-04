/* -*- Mode: C++ -*-
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
 * @file <argos2/simulator/sensors/e-puck/epuck_camera_sensor.cpp>
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#include "epuck_camera_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   static const Real CAMERA_ELEVATION = 0.027f; // Same value than in the "epuck_entity.cpp" file
   static const Real EPUCK_RADIUS = 0.035f; // Same value than in the "epuck_entity.cpp" file
   
   const CRadians PI(ARGOS_PI);
   const CRadians CAMERA_HALF_ANGULAR_HORIZONTAL_RANGE = PI/6.0f; // 30 deg
   const CRadians CAMERA_HALF_ANGULAR_VERTICAL_RANGE = PI/6.0f;
   const Real CAMERA_MAX_DISTANCE_RANGE = 1.3;

   //  Noises defined on angule, distance and range
   const Real MAX_NOISE_ANGLE = 0; //        = ( 0.0174 ); // 0.0174 = more or less 1 degree
   const Real MAX_NOISE_ANGLE_SENSED = 0; //        = ( 0.0174 ); // 0.0174 = more or less 1 degree
   const Real MAX_NOISE_DISTANCE = 0; //     = 0.01;

   // TODO: make camera area configurable
   // @see Epuck HAL - Fast 2 times camera
   UInt16 DEFAULT_PIXEL_NUMBER_WIDTH = 60;
   UInt16 DEFAULT_PIXEL_NUMBER_HEIGHT = 1;

   // Maximum size of the image (in byte) that the e-puck can capture (has to be verified...it is now a minimum value)
   UInt16 IMAGE_MAXIMUM_SIZE = 160;

   /****************************************/
   /****************************************/

   CEPuckCameraSensor::CEPuckCameraSensor() :
      m_bEnabled(false),
      m_unWidth(DEFAULT_PIXEL_NUMBER_WIDTH),
      m_unHeight(DEFAULT_PIXEL_NUMBER_HEIGHT),
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_cEmbodiedSpaceHash(m_cSpace.GetEmbodiedEntitiesSpaceHash()),
      m_cLEDSpaceHash(m_cSpace.GetLEDEntitiesSpaceHash()),
      m_unCameraElevation(m_cLEDSpaceHash.SpaceToHashTable(CAMERA_ELEVATION, 2)),
      m_bShowRays(false) {
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::Init(TConfigurationNode& t_tree) {
      try {
         InitCamera();
         CCI_EPuckCameraSensor::Init(t_tree);
         /* Precalculate the list of cells to analyze */
         CalculateCellsToAnalyze();
         /* Show rays? */
         GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in e-puck camera.", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::Update() {
      /* Compute only if enabled */
      if(m_bEnabled) {
         for(UInt16 i=0;i<m_unHeight;i++){
            for(UInt16 j=0;j<2*m_unWidth;j++){
               m_punCameraReadings[i][j] = 0;
            }
         } 
         ComputeCameraReadings();
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::Reset() {
      /* Erase the last image */
      for(UInt16 i=0;i<m_unHeight;i++){
         for(UInt16 j=0;j<2*m_unWidth;j++){
            m_punCameraReadings[i][j] = 0;
         }
      } 
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::Destroy() {
      m_bEnabled = false;
      for(UInt16 i=0;i<m_unHeight;i++)
         delete [] m_punCameraReadings[i];
      delete [] m_punCameraReadings;
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::ChangeResolution(UInt16 un_width, UInt16 un_height){
      /* Verifies if the total size is less than the maximum size of an image that the e-puck can support */
      if(un_width * un_height < IMAGE_MAXIMUM_SIZE){
         /* Removing the last image so a new one can be created with new dimensions */
         for(UInt16 i=0;i<m_unHeight;i++)
            delete [] m_punCameraReadings[i];
         delete [] m_punCameraReadings;
         m_unWidth = un_width;
         m_unHeight = un_height;
         /* Initialize the camera with the new dimension */
         InitCamera();
      }
      else
         LOG << "ERROR in epuck_camera_sensor : The new resolution is too big for the e-puck memory. The old resolution was kept." << std::endl;
   }

   /****************************************/
   /****************************************/

   UInt16 CEPuckCameraSensor::GetWidth(){
      return m_unWidth;
   }

   /****************************************/
   /****************************************/

   UInt16 CEPuckCameraSensor::GetHeight(){
      return m_unHeight;
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::InitCamera(){
      try{
         // Get and fix the number of pixel the camera is taking.
         m_unPixels = 2*m_unWidth*m_unHeight;
         m_punCameraReadings = new UInt8 * [m_unHeight];
         for(UInt16 i=0;i<m_unHeight;i++) {
            m_punCameraReadings[i] = new UInt8[2*m_unWidth];
            ::memset(m_punCameraReadings[i], 0, sizeof(UInt8) * 2 * m_unWidth);
         }  
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in e-puck camera.", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::CalculateCellsToAnalyze() {
      /* Calculate the maximum range of the camera in the hash table axis system */
      CVector3 cCameraMaxDistanceRange(m_cLEDSpaceHash.SpaceToHashTable(CAMERA_MAX_DISTANCE_RANGE, 0),
                                       m_cLEDSpaceHash.SpaceToHashTable(CAMERA_MAX_DISTANCE_RANGE, 1),
                                       m_cLEDSpaceHash.SpaceToHashTable(CAMERA_MAX_DISTANCE_RANGE, 2));
      
      CVector3 cTempCell, cRealCellPos;
      Real fLength;
      CRadians cInclination;
      /* Search the cells in a cube around the e-puck */
      m_sCellsToVisit.push_back(SCellCoords(0,0,0));
      for(UInt16 unH = 0; unH <= cCameraMaxDistanceRange.GetZ()+m_unCameraElevation; ++unH) {
         for(SInt16 nL = -cCameraMaxDistanceRange.GetX(); nL <= cCameraMaxDistanceRange.GetX(); nL++){
            for(SInt16 nW = -cCameraMaxDistanceRange.GetY(); nW <= cCameraMaxDistanceRange.GetY(); nW++){ 
               cTempCell.Set(nL,nW,unH);
               cRealCellPos.Set(m_cLEDSpaceHash.HashTableToSpace(nL,0),m_cLEDSpaceHash.HashTableToSpace(nW,1),m_cLEDSpaceHash.HashTableToSpace(unH,2));
               fLength = cTempCell.Length();
               cInclination = (ASin(unH/fLength)).SignedNormalize();
               /* Add a cell if it is visible by the e-puck whatever its orientation (with the assumption rot-z-only) */ 
               /* and if the cell is in the range of the camera */
               if(cInclination <= CAMERA_HALF_ANGULAR_VERTICAL_RANGE
                  && cInclination >= -CAMERA_HALF_ANGULAR_VERTICAL_RANGE
                  && cRealCellPos.Length() <= CAMERA_MAX_DISTANCE_RANGE){
                  m_sCellsToVisit.push_back(SCellCoords(nL,nW,unH));
               }
            }
         }
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::ComputeCameraReadings() {
      /* Get the position of the e-puck */
      const CVector3& cEPuckPosition = GetEntity().GetEmbodiedEntity().GetPosition();
      /* We make the assumption that the e-puck is rotated only around Z */
      /* Get the e-puck orientation */
      CRadians cTmp1, cTmp2, cOrientationZ;
      GetEntity().GetEmbodiedEntity().GetOrientation().ToEulerAngles(cOrientationZ, cTmp1, cTmp2);
      /* Calculate the relative position of the camera (despite the name of the variable) */
      CVector2 cCameraPosition;
      cCameraPosition.Set(EPUCK_RADIUS,0.0f);
      cCameraPosition.Rotate(cOrientationZ);
      /* Calculate the real position of the camera */
      cCameraPosition.Set(cEPuckPosition.GetX()+cCameraPosition.GetX(),cEPuckPosition.GetY()+cCameraPosition.GetY());
      /* Initialize the occlusion check ray start to the top of the e-puck */
      CRay cOcclusionCheckRay;
      cOcclusionCheckRay.SetStart(CVector3(cCameraPosition.GetX(), cCameraPosition.GetY(), CAMERA_ELEVATION));
      /* Buffer to store the intersection data */
      CSpace::SEntityIntersectionItem<CEmbodiedEntity> sIntersectionData;
      /* Ignore the sensing robot when checking for occlusions */
      TEmbodiedEntitySet tIgnoreEntities;
      tIgnoreEntities.insert(&GetEntity().GetEmbodiedEntity());
      /* Get the center of the e-puck camera (in the space hash) on XY */
      SInt32 nCenterI = m_cLEDSpaceHash.SpaceToHashTable(cCameraPosition.GetX(), 0);
      SInt32 nCenterJ = m_cLEDSpaceHash.SpaceToHashTable(cCameraPosition.GetY(), 1);
      SInt32 nCenterK = m_cLEDSpaceHash.SpaceToHashTable(CAMERA_ELEVATION, 2);
      GetEntity().GetControllableEntity().AddIntersectionPoint(cOcclusionCheckRay, sIntersectionData.TOnRay);
      /* Buffer for calculating the LED--e-puck distance */
      CVector3 cLEDDistance;
      /* Go through the precalculated list of cells to visit */
      for(UInt32 unCell = 0; unCell < m_sCellsToVisit.size(); ++unCell) {
         /* Get a reference to the current cell to visit */
         SCellCoords& sCell = m_sCellsToVisit[unCell];
         /* Clear the list of candidate LEDs */
         TLedEntitySet tVisibleLEDs;
         /* Visit the cell to collect candidate LEDs */
         if(m_cLEDSpaceHash.CheckCell(sCell.I+nCenterI,
                                      sCell.J+nCenterJ,
                                      sCell.K+nCenterK,
                                      tVisibleLEDs)) {
            /* New candidate LEDs found
               Check for occlusions among the candidate elements */
            for(TLedEntitySet::iterator itLED = tVisibleLEDs.begin();
                itLED != tVisibleLEDs.end(); ++itLED) {
               /* Get a reference to this LED */
               CLedEntity& cLED = **itLED;
               /* A robot cannot see its own LEDs, so check to whom they belong */
               if(&cLED.GetParent() != m_pcLEDEntity) {
                   /* The LED is visible if it's not black */
                  if(cLED.GetColor() != CColor::BLACK) {
                     /* Set the end point of the occlusion check ray to the position of the LED
                        Now we have a ray connecting the e-puck top to the candidate LED */
                     cOcclusionCheckRay.SetEnd(cLED.GetPosition());
                     /* Is there an embodied entity along this ray?
                        One is enough, so just tell me closest */
                     if(! m_cSpace.GetClosestEmbodiedEntityIntersectedByRay(sIntersectionData,
                                                                            cOcclusionCheckRay,
                                                                            tIgnoreEntities)) {
                        /* The LED is not obstructed */
                        /* This LED is OK, create a reading for it */
                        /* Create the distance vector from the center of the robot to the LED */
                        cLEDDistance.Set(cLED.GetPosition().GetX() - cCameraPosition.GetX(),
                                         cLED.GetPosition().GetY() - cCameraPosition.GetY(),
                                         cLED.GetPosition().GetZ() - CAMERA_ELEVATION);        
                        /* Calculate the value of the angles */
                        CRadians * pcAngles = new CRadians[2];
                        /* The first angle is the one in the horizontal plan */
                        pcAngles[0] = ATan2(cLEDDistance.GetY(),cLEDDistance.GetX());
                        pcAngles[0] -= cOrientationZ;
                        pcAngles[0].SignedNormalize();
                        /* The second one is the inclination */
                        pcAngles[1] = ATan2(cLEDDistance.GetZ(),
                        ::sqrt(cLEDDistance.GetX()*cLEDDistance.GetX()+cLEDDistance.GetY()*cLEDDistance.GetY())).SignedNormalize();
                        /* Verifies if the camera can see the led. If it is the case, the led is added to the camera. */
                        if(pcAngles[0]<CAMERA_HALF_ANGULAR_HORIZONTAL_RANGE && pcAngles[0]> -CAMERA_HALF_ANGULAR_HORIZONTAL_RANGE){
                           if(pcAngles[1]<CAMERA_HALF_ANGULAR_VERTICAL_RANGE && pcAngles[1]> -CAMERA_HALF_ANGULAR_VERTICAL_RANGE
                              && ::sqrt(cLEDDistance.GetX()*cLEDDistance.GetX()+cLEDDistance.GetY()*cLEDDistance.GetY()+cLEDDistance.GetZ()*cLEDDistance.GetZ())
                              <CAMERA_MAX_DISTANCE_RANGE) 
                              if(m_bShowRays) GetEntity().GetControllableEntity().AddCheckedRay(true, cOcclusionCheckRay);
                              ComputeView(cLEDDistance.Length() * 100,pcAngles,cLED.GetColor());
                        }
                        delete[] pcAngles;
                     }
                     else {
                        if(m_bShowRays) {
                           GetEntity().GetControllableEntity().AddCheckedRay(false, cOcclusionCheckRay);
                        }
                     }
                  }
               }
            }
         }
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckCameraSensor::ComputeView(Real f_distance, CRadians * pc_angle, CColor c_color){
      
      // shift from angle view to array position
      UInt16 unHorizontalAngle = Floor(-m_unWidth * pc_angle[0].GetValue() / CAMERA_HALF_ANGULAR_HORIZONTAL_RANGE.GetValue() + m_unWidth);
      /* Verify that unHorizontalAngle is an odd value */
      unHorizontalAngle -= unHorizontalAngle%2;
      if(unHorizontalAngle>(2*m_unWidth-2))
         unHorizontalAngle=2*m_unWidth-2;
      UInt16 unVerticalAngle = Floor((m_unHeight * pc_angle[1].GetValue() / CAMERA_HALF_ANGULAR_VERTICAL_RANGE.GetValue() + m_unHeight)/2);
      if(unVerticalAngle>m_unHeight-1)
         unVerticalAngle=m_unHeight-1;

      UInt8 unPixel_RG = (UInt8)(((c_color.GetRed() & 0xF8) >> 1) | ((c_color.GetGreen() & 0xC0) >> 6));
      UInt8 unPixel_GB = (UInt8)(((c_color.GetGreen() & 0x38) << 2) | ((c_color.GetBlue() & 0xF8) >> 3));

      //UInt8 unPixel_RG = (UInt8)(((unColor & 0x00F80000) >> 17) | ((unColor & 0x0000C000) >> 14));   // old calculations from argos 1
      //UInt8 unPixel_GB = (UInt8)(((unColor & 0x00003800) >> 6)  | ((unColor & 0x000000F8) >> 3));
 
      // do logic OR on interested pixels    
      m_punCameraReadings[unVerticalAngle][unHorizontalAngle] = unPixel_RG | m_punCameraReadings[unVerticalAngle][unHorizontalAngle];
      m_punCameraReadings[unVerticalAngle][unHorizontalAngle+1] = unPixel_GB | m_punCameraReadings[unVerticalAngle][unHorizontalAngle+1];
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEPuckCameraSensor,
                   "epuck_camera", "rot_z_only",
                   "The e-puck camera sensor (optimized for 2D)",
                   "Laurent Compere [lcompere@ulb.ac.be]",
                   "This sensor accesses the e-puck camera sensor. For a\n"
                   "complete description of its usage, refer to the common interface.\n"
                   "In this implementation, the readings are calculated under the assumption that\n"
                   "the e-puck is always parallel to the XY plane, i.e., it rotates only around\n"
                   "the Z axis. This implementation is faster than a 3D one and should be used\n"
                   "only when the assumption about the e-puck rotation holds.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <epuck_camera implementation=\"rot_z_only\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "It is possible to draw the rays shot by the camera in the OpenGL\n"
                   "visualization. This can be useful for sensor debugging but also to understand\n"
                   "what's wrong in your controller. In OpenGL, the rays are drawn in cyan when\n"
                   "they are not obstructed and in purple when they are. In case a ray is\n"
                   "obstructed, a black dot is drawn where the intersection occurred.\n"
                   "To turn this functionality on, add the attribute 'show_rays=\"true\"' in the\n"
                   "XML as in this example:\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <epuck_camera implementation=\"rot_z_only\"\n"
                   "                                        show_rays=\"true\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Under development"
      );

}

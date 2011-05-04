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
 * @file <argos2/simulator/sensors/foot-bot/footbot_ceiling_camera_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "footbot_ceiling_camera_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   static const Real FOOTBOT_HEIGHT = 0.288699733f;

   /****************************************/
   /****************************************/

   CFootBotCeilingCameraSensor::CFootBotCeilingCameraSensor() :
      m_bEnabled(false),
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_cEmbodiedSpaceHash(m_cSpace.GetEmbodiedEntitiesSpaceHash()),
      m_cLEDSpaceHash(m_cSpace.GetLEDEntitiesSpaceHash()),
      m_nCameraElevation(m_cLEDSpaceHash.SpaceToHashTable(FOOTBOT_HEIGHT, 2)),
      m_nArenaHeight(m_cLEDSpaceHash.SpaceToHashTable(m_cSpace.GetArenaSize().GetZ(), 2)),
      m_fApertureSlope(0.0f),
      m_bShowRays(false) {
   }

   /****************************************/
   /****************************************/

   void CFootBotCeilingCameraSensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_FootBotCeilingCameraSensor::Init(t_tree);
         /* Get the aperture */
         CDegrees cAperture;
         GetNodeAttributeOrDefault(t_tree, "aperture", cAperture, CDegrees(30.0f));
         m_cApertureAngle = ToRadians(cAperture);
         m_fApertureSlope = Tan(m_cApertureAngle);
         /* Precalculate the list of cells to analyze */
         CalculateCellsToAnalyze();
         /* Show rays? */
         GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in foot-bot ceiling camera.", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotCeilingCameraSensor::Update() {
      /* Compute only if enabled */
      if(m_bEnabled) {
         /* Erase the last detected blobs */
         while(!m_sCameraReadings.BlobList.empty()) {
            delete m_sCameraReadings.BlobList.back();
            m_sCameraReadings.BlobList.pop_back();
         }
         CalculateBlobs();
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotCeilingCameraSensor::Reset() {
      /* By default, the camera is not enabled */
      m_bEnabled = false;
      /* Erase the last detected blobs */
      while(!m_sCameraReadings.BlobList.empty()) {
         delete m_sCameraReadings.BlobList.back();
         m_sCameraReadings.BlobList.pop_back();
      }
      /* Reset the sensor updating counter */
      m_sCameraReadings.Counter = 0;
   }

   /****************************************/
   /****************************************/

   void CFootBotCeilingCameraSensor::Destroy() {
      m_bEnabled = false;
      while(!m_sCameraReadings.BlobList.empty()) {
         delete m_sCameraReadings.BlobList.back();
         m_sCameraReadings.BlobList.pop_back();
      }
      m_sCameraReadings.Counter = 0;
   }

   /****************************************/
   /****************************************/

   void CFootBotCeilingCameraSensor::CalculateCellsToAnalyze() {
      /* We make the assumption that the rotation is only along Z */
      SInt32 nRangeOnX, nRangeOnY;
      SInt32 nI, nJ;
      Real fHeight;
      /* Move from the floor to the top of the foot-bot */
      for(SInt32 nK = m_nCameraElevation; nK <= m_nArenaHeight; ++nK) {
         /* Calculate the range on the XY plane at height nK */
         fHeight = m_cLEDSpaceHash.HashTableToSpace(nK, 2) - FOOTBOT_HEIGHT;
         nRangeOnX = m_cLEDSpaceHash.SpaceToHashTable(m_fApertureSlope * fHeight, 0);
         nRangeOnY = m_cLEDSpaceHash.SpaceToHashTable(m_fApertureSlope * fHeight, 1);
         /* Go through XY according to the range
            The next for loops sweep a square area.
         */
         for(nJ = -nRangeOnY; nJ <= nRangeOnY; ++nJ) {
            for(nI = -nRangeOnX; nI <= nRangeOnX; ++nI) {
               /* Add the cell to the list of those to visit */
               m_sCellsToVisit.push_back(SCellCoords(nI, nJ, nK));
            }
         }
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotCeilingCameraSensor::CalculateBlobs() {
      /* Get the position of the foot-bot */
      const CVector3& cFootBotPosition = GetEntity().GetEmbodiedEntity().GetPosition();
      /* We make the assumption that the foot-bot is rotated only around Z */
      /* Get the foot-bot orientation */
      CRadians cTmp1, cTmp2, cOrientationZ;
      GetEntity().GetEmbodiedEntity().GetOrientation().ToEulerAngles(cOrientationZ, cTmp1, cTmp2);
      /* Initialize the occlusion check ray start to the top of the foot-bot */
      CRay cOcclusionCheckRay;
      cOcclusionCheckRay.SetStart(CVector3(cFootBotPosition.GetX(), cFootBotPosition.GetY(), FOOTBOT_HEIGHT));
      /* Buffer to store the intersection data */
      CSpace::SEntityIntersectionItem<CEmbodiedEntity> sIntersectionData;
      /* Ignore the sensing robot when checking for occlusions */
      TEmbodiedEntitySet tIgnoreEntities;
      tIgnoreEntities.insert(&GetEntity().GetEmbodiedEntity());
      /* Get the center of the foot-bot (in the space hash) on XY */
      SInt32 nCenterI = m_cLEDSpaceHash.SpaceToHashTable(cFootBotPosition.GetX(), 0);
      SInt32 nCenterJ = m_cLEDSpaceHash.SpaceToHashTable(cFootBotPosition.GetY(), 1);
      /* Buffer for calculating the LED--foot-bot distance */
      CVector2 cLEDDistance;
      /* Go through the precalculated list of cells to visit */
      for(UInt32 unCell = 0; unCell < m_sCellsToVisit.size(); ++unCell) {
         /* Get a reference to the current cell to visit */
         SCellCoords& sCell = m_sCellsToVisit[unCell];
         /* Clear the list of candidate LEDs */
         TLedEntitySet tVisibleLEDs;
         /* Visit the cell to collect candidate LEDs */
         if(m_cLEDSpaceHash.CheckCell(sCell.I+nCenterI,
                                      sCell.J+nCenterJ,
                                      sCell.K,
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
                        Now we have a ray connecting the foot-bot top to the candidate LED */
                     cOcclusionCheckRay.SetEnd(cLED.GetPosition());

CVector3 cRayVector;
cOcclusionCheckRay.ToVector(cRayVector);
Real fRadius;
CRadians cInclination, cAzimuth;
cRayVector.ToSphericalCoords(fRadius,cInclination,cAzimuth);
/* Check if angle within aperture */
if (fabs(cInclination.SignedNormalize().GetValue()) < m_cApertureAngle.GetValue())
{

                     /* Is there an embodied entity along this ray?
                        One is enough, so just tell me closest */
                     if(! m_cSpace.GetClosestEmbodiedEntityIntersectedByRay(sIntersectionData,
                                                                            cOcclusionCheckRay,
                                                                            tIgnoreEntities)) {
                        /* The LED is not obstructed */
                        if(m_bShowRays) GetEntity().GetControllableEntity().AddCheckedRay(false, cOcclusionCheckRay);
                        /* This LED is OK, create a reading for it */
                        /* Create the distance vector from the center of the robot to the LED */
                        cLEDDistance.Set(cLED.GetPosition().GetX() - cFootBotPosition.GetX(),
                                         cLED.GetPosition().GetY() - cFootBotPosition.GetY());
                        /* Add the blob */
                        m_sCameraReadings.BlobList.push_back(
                           new SBlob(
                              cLED.GetColor(),
                              (cLEDDistance.Angle() - cOrientationZ).SignedNormalize(),
                              cLEDDistance.Length() * 100,  // The camera sensor transfers distances in cm!
                              0.0f, // TODO: transform cm into pixel
                              3.0f // TODO: calculate area
                              ));
                        m_sCameraReadings.Counter++;
                     }
                     else {
                        if(m_bShowRays) {
                           GetEntity().GetControllableEntity().AddCheckedRay(true, cOcclusionCheckRay);
                           GetEntity().GetControllableEntity().AddIntersectionPoint(cOcclusionCheckRay, sIntersectionData.TOnRay);
                        }
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

   REGISTER_SENSOR(CFootBotCeilingCameraSensor,
                   "footbot_ceiling_camera", "rot_z_only",
                   "The foot-bot ceiling camera sensor (optimized for 2D)",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "This sensor accesses the foot-bot ceiling camera sensor. For a\n"
                   "complete description of its usage, refer to the common interface.\n"
                   "In this implementation, the readings are calculated under the assumption that\n"
                   "the foot-bot is always parallel to the XY plane, i.e., it rotates only around\n"
                   "the Z axis. This implementation is faster than a 3D one and should be used\n"
                   "only when the assumption about the foot-bot rotation holds.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_ceiling_camera implementation=\"rot_z_only\" />\n"
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
                   "        <footbot_ceiling_camera implementation=\"rot_z_only\"\n"
                   "                                show_rays=\"true\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Under development"
      );

}

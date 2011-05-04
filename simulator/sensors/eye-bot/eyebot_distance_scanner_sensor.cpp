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
 * @file <argos2/simulator/sensors/eye-bot/eyebot_distance_scanner_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "eyebot_distance_scanner_sensor.h"
#include <argos2/simulator/simulator.h>

namespace argos {

   /****************************************/
   /****************************************/

   static const Real DISTANCE_SCANNER_ELEVATION = 0.1f;
   static const Real DISTANCE_SCANNER_RANGE     = 15.0f;

   /****************************************/
   /****************************************/

   CEyeBotDistanceScannerSensor::CEyeBotDistanceScannerSensor() :
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_cEmbodiedSpaceHash(m_cSpace.GetEmbodiedEntitiesSpaceHash()),
      m_bShowRays(false),
      m_cAngleSlice(CRadians::TWO_PI / CCI_EyeBotDistanceScannerSensor::NUM_READINGS) {
   }

   /****************************************/
   /****************************************/

   void CEyeBotDistanceScannerSensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_EyeBotDistanceScannerSensor::Init(t_tree);
         /* Show rays? */
         GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in eye-bot distance scanner sensor.", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CEyeBotDistanceScannerSensor::Update() {
      /* Clear the map */
      m_tReadings.clear();
      /* Get the position of the eye-bot */
      const CVector3& cPosition = m_pcEmbodiedEntity->GetPosition();
      /* Get the orientation of the eye-bot */
      const CQuaternion& cOrientation = m_pcEmbodiedEntity->GetOrientation();
      /* Calculate the ray start */
      m_cRayStart.Set(0.0f, 0.0f, DISTANCE_SCANNER_ELEVATION);
      m_cRayStart.Rotate(cOrientation);
      m_cRayStart += cPosition;
      /* Calculate the first ray end */
      m_cRayEnd.Set(DISTANCE_SCANNER_RANGE, 0.0f, DISTANCE_SCANNER_ELEVATION);
      m_cRayEnd.Rotate(cOrientation);
      m_cRayEnd += cPosition;
      /* Calculate the reading for the ray */
      m_tReadings[CRadians::ZERO] = CalculateReadingForRay(CRay(m_cRayStart,m_cRayEnd));
      /* Cycle through the other rays */
      for(UInt32 i = 1; i < CCI_EyeBotDistanceScannerSensor::NUM_READINGS; ++i) {         
         /* Calculate the ray end */
         m_cRayEnd.Set(DISTANCE_SCANNER_RANGE, 0.0f, DISTANCE_SCANNER_ELEVATION);
         m_cRayEnd.RotateZ(m_cAngleSlice * i);
         m_cRayEnd.Rotate(cOrientation);
         m_cRayEnd += cPosition;
         /* Calculate the reading for the ray */
         m_tReadings[m_cAngleSlice * i] = CalculateReadingForRay(CRay(m_cRayStart,m_cRayEnd));
      }
   }

   /****************************************/
   /****************************************/

   void CEyeBotDistanceScannerSensor::Reset() {      
      /* Clear the map */
      m_tReadings.clear();
   }

   /****************************************/
   /****************************************/

   Real CEyeBotDistanceScannerSensor::CalculateReadingForRay(const CRay& c_ray) {
      /* Get the closest intersection */
      CSpace::SEntityIntersectionItem<CEmbodiedEntity> sIntersection;
      if(m_cSpace.GetClosestEmbodiedEntityIntersectedByRay(sIntersection, c_ray)) {
         if(m_bShowRays) {
            GetEntity().GetControllableEntity().AddCheckedRay(true, c_ray);
            GetEntity().GetControllableEntity().AddIntersectionPoint(c_ray, sIntersection.TOnRay);
         }
         /* There is an intersection! */
         /* NO: WE KEEP METERS FOR NOW! - The distance is returned in meters, but the reading must be in cm */ 
         return c_ray.GetDistance(sIntersection.TOnRay); // * 100.0f;
      }
      else {
         /* No intersection */
         if(m_bShowRays) GetEntity().GetControllableEntity().AddCheckedRay(false, c_ray);
         return DISTANCE_SCANNER_RANGE;  // Return maximum instead of -2 as for footbot
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEyeBotDistanceScannerSensor,
                   "eyebot_distance_scanner", "default",
                   "The eye-bot distance scanner sensor",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "This sensor accesses the eye-bot distance scanner sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <eyebot_distance_scanner implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "It is possible to draw the rays shot by the distance scanner in the OpenGL\n"
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
                   "        <eyebot_distance_scanner implementation=\"default\"\n"
                   "                                  show_rays=\"true\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Under development"
      );

}

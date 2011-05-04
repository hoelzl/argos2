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
 * @file <argos2/simulator/sensors/e-puck/epuck_proximity_sensor.cpp>
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#include <argos2/common/utility/argos_random.h>

#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/simulator.h>

#include "epuck_proximity_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   static const Real EPUCK_RADIUS       = 0.035f;
   static const Real RAY_START_DISTANCE = EPUCK_RADIUS;
   static const Real RAY_END_DISTANCE   = EPUCK_RADIUS + 0.075f;
   static const Real SENSOR_ELEVATION   = 0.06f; //TODO: fix (measured by hand...)

   const CRange<Real> CEPuckProximitySensor::EPUCK_PROXIMITY_SENSORS_READINGS_RANGE(0,4096);

   /****************************************/
   /****************************************/

   CEPuckProximitySensor::CEPuckProximitySensor() :
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_cEmbodiedSpaceHash(m_cSpace.GetEmbodiedEntitiesSpaceHash()),
      m_pcEmbodiedEntity(NULL),
      m_bShowRays(false),
      m_pcRNG(NULL),
      m_fNoiseLevel(0.0f) {}

   /****************************************/
   /****************************************/

   void CEPuckProximitySensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_EPuckProximitySensor::Init(t_tree);
         /* Show rays? */
         GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
         /* Parse noise level */
         GetNodeAttributeOrDefault(t_tree, "noise_level", m_fNoiseLevel, m_fNoiseLevel);
         m_fNoiseLevel *= EPUCK_PROXIMITY_SENSORS_READINGS_RANGE.GetMax();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in e-puck proximity sensor", ex);
      }
      /* Random number generator*/
      m_pcRNG = CARGoSRandom::CreateRNG("argos");
   }

   /****************************************/
   /****************************************/

   void CEPuckProximitySensor::Reset() {
      for(UInt16 i = 0; i < CCI_EPuckProximitySensor::NUM_READINGS; ++i) {
         m_tReadings[i].Value = 0.0f;
      }
   }

   /****************************************/
   /****************************************/

   /* Function implementing sensor response to distance.
    * Distance goes in cm.
    * */
   static Real MapReadingToDistance(Real f_distance){
      Real fDistance2 = f_distance * f_distance;
      Real fDistance3 = fDistance2 * f_distance;
      Real fDistance4 = fDistance3 * f_distance;
      /* Compute the reading with the equation found on
         http://iridia.ulb.ac.be/~e-puck/sampling/proximity/wall/results/sensor_model */
      Real measure = 3493.615f - (2392.238f * f_distance) + 741.182f * fDistance2 - 99.262f * fDistance3 + 4.782f * fDistance4;
      /* Limits to the maximum value found on http://www.roborealm.com/help/GCtronic_Epuck.php */
      if(measure > 3850.0f)
         return 3850.0f;
      else if (measure < 0.0f)
         return 0.0f;
      else
         return measure;
   }

   /****************************************/
   /****************************************/

   void CEPuckProximitySensor::Update() {
      /* We make the assumption that the e-puck is rotated only around Z */
      /* Get the e-puck orientation */
      CRadians cTmp1, cTmp2, cOrientationZ;
      m_pcEmbodiedEntity->GetOrientation().ToEulerAngles(cOrientationZ, cTmp1, cTmp2);
      /* Ray used for scanning the environment for obstacles */
      CRay cScanningRay;
      CVector3 cRayStart, cRayEnd;
      /* Buffers to contain data about the intersection */
      CSpace::SEntityIntersectionItem<CEmbodiedEntity> sIntersection;
      Real fDistance;
      /* Ignore the sensing robot when checking for occlusions */
      TEmbodiedEntitySet tIgnoreEntities;
      tIgnoreEntities.insert(m_pcEmbodiedEntity);
      cRayStart.SetZ(SENSOR_ELEVATION);
      cRayStart += m_pcEmbodiedEntity->GetPosition();
      for(UInt16 i = 0; i < CCI_EPuckProximitySensor::NUM_READINGS; ++i) {
         /* Compute reading */
         /* Compute ray for sensor i */
     	 cRayEnd = CVector3::X;
     	 cRayEnd.RotateZ(m_tReadings[i].Angle + cOrientationZ);
         cRayEnd *= RAY_END_DISTANCE;
         cRayEnd.SetZ(SENSOR_ELEVATION);
         cRayEnd += m_pcEmbodiedEntity->GetPosition();
         cScanningRay.Set(cRayStart,cRayEnd);
         /* Get the closest intersection */
         if(m_cSpace.GetClosestEmbodiedEntityIntersectedByRay(sIntersection, cScanningRay, tIgnoreEntities)) {
            /* There is an intersection */
            if(m_bShowRays) {
               GetEntity().GetControllableEntity().AddIntersectionPoint(cScanningRay, sIntersection.TOnRay);
               GetEntity().GetControllableEntity().AddCheckedRay(true, cScanningRay);
            }
            /* There is an intersection */
            /* Convert distance to cm for the distance-reading mapping function */
            fDistance = (cScanningRay.GetDistance(sIntersection.TOnRay) - EPUCK_RADIUS ) * 100.f;
            if(fDistance < 0.0) {
            	fDistance = 0.0;
            }
            m_tReadings[i].Value = MapReadingToDistance(fDistance);
         }
         else {
            /* No intersection */
            m_tReadings[i].Value = 0.0f;
            if(m_bShowRays) GetEntity().GetControllableEntity().AddCheckedRay(false, cScanningRay);
         }

         /* Apply noise to the sensor */
	 if( m_fNoiseLevel > 0.0f ) {
	    AddNoise(i);
	 }
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckProximitySensor::AddNoise(UInt16 un_sensor_index) {
      m_tReadings[un_sensor_index].Value += m_pcRNG->Uniform(CRange<Real>(-m_fNoiseLevel, m_fNoiseLevel));
      if(m_tReadings[un_sensor_index].Value<0)
         m_tReadings[un_sensor_index].Value=0;
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEPuckProximitySensor,
                   "epuck_proximity", "rot_z_only",
                   "The e-puck proximity sensor (optimized for 2D)",
                   "Giovanni Pini [gpini@ulb.ac.be]",
                   "This sensor accesses the e-puck proximity sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n"
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
                   "        <epuck_proximity implementation=\"rot_z_only\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "It is possible to draw the rays shot by the proximity sensor in the OpenGL\n"
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
                   "        <epuck_proximity implementation=\"rot_z_only\"\n"
                   "                         show_rays=\"true\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n"
                   "It is possible to specify noisy sensors in order to match the characteristics\n"
                   "of the real e-puck. This can be done with two xml parameters: 'noise_level'\n"
                   "indicates a percentage of the sensor range that is added to the actual sensor\n"
                   "reading. The added noise value is uniformly random on this range. With the\n"
                   "parameter 'range_noise_level' (NOT IMPLEMENTED YET) it is possible to specify how much the range of\n"
                   "the proximity sensors varies (in percentage) with respect to the standard.\n"
                   "To turn this functionality on, add the attribute 'show_rays=\"true\"' in the\n"
                   "XML as in this example:\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <epuck_proximity implementation=\"rot_z_only\"\n"
                   "                         noise_level=\"0.05\" />\n"
                   "                         range_noise_level=\"0.05\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Under development"
		  );

}

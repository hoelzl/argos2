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
 * @file <argos2/simulator/sensors/foot-bot/footbot_distance_scanner_sensor.cpp>
 *
 * @author Giovanni Pini - <gpini@ulb.ac.be>
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include <argos2/common/utility/argos_random.h>
#include <argos2/common/utility/math/segment.h>

#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/entities/box_entity.h>

#include "footbot_sampled_proximity_sensor.h"

namespace argos {

   static const Real FOOTBOT_RADIUS     = 0.085036758f;
   static const Real RAY_END_DISTANCE   = FOOTBOT_RADIUS + 0.1f;

   /****************************************/
   /****************************************/

   CFootBotSampledProximitySensor::CFootBotSampledProximitySensor() {}

   /****************************************/
   /****************************************/

   void CFootBotSampledProximitySensor::Init(TConfigurationNode& t_tree) {
      try {
         CGenericSampledSensor::Init(t_tree);
         CFootBotProximitySensor::Init(t_tree);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in foot-bot sampled proximity sensor", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotSampledProximitySensor::Update() {
      // reset the proximity readings
      for(UInt32 i = 0; i < CCI_FootBotProximitySensor::NUM_READINGS; ++i) {
         m_tReadings[i].Value = 0.0f;
      }

      CVector3 cProximityRange(RAY_END_DISTANCE, RAY_END_DISTANCE, RAY_END_DISTANCE);
      m_cSensorBoundingBox.MinCorner = m_pcEmbodiedEntity->GetPosition() - cProximityRange;
      m_cSensorBoundingBox.MaxCorner = m_pcEmbodiedEntity->GetPosition() + cProximityRange;

      CSpace::TAnyEntityMap tEntityMap;

      // iterate through all footbot entities
      try {
         tEntityMap = m_cSpace.GetEntitiesByType("footbot_entity");
         for(CSpace::TAnyEntityMap::iterator it = tEntityMap.begin(); it != tEntityMap.end(); ++it) {
            CFootBotEntity* pcEntity = any_cast<CFootBotEntity*>(it->second);
            if(pcEntity == &GetEntity()) continue;

            if(pcEntity->GetEmbodiedEntity().GetBoundingBox().Intersects(m_cSensorBoundingBox)) {
               Real fDistance = 0.0f;
               CRadians cAngle;
               if(GetDistanceAndAngle(pcEntity, fDistance, cAngle)) {
                  const Real* pfReadings = GetSensorReadings(pcEntity->GetTypeDescription(), fDistance, cAngle);
                  if(pfReadings != NULL) {
                     AddReadings(pfReadings);
                  }
               }
            }
         }
      }
      catch(CARGoSException& ex) {}

      // iterate through all box entities
      try{
         tEntityMap = m_cSpace.GetEntitiesByType("box_entity");
         for(CSpace::TAnyEntityMap::iterator it = tEntityMap.begin(); it != tEntityMap.end(); ++it) {
            CBoxEntity* entity = any_cast<CBoxEntity*>(it->second);

            if(entity->GetEmbodiedEntity().GetBoundingBox().Intersects(m_cSensorBoundingBox)) {
               Real distance = 0;
               CRadians angle(0);
               if(GetDistanceAndAngle(entity, distance, angle)) {
                  const Real* readings = GetSensorReadings(entity->GetTypeDescription(), distance, angle);
                  if(readings != NULL) {
                     AddReadings(readings);
                  }
               }
            }
         }
      }
      catch(CARGoSException& ex) {}

      // iterate through all cylinder entities
      try{
         tEntityMap = m_cSpace.GetEntitiesByType("cylinder_entity");
         for(CSpace::TAnyEntityMap::iterator it = tEntityMap.begin(); it != tEntityMap.end(); ++it) {
            CCylinderEntity* entity = any_cast<CCylinderEntity*>(it->second);

            if(entity->GetEmbodiedEntity().GetBoundingBox().Intersects(m_cSensorBoundingBox)) {
               Real distance = 0;
               CRadians angle(0);
               if(GetDistanceAndAngle(entity, distance, angle)) {
                  const Real* readings = GetSensorReadings(entity->GetTypeDescription(), distance, angle);
                  if(readings != NULL) {
                     AddReadings(readings);
                  }
               }
            }
         }
      }
      catch(CARGoSException& ex) {}

      // add noise
      for(UInt32 i = 0; i < CCI_FootBotProximitySensor::NUM_READINGS; ++i) {
         AddNoise(i);
	 
	 /* Normalize reading between 0 and 1, only if calibration has been performed */
	 if( m_bCalibrated ) {
	    m_tReadings[i].Value = FOOTBOT_PROXIMITY_SENSOR_READING_RANGE.NormalizeValue(m_tReadings[i].Value);
	 }
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotSampledProximitySensor::Reset() {
      CFootBotProximitySensor::Reset();
   }

   /****************************************/
   /****************************************/

   void CFootBotSampledProximitySensor::Destroy() {
      CGenericSampledSensor::Destroy();
   }

   /****************************************/
   /****************************************/

   bool CFootBotSampledProximitySensor::GetDistanceAndAngle(CFootBotEntity* pc_entity, Real& distance, CRadians& angle) {
      CRadians tmp1, tmp2, orientation;
      m_pcEmbodiedEntity->GetOrientation().ToEulerAngles(orientation, tmp2, tmp1);

      CVector2 relative_position = pc_entity->GetEmbodiedEntity().GetPosition().ProjectOntoXY() - m_pcEmbodiedEntity->GetPosition().ProjectOntoXY();
      distance = relative_position.Length() - 2*FOOTBOT_RADIUS;
      angle    = relative_position.Angle() - orientation;

      if(m_bShowRays) {
         CRay cScanningRay(m_pcEmbodiedEntity->GetPosition(),
                           CVector3(pc_entity->GetEmbodiedEntity().GetPosition().GetX(),
                                    pc_entity->GetEmbodiedEntity().GetPosition().GetY(),
                                    m_pcEmbodiedEntity->GetPosition().GetZ()));
         GetEntity().GetControllableEntity().AddIntersectionPoint(cScanningRay, (relative_position.Length()-FOOTBOT_RADIUS)/cScanningRay.GetLength());
         GetEntity().GetControllableEntity().AddCheckedRay(true, cScanningRay);
      }

      return true;
   }

   /****************************************/
   /****************************************/

   bool CFootBotSampledProximitySensor::GetDistanceAndAngle(CBoxEntity* pc_entity, Real& distance, CRadians& angle) {
      CVector2 position = m_pcEmbodiedEntity->GetPosition().ProjectOntoXY();
      CRadians tmp1, tmp2, orientation;
      m_pcEmbodiedEntity->GetOrientation().ToEulerAngles(orientation, tmp2, tmp1);

      CVector2 intersection(0,0);
      bool     dist_valid = false;

      CVector3 box_size = pc_entity->GetSize();
      CRadians box_orientation;
      pc_entity->GetEmbodiedEntity().GetOrientation().ToEulerAngles(box_orientation, tmp2, tmp1);


      CVector2 box_position(pc_entity->GetEmbodiedEntity().GetPosition().GetX(),pc_entity->GetEmbodiedEntity().GetPosition().GetY());
      CVector2 box_vertex[4];
      box_vertex[0] = box_position + CVector2(box_size.GetX(), box_size.GetY()).Rotate(box_orientation)*0.5;
      box_vertex[1] = box_position + CVector2(box_size.GetX(),-box_size.GetY()).Rotate(box_orientation)*0.5;
      box_vertex[2] = box_position + CVector2(-box_size.GetX(),-box_size.GetY()).Rotate(box_orientation)*0.5;
      box_vertex[3] = box_position + CVector2(-box_size.GetX(), box_size.GetY()).Rotate(box_orientation)*0.5;

      for(unsigned int i = 0; i < 4; i++) {
         CSegment box_side(box_vertex[i],box_vertex[(i+1)%4]);
         CVector2 closest_point, closest_segment_point;
         Real     fraction = box_side.GetMinimumDistancePoints(position, closest_point, closest_segment_point);
         if((fraction > 0) && (fraction < 1)) {
            Real dist = (position - closest_point).Length();
            if(!dist_valid || (dist < distance)) {
               distance = dist;
               intersection = closest_point;
               dist_valid = true;
            }
         }
      }

      if(m_bShowRays && dist_valid) {
         CRay cScanningRay(m_pcEmbodiedEntity->GetPosition(),
                           CVector3(intersection.GetX(),intersection.GetY(),m_pcEmbodiedEntity->GetPosition().GetZ()));
         GetEntity().GetControllableEntity().AddIntersectionPoint(cScanningRay, distance/(intersection - position).Length());
         GetEntity().GetControllableEntity().AddCheckedRay(true, cScanningRay);
      }


      distance -= FOOTBOT_RADIUS;
      angle = (intersection - position).Angle() - orientation;
      return dist_valid;
   }

   /****************************************/
   /****************************************/

   bool CFootBotSampledProximitySensor::GetDistanceAndAngle(CCylinderEntity* pc_entity, Real& distance, CRadians& angle) {
      CRadians tmp1, tmp2, orientation;
      m_pcEmbodiedEntity->GetOrientation().ToEulerAngles(orientation, tmp2, tmp1);

      CVector2 relative_position = pc_entity->GetEmbodiedEntity().GetPosition().ProjectOntoXY() - m_pcEmbodiedEntity->GetPosition().ProjectOntoXY();
      distance = relative_position.Length() - FOOTBOT_RADIUS - pc_entity->GetRadius();
      angle    = relative_position.Angle() - orientation;

      if(m_bShowRays) {
         CRay cScanningRay(m_pcEmbodiedEntity->GetPosition(),
                           CVector3(pc_entity->GetEmbodiedEntity().GetPosition().GetX(),
                                    pc_entity->GetEmbodiedEntity().GetPosition().GetY(),
                                    m_pcEmbodiedEntity->GetPosition().GetZ()));
         GetEntity().GetControllableEntity().AddIntersectionPoint(cScanningRay, (relative_position.Length()-pc_entity->GetRadius())/cScanningRay.GetLength());
         GetEntity().GetControllableEntity().AddCheckedRay(true, cScanningRay);
      }

      return true;
   }

   /****************************************/
   /****************************************/

   void CFootBotSampledProximitySensor::AddReadings(const Real* pf_readings) {
      for(UInt32 i = 0; i < CCI_FootBotProximitySensor::NUM_READINGS; i++) {
         m_tReadings[i].Value = Max(m_tReadings[i].Value, pf_readings[i]);
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CFootBotSampledProximitySensor,
                   "footbot_proximity", "sampled",
                   "The foot-bot proximity sensor (sampling technique)",
                   "Vito Trianni [vito.trianni@istc.cnr.it]",
                   "This sensor accesses the foot-bot proximity sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n"
                   "In this implementation, the readings are pre-calculated (sampled) and stored in"
                   "a file, to be loaded at the initialisation (see below). Various assumptions\n"
                   "are done for this technique, see Migliono et al., Evolving Mobile Robots in\n"
                   "Simulated and Real Environments, Artificial Life 2(4):417-434, 1995\n"
                   "To load sensor samples, use the xml configuration as follows.\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_proximity implementation=\"sampled\">\n"
                   "          <samples entity=\"footbot_entity\"  filename=\"path/to/sample/file/footbot.sam\" />"
                   "          <samples entity=\"box_entity\"      filename=\"path/to/sample/file/box.sam\" />"
                   "          <samples entity=\"cylinder_entity\" filename=\"path/to/sample/file/cylinder.sam\" />"
                   "        </footbot_proximity>\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "It is possible to draw the rays shot by the proximity sensor in the OpenGL\n"
                   "visualization. XML as in this example:\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_proximity implementation=\"sampled\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n"
                   "It is possible to specify noisy sensors in order to match the characteristics\n"
                   "of the real robot. This can be done with two xml parameters: 'noise_level'\n"
                   "indicates a percentage of the sensor range that is added to the actual sensor\n"
                   "reading. The added noise value is uniformly random on this range." 
		   // "With the parameter 'range_noise_level' it is possible to specify how much the range of\n"
		   // "the proximity sensors varies (in percentage) with respect to the standard.\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_proximity implementation=\"rot_z_only\"\n"
                   "                                  noise_level=\"0.05\" />\n"
                   // "                                  range_noise_level=\"0.05\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Under development"
      );

}

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
 * @file <argos2/simulator/sensors/foot-bot/footbot_sampled_proximity_sensor.h>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef FOOTBOT_SAMPLED_PROXIMITY_SENSOR_H
#define FOOTBOT_SAMPLED_PROXIMITY_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotSampledProximitySensor;
}

#include <argos2/simulator/sensors/generic_sampled_sensor.h>
#include <argos2/simulator/sensors/foot-bot/footbot_proximity_sensor.h>
#include <argos2/simulator/space/entities/box_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>
#include <argos2/simulator/space/entities/embodied_entity.h>



namespace argos {

   class CFootBotSampledProximitySensor : public CFootBotProximitySensor,
                                          public CGenericSampledSensor {

   public:

      CFootBotSampledProximitySensor();
      virtual ~CFootBotSampledProximitySensor() {};

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Update();
      virtual void Reset();
      virtual void Destroy();

   protected:

      virtual bool GetDistanceAndAngle(CFootBotEntity* pc_entity, Real& f_distance, CRadians& c_angle);
      virtual bool GetDistanceAndAngle(CBoxEntity* pc_entity, Real& f_distance, CRadians& c_angle);
      virtual bool GetDistanceAndAngle(CCylinderEntity* pc_entity, Real& f_distance, CRadians& c_angle);
      virtual void AddReadings(const Real* pf_readings);

      CEmbodiedEntity::SBoundingBox m_cSensorBoundingBox;

   };
}

#endif

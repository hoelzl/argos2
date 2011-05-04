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
 * @file <argos2/simulator/sensors/foot-bot/footbot_turret_torque_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_TURRET_TORQUE_SENSOR_H
#define FOOTBOT_TURRET_TORQUE_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotTurretTorqueSensor;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_torque_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_actuator.h>
#include <argos2/simulator/sensors/foot-bot/footbot_sensor.h>
#include <argos2/simulator/space/entities/footbot_entity.h>

namespace argos {

   class CFootBotTurretTorqueSensor : public CFootBotSensor,
                                      public CCI_FootBotTurretTorqueSensor{

   public:
      
      CFootBotTurretTorqueSensor();
      virtual ~CFootBotTurretTorqueSensor() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotSensor::SetEntity(c_entity);
      }

      virtual void Update();
      virtual void Reset();

   private:


   };

}

#endif


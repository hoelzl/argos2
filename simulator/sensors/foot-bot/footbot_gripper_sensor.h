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
 * @file <argos2/simulator/sensors/foot-bot/footbot_gripper_sensor.h>
 *
 * @author Giovanni Pini - <gpini@ulb.ac.be>
 */

#ifndef FOOTBOT_GRIPPER_SENSOR_H
#define FOOTBOT_GRIPPER_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotGripperSensor;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_gripper_sensor.h>
#include <argos2/simulator/sensors/foot-bot/footbot_sensor.h>
#include <argos2/simulator/space/entities/footbot_entity.h>

namespace argos {

   class CFootBotGripperSensor : public CFootBotSensor,
                                 public CCI_FootBotGripperSensor{

   public:

      CFootBotGripperSensor() {}
      virtual ~CFootBotGripperSensor() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotSensor::SetEntity(c_entity);
         m_pcGripperEquippedEntity = &(GetEntity().GetGripperEquippedEntity());
      }

      virtual void Update();
      virtual void Reset();

   private:

      CGripperEquippedEntity* m_pcGripperEquippedEntity;

   };

}

#endif


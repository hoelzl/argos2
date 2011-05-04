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
 * @file <argos2/simulator/actuators/foot-bot/footbot_gripper_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_GRIPPER_ACTUATOR_H
#define FOOTBOT_GRIPPER_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotGripperActuator;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_gripper_actuator.h>
#include <argos2/simulator/actuators/foot-bot/footbot_actuator.h>
#include <argos2/simulator/space/entities/footbot_entity.h>

namespace argos {

   class CFootBotGripperActuator : public CFootBotActuator,
                                   public CCI_FootBotGripperActuator {

   public:

      CFootBotGripperActuator() {}
      virtual ~CFootBotGripperActuator() {}

      inline virtual void SetAperture(const CRadians& c_aperture) {
         m_cDesiredAperture = c_aperture;
      }

      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotActuator::SetEntity(c_entity);
         m_pcGripperEquippedEntity = &(GetEntity().GetGripperEquippedEntity());
      }

      virtual void Update();
      virtual void Reset();

   private:

      CRadians m_cDesiredAperture;
      CGripperEquippedEntity* m_pcGripperEquippedEntity;

   };

}

#endif

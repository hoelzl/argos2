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
 * @file <argos2/simulator/actuators/foot-bot/footbot_beacon_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_BEACON_ACTUATOR_H
#define FOOTBOT_BEACON_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotBeaconActuator;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_beacon_actuator.h>
#include <argos2/simulator/actuators/foot-bot/footbot_actuator.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>

namespace argos {

   class CFootBotBeaconActuator : public CFootBotActuator,
                                  public CCI_FootBotBeaconActuator {

   public:

      CFootBotBeaconActuator() {}
      virtual ~CFootBotBeaconActuator() {}

      virtual void Init(TConfigurationNode& t_tree) {}
      virtual void Destroy() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotActuator::SetEntity(c_entity);
         m_pcLEDEquippedEntity = &(GetEntity().GetLEDEquippedEntity());
      }

      inline virtual void SetColor(const CColor& c_color) {
         m_cDesiredColor = c_color;
      }

      virtual void Update();
      virtual void Reset();

   private:

      CLedEquippedEntity* m_pcLEDEquippedEntity;
      CColor m_cDesiredColor;

   };

}

#endif

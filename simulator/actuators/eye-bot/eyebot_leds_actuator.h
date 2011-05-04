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
 * @file <argos2/simulator/actuators/eye-bot/eyebot_leds_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EYEBOT_LEDS_ACTUATOR_H
#define EYEBOT_LEDS_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEyeBotLedsActuator;
}

#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_leds_actuator.h>
#include <argos2/simulator/actuators/eye-bot/eyebot_actuator.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>

namespace argos {

   class CEyeBotLedsActuator : public CEyeBotActuator,
                               public CCI_EyeBotLedsActuator {

   public:

      CEyeBotLedsActuator();
      virtual ~CEyeBotLedsActuator() {}

      virtual void Init(TConfigurationNode& t_tree) {}
      virtual void Destroy() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CEyeBotActuator::SetEntity(c_entity);
         m_pcLedEquippedEntity = &(GetEntity().GetLEDEquippedEntity());
      }

      inline virtual void SetSingleColor(UInt32 un_led_number,
                                         const CColor& c_color) {
         m_tLedSettings[un_led_number] = c_color;
      }

      inline virtual void SetAllColors(const CColor& c_color) {
         /* No for loop - much faster than with */
         m_tLedSettings[0] = c_color;
         m_tLedSettings[1] = c_color;
         m_tLedSettings[2] = c_color;
         m_tLedSettings[3] = c_color;
         m_tLedSettings[4] = c_color;
         m_tLedSettings[5] = c_color;
         m_tLedSettings[6] = c_color;
         m_tLedSettings[7] = c_color;
         m_tLedSettings[8] = c_color;
         m_tLedSettings[9] = c_color;
         m_tLedSettings[10] = c_color;
         m_tLedSettings[11] = c_color;
      }

      inline virtual void SetAllColors(const TLedSettings& c_colors) {
         m_tLedSettings = c_colors;
      }

      inline virtual void EnableRings(const ERingModes& e_mode) {
         m_eMode = e_mode;
      }

      virtual void Update();
      virtual void Reset();

   private:

      CLedEquippedEntity* m_pcLedEquippedEntity;

      CCI_EyeBotLedsActuator::ERingModes m_eMode;

   };

}

#endif

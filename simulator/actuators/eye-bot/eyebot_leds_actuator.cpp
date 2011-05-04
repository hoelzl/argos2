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
 * @file <argos2/simulator/generic_actuators/eye-bot/eyebot_leds_actuator.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "eyebot_leds_actuator.h"
#include <argos2/common/utility/logging/argos_log.h>

namespace argos {

   /****************************************/
   /****************************************/

   CEyeBotLedsActuator::CEyeBotLedsActuator() :
      m_pcLedEquippedEntity(NULL),
      m_eMode() {}
   
   /****************************************/
   /****************************************/

   void CEyeBotLedsActuator::Update()
   {
      if(m_eMode == CCI_EyeBotLedsActuator::BOTH_RINGS_ON) {
         for(UInt32 i = 0; i < CCI_EyeBotLedsActuator::NUM_LEDS; ++i) {
            m_pcLedEquippedEntity->SetLedColor(i+i, m_tLedSettings[i]);
            m_pcLedEquippedEntity->SetLedColor(i+i+1, m_tLedSettings[i]);
         }
      }
      else if(m_eMode == CCI_EyeBotLedsActuator::SIDE_RING_ON) {
         for(UInt32 i = 0; i < CCI_EyeBotLedsActuator::NUM_LEDS; ++i) {
            m_pcLedEquippedEntity->SetLedColor(i+i, m_tLedSettings[i]);
            m_pcLedEquippedEntity->SetLedColor(i+i+1, CColor::BLACK);
         }
      }
      else if(m_eMode == CCI_EyeBotLedsActuator::BOTTOM_RING_ON) {
         for(UInt32 i = 0; i < CCI_EyeBotLedsActuator::NUM_LEDS; ++i) {
            m_pcLedEquippedEntity->SetLedColor(i+i, CColor::BLACK);
            m_pcLedEquippedEntity->SetLedColor(i+i+1, m_tLedSettings[i]);
         }
      }
      else {
         for(UInt32 i = 0; i < CCI_EyeBotLedsActuator::NUM_LEDS; ++i) {
            m_pcLedEquippedEntity->SetLedColor(i+i, CColor::BLACK);
            m_pcLedEquippedEntity->SetLedColor(i+i+1, CColor::BLACK);
         }
      }
   }

   /****************************************/
   /****************************************/

   void CEyeBotLedsActuator::Reset()
   {
      EnableRings(CCI_EyeBotLedsActuator::BOTH_RINGS_ON);
      SetAllColors(CColor::BLACK);
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CEyeBotLedsActuator,
                     "eyebot_leds", "default",
                     "The eye-bot LED actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "This actuator controls the eye-bot LEDs. For a complete description of its\n"
                     "usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <eyebot_leds implementation=\"default\" />\n"
                     "        ...\n"
                     "      </actuators>\n"
                     "      ...\n"
                     "    </my_controller>\n"
                     "    ...\n"
                     "  </controllers>\n\n"
                     "OPTIONAL XML CONFIGURATION\n\n"
                     "None for the time being.\n",
                     "Under development"
      );

}

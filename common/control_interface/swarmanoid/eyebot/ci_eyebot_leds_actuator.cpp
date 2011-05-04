/*
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
 * @file <argos2/common/control_interface/eyebot/ci_eyebot_leds_actuator.h>
 *
 * @brief This file provides the definition of eyebot LEDs actuator.
 *
 * This file provides the definition of eyebot LEDs actuator.
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#include "ci_eyebot_leds_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/

   const UInt32 CCI_EyeBotLedsActuator::NUM_LEDS = 16;

   /****************************************/
   /****************************************/

   CCI_EyeBotLedsActuator::CCI_EyeBotLedsActuator() :
      m_tLedSettings(NUM_LEDS, CColor::BLACK)
   {
   }

   /****************************************/
   /****************************************/

   void CCI_EyeBotLedsActuator::SetAllColors(const TLedSettings& t_colors)
   {
      for(UInt32 i = 0; i < NUM_LEDS; ++i) {
         m_tLedSettings[i] = t_colors[i];
         SetSingleColor(i, m_tLedSettings[i]);
      }
   }

   /****************************************/
   /****************************************/

   void CCI_EyeBotLedsActuator::SetSingleIntensity(UInt32 un_led_number,
                                                   UInt32 un_intensity)
   {
      m_tLedSettings[un_led_number].SetAlpha(un_intensity);

      SetSingleColor(un_led_number, m_tLedSettings[un_led_number]);
   }

   /****************************************/
   /****************************************/

   void CCI_EyeBotLedsActuator::SetAllIntensities(UInt32 un_intensity)
   {
      for (UInt8 i = 0; i < NUM_LEDS; ++i)
         m_tLedSettings[i].SetAlpha(un_intensity);

      SetAllColors(m_tLedSettings);
   }

   /****************************************/
   /****************************************/

}

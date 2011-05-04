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
 * @file <common/control_interface/footbot/ci_footbot_leds_actuator.cpp>
 *
 * @brief This file provides the implementation of footbot LEDs actuator.
 *
 * This file provides the implementation of footbot LEDs actuator.
 *
 * The user can control the color and the intensity of each LED.
 * Intensity s stored in the alpha channel of the color. If the intensity
 * of the (one of the) LEDs is changed, its value is kept in memory
 * also when the color is changed (i.e SetColor(s) methods do not change
 * the intensity).
 * The method that takes a TLedSettings type as parameter, on the other hand,
 * also changes the intensity of the LEDs. It is up to the user to provide
 * a vector of CColor with the desired intensity if the method is called.
 *
 * The LEDs are distributed evenly around the robot, in the same module
 * as the gripper. When the gripper rotates, so do the LEDs. The total
 * number of LEDs is 12 and they are distributed as follows:
 *
 *       00 G 11
 *     01       10
 *   02           09
 *   03           08
 *     04       07
 *        05 06
 *
 * The G depicts the gripper.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Giovanni Pini   - <gpini@iridia.ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#include "ci_footbot_leds_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/

   const UInt8 CCI_FootBotLedsActuator::NUM_LEDS = 12;

   /****************************************/
   /****************************************/

   CCI_FootBotLedsActuator::CCI_FootBotLedsActuator()
   {
       for(UInt32 i = 0; i < NUM_LEDS; ++i) {
           m_tLedSettings.push_back(CColor::BLACK);
       }
   }

   /****************************************/
   /****************************************/

   void CCI_FootBotLedsActuator::SetSingleIntensity(const UInt8 un_led_number, const UInt8 un_intensity)
   {
       m_tLedSettings[un_led_number].SetAlpha(un_intensity);

       SetSingleColor(un_led_number, m_tLedSettings[un_led_number]);
   }

   /****************************************/
   /****************************************/

   void CCI_FootBotLedsActuator::SetAllIntensities(const UInt8 un_intensity)
   {
       for (UInt8 i = 0; i < NUM_LEDS; ++i)
           m_tLedSettings[i].SetAlpha(un_intensity);

       SetAllColors(m_tLedSettings);
   }

   /****************************************/
   /****************************************/

}

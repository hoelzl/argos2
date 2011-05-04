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
 * @file <common/control_interface/e-puck/ci_epuck_leds_actuator.cpp>
 *
 * @brief This file provides the definition of the e-puck LEDs actuator.
 *
 * This file provides the definition of the e-puck LEDs actuator.
 *
 * The user can switch on/off the 8 LEDs around the e-puck.
 * The LEDs are distributed all over the e-puck as follows:
 * (View from the top)
 *
 *        front
 *        0   7    r
 *   l 1         6 i
 *   e             g
 *   f 2         5 h
 *   t    3   4    t
 *        back
 *
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#include "ci_epuck_leds_actuator.h"
#include <argos2/common/utility/logging/argos_log.h>

namespace argos {

   /****************************************/
   /****************************************/

   const UInt16 CCI_EPuckLedsActuator::NUM_LEDS = 8;

   /****************************************/
   /****************************************/

   CCI_EPuckLedsActuator::CCI_EPuckLedsActuator() :
      m_unLedSettings(0) {
   }

   /****************************************/
   /****************************************/

   void CCI_EPuckLedsActuator::SwitchSingleLed(UInt8 un_led_number,
                                               bool b_switched_on) {
      if(b_switched_on) {
         m_unLedSettings |= (128 >> un_led_number);
      }
      else {
         m_unLedSettings &= ~(128 >> un_led_number);
      }
   }

   /****************************************/
   /****************************************/

   void CCI_EPuckLedsActuator::SwitchAllLeds(bool b_switched_on) {
      if(b_switched_on) {
         m_unLedSettings = 255;
      }
      else {
         m_unLedSettings = 0;
      }
   }

   /****************************************/
   /****************************************/

}

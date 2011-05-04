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
 * @file <common/control_interface/e-puck/ci_epuck_leds_actuator.h>
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

#ifndef CCI_EPUCK_LEDS_ACTUATOR_H
#define CCI_EPUCK_LEDS_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EPuckLedsActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

   class CCI_EPuckLedsActuator : virtual public CCI_Actuator {

   public:

      static const UInt16 NUM_LEDS;

      CCI_EPuckLedsActuator();

      virtual ~CCI_EPuckLedsActuator() {
      }

      /**
       * Switches on/off a single LED.
       */
      virtual void SwitchSingleLed(UInt8 un_led_number,
                                   bool b_switched_on);

      /**
       * Switches on/off all LEDs.
       */
      virtual void SwitchAllLeds(bool b_switched_on);

   protected:

      UInt8 m_unLedSettings;

   };

}

#endif

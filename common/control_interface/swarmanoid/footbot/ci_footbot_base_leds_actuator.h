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
 * @file <common/control_interface/footbot/ci_footbot_base_leds_actuator.h>
 *
 * @brief This file provides the definition of footbot LEDs actuator.
 *
 * This file provides the definition of footbot base LEDs actuator.
 *
 * The base LEDs consist of several LEDs which are scattered over the
 * base of the footbot. In detail, they consist of:
 *
 *  1. RGB LED on the ceiling camera (SetCameraLedColor)
 *  2. REB LED on the IMX board (SetImxLedColor)
 *  3. 4 red debugging LEDs (SetDebugLeds)
 *  4. blue LED for Wifi status display (SetWifiStatusLed)
 *  5. orange LED for Wifi transmit display (SetWifiTransmitLed)
 *
 * The user can control the color and the intensity of the first two LEDs.
 * The other LEDs (3-5) can only be switched on or off.
 *
 * The main use of this actuator is to lower the amount of visual noise
 * in an experiment or for debugging.
 *
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_BASE_LEDS_ACTUATOR_H
#define CCI_FOOTBOT_BASE_LEDS_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
    class CCI_FootBotBaseLedsActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>
#include <argos2/common/utility/datatypes/color.h>

namespace argos {

    class CCI_FootBotBaseLedsActuator : virtual public CCI_Actuator {

    public:

        static const UInt8 NUM_DEBUG_LEDS;

        CCI_FootBotBaseLedsActuator() {
        }

        virtual ~CCI_FootBotBaseLedsActuator() {
        }

        virtual void SetCameraLedColor(const CColor& c_color) = 0;
        virtual void SetImxLedColor(const CColor& c_color) = 0;
        virtual void SetDebugLeds(UInt8 un_led_number, const bool b_state) = 0;
        virtual void SetWifiStatusLed(const bool b_state) = 0;
        virtual void SetWifiTransmitLed(const bool b_state) = 0;

    };

}

#endif

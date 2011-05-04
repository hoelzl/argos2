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
 * @file <common/control_interface/footbot/ci_footbot_base_leds_actuator.cpp>
 *
 * @brief This file provides the implementation of footbot base LEDs actuator.
 *
 * This file provides the implementation of footbot base LEDs actuator.
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

#include "ci_footbot_base_leds_actuator.h"

namespace argos {

    /****************************************/
    /****************************************/

    const UInt8 CCI_FootBotBaseLedsActuator::NUM_DEBUG_LEDS = 4;

    /****************************************/
    /****************************************/

}

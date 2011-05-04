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
 * @file <argos2/simulator/actuators/foot-bot/footbot_base_leds_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef FOOTBOT_BASELEDS_ACTUATOR_H
#define FOOTBOT_BASELEDS_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
  class CFootBotBaseLedsActuator;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_base_leds_actuator.h>
#include <argos2/simulator/actuators/foot-bot/footbot_actuator.h>

namespace argos {

  class CFootBotBaseLedsActuator : public CFootBotActuator,
				   public CCI_FootBotBaseLedsActuator {

  public:

    CFootBotBaseLedsActuator() {}
    virtual ~CFootBotBaseLedsActuator() {}

    virtual void Init(TConfigurationNode& t_tree) {}
    virtual void Destroy() {}
    virtual void Update() {};
    virtual void Reset() {};

    virtual void SetCameraLedColor(const CColor& c_color) {};
    virtual void SetImxLedColor(const CColor& c_color) {};
    virtual void SetDebugLeds(UInt8 un_led_number, const bool b_state) {};
    virtual void SetWifiStatusLed(const bool b_state) {};
    virtual void SetWifiTransmitLed(const bool b_state) {};
  };

}

#endif

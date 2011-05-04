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
 * @file <common/control_interface/handbot/ci_handbot_leds_actuator.h>
 *
 * @brief This file provides the common interface implementation of handbot LEDs actuator.
 *
 * This file provides the common interface implementation of handbot LEDs actuator.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "ci_handbot_leds_actuator.h"

namespace argos {

    /****************************************/
    /****************************************/

    const UInt8 CCI_HandBotLedsActuator::NUM_LEDS = 12;

    /****************************************/
    /****************************************/

    CCI_HandBotLedsActuator::CCI_HandBotLedsActuator() :
            m_tLedSettings(NUM_LEDS, CColor::BLACK)
    {
    }

    /****************************************/
    /****************************************/

    void CCI_HandBotLedsActuator::SetSingleIntensity(const UInt8 un_led_number, const UInt8 un_intensity)
    {
        m_tLedSettings[un_led_number].SetAlpha(un_intensity);

        SetSingleColor(un_led_number, m_tLedSettings[un_led_number]);
    }

    /****************************************/
    /****************************************/

    void CCI_HandBotLedsActuator::SetAllIntensities(const UInt8 un_intensity)
    {
        for (UInt8 i = 0; i < NUM_LEDS; ++i)
            m_tLedSettings[i].SetAlpha(un_intensity);

        SetAllColors(m_tLedSettings);
    }

    /****************************************/
    /****************************************/

}

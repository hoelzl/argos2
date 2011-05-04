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
 * @file <argos2/simulator/generic_actuators/foot-bot/footbot_leds_actuator.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "footbot_leds_actuator.h"
#include <argos2/common/utility/logging/argos_log.h>

namespace argos {

    /****************************************/
    /****************************************/

    void CFootBotLedsActuator::Update()
    {
        m_pcLedEquippedEntity->SetAllLedsColors(m_tLedSettings);
    }

    /****************************************/
    /****************************************/

    void CFootBotLedsActuator::Reset()
    {
        SetAllColors(CColor::BLACK);
    }

    /****************************************/
    /****************************************/

    REGISTER_ACTUATOR(CFootBotLedsActuator,
            "footbot_leds", "default",
            "The foot-bot LED actuator",
            "Carlo Pinciroli [cpinciro@ulb.ac.be]",
            "This actuator controls the foot-bot LEDs. For a complete description of its\n"
            "usage, refer to the common interface.\n\n"
            "REQUIRED XML CONFIGURATION\n\n"
            "  <controllers>\n"
            "    ...\n"
            "    <my_controller ...>\n"
            "      ...\n"
            "      <actuators>\n"
            "        ...\n"
            "        <footbot_leds implementation=\"default\" />\n"
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

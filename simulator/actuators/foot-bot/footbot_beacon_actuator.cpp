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
 * @file <argos2/simulator/actuators/foot-bot/footbot_beacon_actuator.cpp>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "footbot_beacon_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/

   void CFootBotBeaconActuator::Update() {
      m_pcLEDEquippedEntity->SetLedColor(12, m_cDesiredColor);
   }

   /****************************************/
   /****************************************/

   void CFootBotBeaconActuator::Reset() {
      m_cDesiredColor = CColor::BLACK;
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CFootBotBeaconActuator,
                     "footbot_beacon", "default",
                     "The foot-bot beacon actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "This actuator controls the foot-bot beacon LED. For a complete description of\n"
                     "its usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <footbot_beacon implementation=\"default\" />\n"
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

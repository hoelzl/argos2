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
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "footbot_base_leds_actuator.h"

namespace argos {

  /****************************************/
  /****************************************/

  REGISTER_ACTUATOR(CFootBotBaseLedsActuator,
		    "footbot_base_leds", "default",
		    "The foot-bot Base LED actuator",
		    "Vito Trianni [vito.trianni@istc.cnr.it]",
		    "This actuator controls the foot-bot LEDs on the base.\n"
		    "REQUIRED XML CONFIGURATION\n\n"
		    "  <controllers>\n"
		    "    ...\n"
		    "    <my_controller ...>\n"
		    "      ...\n"
		    "      <actuators>\n"
		    "        ...\n"
		    "        <footbot_base_leds implementation=\"default\" />\n"
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

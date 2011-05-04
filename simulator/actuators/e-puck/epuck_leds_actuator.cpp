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
 * @file <argos2/simulator/generic_actuators/e-puck/epuck_leds_actuator.cpp>
 *
 * @brief This file provides the implementation of the e-puck LEDs actuator.
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#include "epuck_leds_actuator.h"
#include <argos2/common/utility/logging/argos_log.h>

namespace argos {

   /****************************************/
   /****************************************/

   void CEPuckLedsActuator::Update() {
      UInt8 unMask = 1;
      for(UInt8 i = 0; i < 8; ++i) {
         if(m_unLedSettings & unMask) {
            m_pcLedEquippedEntity->SetLedColor(i, CColor::RED);
         }
         else {
            m_pcLedEquippedEntity->SetLedColor(i, CColor::BLACK);
         }
         unMask <<= 1;
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckLedsActuator::Reset() {
        SwitchAllLeds(false);
    	m_pcLedEquippedEntity->SetLedColor(0,CColor::BLACK);
    	m_pcLedEquippedEntity->SetLedColor(1,CColor::BLACK);
    	m_pcLedEquippedEntity->SetLedColor(2,CColor::BLACK);
    	m_pcLedEquippedEntity->SetLedColor(3,CColor::BLACK);
    	m_pcLedEquippedEntity->SetLedColor(4,CColor::BLACK);
    	m_pcLedEquippedEntity->SetLedColor(5,CColor::BLACK);
    	m_pcLedEquippedEntity->SetLedColor(6,CColor::BLACK);
    	m_pcLedEquippedEntity->SetLedColor(7,CColor::BLACK);
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CEPuckLedsActuator,
                     "epuck_leds", "default",
                     "The e-puck LED actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "This actuator controls the e-puck LEDs. For a complete description of its\n"
                     "usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <epuck_leds implementation=\"default\" />\n"
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

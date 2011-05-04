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
 * @file <argos2/simulator/actuators/foot-bot/footbot_distance_scanner_actuator.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "footbot_distance_scanner_actuator.h"

namespace argos {

	 const Real CFootBotDistanceScannerActuator::RPM_TO_RADIANS_PER_SEC = ARGOS_PI / 30.0f;

   /****************************************/
   /****************************************/

   CFootBotDistanceScannerActuator::CFootBotDistanceScannerActuator() :
      m_fDesiredRotationSpeed(0.0f),
      m_unDesiredMode(CDistanceScannerEquippedEntity::MODE_OFF) {}

   /****************************************/
   /****************************************/

   void CFootBotDistanceScannerActuator::Update() {
      m_pcDistanceScannerEquippedEntity->SetMode(m_unDesiredMode);
      if(m_unDesiredMode == CDistanceScannerEquippedEntity::MODE_POSITION_CONTROL) {
         m_pcDistanceScannerEquippedEntity->SetRotation(m_cDesiredRotation);
      }
      else if(m_unDesiredMode == CDistanceScannerEquippedEntity::MODE_SPEED_CONTROL) {
         m_pcDistanceScannerEquippedEntity->SetRotationSpeed(m_fDesiredRotationSpeed);
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotDistanceScannerActuator::Reset() {
      m_cDesiredRotation = CRadians::ZERO;
      m_fDesiredRotationSpeed = 0.0f;
      m_unDesiredMode = CDistanceScannerEquippedEntity::MODE_OFF;
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CFootBotDistanceScannerActuator,
                     "footbot_distance_scanner", "default",
                     "The foot-bot distance scanner actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "This actuator controls the foot-bot distance scanner. For a complete\n"
                     "description of its usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <footbot_distance_scanner implementation=\"default\" />\n"
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

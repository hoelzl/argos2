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
 * @file <argos2/simulator/generic_actuators/foot-bot/footbot_turret_actuator.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "footbot_turret_actuator.h"
#include <argos2/common/utility/logging/argos_log.h>

/*
 * TODO: find the right conversion from PID pulses to rotational speed
 *
 * The PID values are in the range [0,2]. When the value is set to 2,
 * the turret completes a turn in roughly T = 4 seconds (TODO: measure it better).
 * Therefore, the max speed corresponding to the input value 2 is W = 2*PI / T.
 */

namespace argos {

   /****************************************/
   /****************************************/

   static const Real TIME_TO_COMPLETE_A_TURN = 4.0f;                            // in seconds
   static const Real MAX_TURN_SPEED = 2.0 * ARGOS_PI / TIME_TO_COMPLETE_A_TURN; // in rad/seconds
   static const Real MAX_INPUT_PID_PULSES = 2.0;
   static const Real PIDPULSES_TO_RADIANS = MAX_TURN_SPEED / MAX_INPUT_PID_PULSES;

   /****************************************/
   /****************************************/

   CFootBotTurretActuator::CFootBotTurretActuator() :
      m_fDesiredRotationSpeed(0.0f),
      m_eDesiredMode(CCI_FootBotTurretActuator::MODE_OFF) {}

   /****************************************/
   /****************************************/

   void CFootBotTurretActuator::SetRotationSpeed(SInt32 n_speed_pulses) {
      m_fDesiredRotationSpeed = static_cast<Real>(n_speed_pulses) * PIDPULSES_TO_RADIANS;
   }

   /****************************************/
   /****************************************/

   void CFootBotTurretActuator::Update() {
      GetEntity().SetTurretMode(m_eDesiredMode);
      if(m_eDesiredMode == CCI_FootBotTurretActuator::MODE_POSITION_CONTROL) {
         GetEntity().SetTurretRotation(m_cDesiredRotation);
      }
      else if(m_eDesiredMode == CCI_FootBotTurretActuator::MODE_SPEED_CONTROL) {
         GetEntity().SetTurretRotationSpeed(m_fDesiredRotationSpeed);
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotTurretActuator::Reset() {
      m_cDesiredRotation = CRadians::ZERO;
      m_fDesiredRotationSpeed = 0.0f;
      m_eDesiredMode = CCI_FootBotTurretActuator::MODE_OFF;
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CFootBotTurretActuator,
                     "footbot_turret", "default",
                     "The foot-bot turret actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "This actuator controls the foot-bot turret. For a complete description of its\n"
                     "usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <footbot_turret implementation=\"default\" />\n"
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

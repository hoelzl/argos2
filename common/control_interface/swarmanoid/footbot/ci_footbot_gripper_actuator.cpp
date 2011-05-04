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
 * @file <common/control_interface/footbot/ci_footbot_gripper_actuator.cpp>
 *
 * @brief This file provides the definition of the gripper actuator.

 * This file provides the definition of the gripper actuator. It allows
 * to set the gripper aperture in the range [-90:90] degrees.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "ci_footbot_gripper_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/
   
   CRadians CCI_FootBotGripperActuator::LOCKED_NEGATIVE(-ARGOS_PI * 0.5f);
   CRadians CCI_FootBotGripperActuator::LOCKED_POSITIVE(ARGOS_PI * 0.5f);
   CRadians CCI_FootBotGripperActuator::UNLOCKED(0.0f);
   
   /****************************************/
   /****************************************/

}

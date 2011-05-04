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
 * @file <common/control_interface/swarmanoid/handbot/ci_handbot_arms_actuator.cpp>
 *
 * @brief This file provides the implementation of the common interface to the
 *        handbot arms actuators (head, arms and grippers).
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_arms_actuator.h>

namespace argos {

   /****************************************/
   /****************************************/

   //TODO: Use the CRadians::PI*
   const Real CCI_HandBotArmsActuator::ANGLE_TO_PID_HEAD_ROTATION = 1000.0 / 1.570796327;
   const Real CCI_HandBotArmsActuator::ANGLE_TO_PID_ARMS_APERTURE = 600.0 / 1.047197551;
   const Real CCI_HandBotArmsActuator::ANGLE_TO_PID_GRIPPER_APERTURE = (-1000.0) / 3.141592654;
   const Real CCI_HandBotArmsActuator::ANGLE_TO_PID_GRIPPER_ROTATION = -900.0 / 1.570796327;

   const CRadians CCI_HandBotArmsActuator::ARM_RETRACTED       = CRadians(0.0);
   const CRadians CCI_HandBotArmsActuator::ARM_EXTENDED        = CRadians(1.047197551);
   const CRadians CCI_HandBotArmsActuator::WRIST_STRAIGHT      = CRadians(1.570796327);
   const CRadians CCI_HandBotArmsActuator::WRIST_PERPENDICULAR = CRadians(0.0);
   const CRadians CCI_HandBotArmsActuator::GRIPPER_OPEN        = CRadians(3.141592654);
   const CRadians CCI_HandBotArmsActuator::GRIPPER_CLOSED      = CRadians(0.0);

   /****************************************/
   /****************************************/

}

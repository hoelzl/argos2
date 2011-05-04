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
 * @file <common/control_interface/behavioral_toolkit/swarmanoid/ci_swarmanoid_robot_state.cpp>
 *
 * @brief This file provides the implementation for the behavioral toolkit state of the swarmanoid robots.
 * It is intended to provide all the functionalities that are shared by the swarmanoid robots, such
 * as the range and bearing support
 *
 * @author Giovanni Pini  - <gpini@iridia.ulb.ac.be>
 */

#include "ci_swarmanoid_robot_state.h"

namespace argos{

   /****************************************/
   /****************************************/

   const std::string CCI_SwarmanoidRobotState::RAB_SENSOR_XML_NAME     = "range_and_bearing";
   const std::string CCI_SwarmanoidRobotState::BATTERY_SENSOR_XML_NAME = "battery";
   const std::string CCI_SwarmanoidRobotState::RAB_ACTUATOR_XML_NAME   = "range_and_bearing";

   /****************************************/
   /****************************************/

   void CCI_SwarmanoidRobotState::Init(){

      CCI_RobotState::Init();

      /////////////////////////////////////////////////////////////////
      //   INITIALIZE ALL THE SENSORS DECLARED IN THE XML CONFIGURATION
      /////////////////////////////////////////////////////////////////

      TSensorMap mapSensors = m_pcRobot->GetAllSensors();
      TSensorMap::const_iterator itSensors;

      SENSOR_INIT_HELPER(RAB_SENSOR_XML_NAME, CCI_RangeAndBearingSensor, m_pcRABSensor, m_bIsUsingRABSensor);
      SENSOR_INIT_HELPER(BATTERY_SENSOR_XML_NAME, CCI_BatterySensor, m_pcBatterySensor, m_bIsUsingBatterySensor);

      //Initialize misc sensors variables
      if (m_bIsUsingBatterySensor) {
    	  m_fBatteryMinSafeValue = m_pcBatterySensor->GetMinSafeValue();
      }

      ///////////////////////////////////////////////////////////////////
      //   INITIALIZE ALL THE ACTUATORS DECLARED IN THE XML CONFIGURATION
      ///////////////////////////////////////////////////////////////////

      TActuatorMap mapActuators = m_pcRobot->GetAllActuators();
      TActuatorMap::const_iterator itActuators;

      ACTUATOR_INIT_HELPER(RAB_ACTUATOR_XML_NAME, CCI_RangeAndBearingActuator, m_pcRABActuator, m_bIsUsingRABActuator);

   }

   /****************************************/
   /****************************************/

   void CCI_SwarmanoidRobotState::ApplyState(){

      CCI_RobotState::ApplyState();

      if (m_bIsUsingRABActuator) {
         m_pcRABActuator->SetData(m_tRABPacketDataToSend);
         m_bIsLastRABPacketSent = false;
      }

   }

   /****************************************/
   /****************************************/

   void CCI_SwarmanoidRobotState::ReadState(){

      if (m_bIsUsingRABSensor) {
    	  m_bIsLastRABPacketSent = m_pcRABActuator->IsLastPacketSent();
      }

   }

   /****************************************/
   /****************************************/

}

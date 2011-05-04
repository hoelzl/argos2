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
 * @file <common/control_interface/behavioral_toolkit/ci_robot_state.cpp>
 *
 * @brief This file provides the control interface implementation for the robot
 * state needed by the behavioral toolkit.
 * It is meant to contain the behavioral toolkit implementation that is shared
 * among all the robots (example: clock sensor)
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#include <argos2/common/control_interface/behavioral_toolkit/ci_robot_state.h>

namespace argos {

   /****************************************/
   /****************************************/

   const std::string CCI_RobotState::CLOCK_SENSOR_XML_NAME = "clock";

   /****************************************/
   /****************************************/

   void CCI_RobotState::Init(){
	  TSensorMap mapSensors = m_pcRobot->GetAllSensors();
	  TSensorMap::const_iterator itSensors;

      SENSOR_INIT_HELPER(CLOCK_SENSOR_XML_NAME, CCI_ClockSensor, m_pcClockSensor, m_bIsUsingClockSensor);

      if (m_bIsUsingClockSensor) {
    	  m_fClockTickLength = m_pcClockSensor->GetClockTickLength();
      }
   }

   /****************************************/
   /****************************************/

   void CCI_RobotState::ApplyState(){
   }

   /****************************************/
   /****************************************/

}


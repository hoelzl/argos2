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
 * @file <common/control_interface/sbot/ci_sbot_gripper_actuator.cpp>
 *
 * @brief This file provides the definition of
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_sbot_gripper_sensor.h"
#include <argos2/common/utility/string_utilities.h>

const string CONFIGURATION_GRIPPER_MINAPERTURE             = "min_aperture";
const string CONFIGURATION_GRIPPER_MAXAPERTURE             = "max_aperture";
const string CONFIGURATION_GRIPPER_MINELEVATION            = "min_elevation";
const string CONFIGURATION_GRIPPER_MAXELEVATION            = "max_elevation";
const string CONFIGURATION_GRIPPER_MINELEVATIONTORQUE      = "min_elevation_torque";
const string CONFIGURATION_GRIPPER_MAXELEVATIONTORQUE      = "max_elevation_torque";
const string CONFIGURATION_GRIPPER_MINELEVATIONMOTORTORQUE = "min_elevation_motor_torque";
const string CONFIGURATION_GRIPPER_MAXELEVATIONMOTORTORQUE = "max_elevation_motor_torque";


/****************************************/
/****************************************/

CCI_SBotGripperSensor::CCI_SBotGripperSensor() {
  m_fMinAperture = 0.0;
  m_fMaxAperture = 1.0;

  m_fMinElevation = 0.0;
  m_fMaxElevation = 1.0;

  m_fMinElevationTorque = 0.0;
  m_fMaxElevationTorque = 1.0;

  m_fMinElevationMotorTorque = 0.0;
  m_fMaxElevationMotorTorque = 1.0;
}


/****************************************/
/****************************************/

CCI_SBotGripperSensor::~CCI_SBotGripperSensor() {

}


/****************************************/
/****************************************/

int CCI_SBotGripperSensor::Init( const TConfigurationTree t_configuration_tree ) {

  string s_minaperture = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MINAPERTURE );
  if( (s_minaperture != "") &&
      (StringToDouble( s_minaperture, m_fMinAperture ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MINAPERTURE << "> tag: '"
				 << s_minaperture << "'" << endl;
    return -1;
  }

  string s_maxaperture = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MAXAPERTURE );
  if( (s_maxaperture != "") &&
      (StringToDouble( s_maxaperture, m_fMaxAperture ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MAXAPERTURE << "> tag: '"
				 << s_maxaperture << "'" << endl;
    return -1;
  }

  string s_minelevation = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MINELEVATION );
  if( (s_minelevation != "") &&
      (StringToDouble( s_minelevation, m_fMinElevation ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MINELEVATION << "> tag: '"
				 << s_minelevation << "'" << endl;
    return -1;
  }

  string s_maxelevation = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MAXELEVATION );
  if( (s_maxelevation != "") &&
      (StringToDouble( s_maxelevation, m_fMaxElevation ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MAXELEVATION << "> tag: '"
				 << s_maxelevation << "'" << endl;
    return -1;
  }

  string s_minelevationtorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MINELEVATIONTORQUE );
  if( (s_minelevationtorque != "") &&
      (StringToDouble( s_minelevationtorque, m_fMinElevationTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MINELEVATIONTORQUE << "> tag: '"
				 << s_minelevationtorque << "'" << endl;
    return -1;
  }

  string s_maxelevationtorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MAXELEVATIONTORQUE );
  if( (s_maxelevationtorque != "") &&
      (StringToDouble( s_maxelevationtorque, m_fMaxElevationTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MAXELEVATIONTORQUE << "> tag: '"
				 << s_maxelevationtorque << "'" << endl;
    return -1;
  }

  string s_minelevationmotortorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MINELEVATIONMOTORTORQUE );
  if( (s_minelevationmotortorque != "") &&
      (StringToDouble( s_minelevationmotortorque, m_fMinElevationMotorTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MINELEVATIONMOTORTORQUE << "> tag: '"
				 << s_minelevationmotortorque << "'" << endl;
    return -1;
  }

  string s_maxelevationmotortorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MAXELEVATIONMOTORTORQUE );
  if( (s_maxelevationmotortorque != "") &&
      (StringToDouble( s_maxelevationmotortorque, m_fMaxElevationMotorTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
				 << CONFIGURATION_GRIPPER_MAXELEVATIONMOTORTORQUE << "> tag: '"
				 << s_maxelevationmotortorque << "'" << endl;
    return -1;
  }

  return 0;
}


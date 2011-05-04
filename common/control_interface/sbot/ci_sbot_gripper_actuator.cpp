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
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "ci_sbot_gripper_actuator.h"
#include <argos2/common/utility/string_utilities.h>


using namespace argos;

Real CCI_SBotGripperActuator::SBOT_GRIPPER_OPEN               = 1.0;  // rad
Real CCI_SBotGripperActuator::SBOT_GRIPPER_CLOSED             = 0.0;  // rad
Real CCI_SBotGripperActuator::SBOT_GRIPPER_OBJECT_GRIPPED     = 0.30; // rad
Real CCI_SBotGripperActuator::SBOT_GRIPPER_OBJECT_RELEASED    = 0.35; // rad
Real CCI_SBotGripperActuator::SBOT_GRIPPER_APERTURE_DEFAULT   = 0.45; // rad
Real CCI_SBotGripperActuator::SBOT_GRIPPER_APERTURE_MAX_SPEED = 0.4;  // rad/s


const string CONFIGURATION_GRIPPER_MINAPERTURE             = "max_aperture";
const string CONFIGURATION_GRIPPER_MAXAPERTURE             = "max_aperture";
const string CONFIGURATION_GRIPPER_MINELEVATION            = "max_elevation";
const string CONFIGURATION_GRIPPER_MAXELEVATION            = "max_elevation";
const string CONFIGURATION_GRIPPER_MINAPERTURETORQUE       = "max_aperture_torque";
const string CONFIGURATION_GRIPPER_MAXAPERTURETORQUE       = "max_aperture_torque";
const string CONFIGURATION_GRIPPER_THRESHOLD_APERTURE      = "threshold_aperture";

/****************************************/
/****************************************/

CCI_SBotGripperActuator::CCI_SBotGripperActuator() {
  m_fMinAperture = 0.0;
  m_fMaxAperture = 1.0;
  m_fThresholdAperture[0] = 0.0;
  m_fThresholdAperture[1] = 0.0;
  
  m_fMinElevation = 0.0;
  m_fMaxElevation = 1.0;
  
  m_fMinApertureTorque = 0.0;
  m_fMaxApertureTorque = 1.0;

  m_bUseThresholdAperture = false;
}


/****************************************/
/****************************************/

CCI_SBotGripperActuator::~CCI_SBotGripperActuator() {

}


/****************************************/
/****************************************/

int CCI_SBotGripperActuator::Init( const TConfigurationTree t_configuration_tree ) {

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

  string s_minaperturetorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MINAPERTURETORQUE );
  if( (s_minaperturetorque != "") &&
      (StringToDouble( s_minaperturetorque, m_fMinApertureTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <" 
				 << CONFIGURATION_GRIPPER_MINAPERTURETORQUE << "> tag: '" 
				 << s_minaperturetorque << "'" << endl;
    return -1;
  }

  string s_maxaperturetorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_MAXAPERTURETORQUE );
  if( (s_maxaperturetorque != "") &&
      (StringToDouble( s_maxaperturetorque, m_fMaxApertureTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <" 
				 << CONFIGURATION_GRIPPER_MAXAPERTURETORQUE << "> tag: '" 
				 << s_maxaperturetorque << "'" << endl;
    return -1;
  }


  string s_thresholdaperture = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_GRIPPER_THRESHOLD_APERTURE );
  if( s_thresholdaperture != "" ) {
    if(CExperimentConfiguration::GetNReals( s_thresholdaperture, m_fThresholdAperture, 2 ) != -1) {
      if( m_fThresholdAperture[0] > m_fThresholdAperture[1] ) {
	CSwarmanoidLogger::LogErr( ) << "[FATAL] Error in values of <" 
				     << CONFIGURATION_GRIPPER_THRESHOLD_APERTURE << ">  "
				     << "first threshold ("<< m_fThresholdAperture[0] 
				     << ") must be less or equal than second  ("<< m_fThresholdAperture[1] << ") " << endl;
	return -1;
      }

      m_bUseThresholdAperture = true;
    }
    else {
      CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <" 
				   << CONFIGURATION_GRIPPER_THRESHOLD_APERTURE << "> tag: '" 
				   << s_thresholdaperture << "'" << endl;
      return -1;
    }
  }

  return 0;
}


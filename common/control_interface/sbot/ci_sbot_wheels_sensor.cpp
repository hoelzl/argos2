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
 * @file <common/control_interface/sbot/ci_sbot_wheels_actuator.cpp>
 *
 * @brief This file provides the definition of the sbot wheels sensor.
 * The Sbot Wheels Sensor groups all sensor values specific to the sbot wheels.
 * These values are:
 *  - angular velocity of each wheel (as set by the controller)
 *  - position of each wheel (as read from the encoder sensor)
 *  - torque of each wheel (as read from the torque sensor)
 * Min and max values can be overridden by the XML (see code for tag names).
 *
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_sbot_wheels_sensor.h"
#include "ci_sbot_wheels_actuator.h"
#include <argos2/common/utility/swarmanoid_math.h>
#include <argos2/common/utility/string_utilities.h>

const string CONFIGURATION_WHEELS_MINSPEED    = "min_speed";
const string CONFIGURATION_WHEELS_MAXSPEED    = "max_speed";
const string CONFIGURATION_WHEELS_MINPOSITION = "min_position";
const string CONFIGURATION_WHEELS_MAXPOSITION = "max_position";
const string CONFIGURATION_WHEELS_MINTORQUE   = "min_torque";
const string CONFIGURATION_WHEELS_MAXTORQUE   = "max_torque";


const unsigned int CCI_SBotWheelsSensor::LEFT_WHEEL = 0;
const unsigned int CCI_SBotWheelsSensor::RIGHT_WHEEL = 1;


/****************************************/
/****************************************/

CCI_SBotWheelsSensor::CCI_SBotWheelsSensor() {
  m_fMinSpeed = 0.0;
  m_fMaxSpeed = CCI_SBotWheelsActuator::MAX_ABSOLUTE_SPEED;

  m_fMinPosition = 0.0;
  m_fMaxPosition = TWO_PI;

  m_fMinTorque = 0.0;
  m_fMaxTorque = 100.0;
}


/****************************************/
/****************************************/

CCI_SBotWheelsSensor::~CCI_SBotWheelsSensor() {

}


/****************************************/
/****************************************/

int CCI_SBotWheelsSensor::Init( const TConfigurationTree t_configuration_tree ) {

  string s_minspeed = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_WHEELS_MINSPEED );
  if( (s_minspeed != "") && (StringToDouble( s_minspeed, m_fMinSpeed ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
                                 << CONFIGURATION_WHEELS_MINSPEED << "> tag: '"
                                 << s_minspeed << "'" << endl;
    return -1;
  }

  string s_maxspeed = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_WHEELS_MAXSPEED );
  if( (s_maxspeed != "") && (StringToDouble( s_maxspeed, m_fMaxSpeed ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
                                 << CONFIGURATION_WHEELS_MAXSPEED << "> tag: '"
                                 << s_maxspeed << "'" << endl;
    return -1;
  }

  string s_minposition = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_WHEELS_MINPOSITION );
  if( (s_minposition != "") && (StringToDouble( s_minposition, m_fMinPosition ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
                                 << CONFIGURATION_WHEELS_MINPOSITION << "> tag: '"
                                 << s_minposition << "'" << endl;
    return -1;
  }

  string s_maxposition = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_WHEELS_MAXPOSITION );
  if( (s_maxposition != "") && (StringToDouble( s_maxposition, m_fMaxPosition ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
                                 << CONFIGURATION_WHEELS_MAXPOSITION << "> tag: '"
                                 << s_maxposition << "'" << endl;
    return -1;
  }

  string s_mintorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_WHEELS_MINTORQUE );
  if( (s_mintorque != "") && (StringToDouble( s_mintorque, m_fMinTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
                                 << CONFIGURATION_WHEELS_MINTORQUE << "> tag: '"
                                 << s_mintorque << "'" << endl;
    return -1;
  }

  string s_maxtorque = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_WHEELS_MAXTORQUE );
  if( (s_maxtorque != "") && (StringToDouble( s_maxtorque, m_fMaxTorque ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Error converting value of <"
                                 << CONFIGURATION_WHEELS_MAXTORQUE << "> tag: '"
                                 << s_maxtorque << "'" << endl;
    return -1;
  }


  return 0;
}


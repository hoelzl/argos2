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
 * @file <common/control_interface/sbot/ci_sbot_turret_rotation_sensor.cpp>
 *
 * @brief This file provides the definition of
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_sbot_turret_rotation_sensor.h"

#include <math.h>
#include <argos2/common/utility/swarmanoid_math.h>

const string CONFIGURATION_SBOT_TURRETROTATION_ENCODING = "encoding";

/****************************************/
/****************************************/

CCI_SBotTurretRotationSensor::CCI_SBotTurretRotationSensor() {
  SetSensorMinValue( -M_PI );
  SetSensorMaxValue( M_PI );
}


/****************************************/
/****************************************/

int CCI_SBotTurretRotationSensor::Init( const TConfigurationTree t_configuration_tree ) {
  if( CCI_Sensor::Init( t_configuration_tree ) != 0 ) return -1;

  // intialise the configuration tree iterator and get the sensor type
  TConfigurationTree::iterator it_root = t_configuration_tree.begin( );
  string s_sensor = it_root->GetNodeName();

  ////////////////////////////////////////////////////////////////////////////////
  // init the sensor encoding configuration: one can choose 'raw'
  // (default) or 'sector' readings.
  ////////////////////////////////////////////////////////////////////////////////
  m_sTurretRotationEncoding = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_SBOT_TURRETROTATION_ENCODING );
  if( (m_sTurretRotationEncoding != "raw") &&
      (m_sTurretRotationEncoding != "invert") ) {
    CSwarmanoidLogger::LogErr( ) << "[WARNING] Could not recognise value '" << m_sTurretRotationEncoding << "' for tag <" << CONFIGURATION_SBOT_TURRETROTATION_ENCODING << ">" << endl;
    CSwarmanoidLogger::LogErr( ) << "[WARNING] using 'raw' encoding" << endl;
    m_sTurretRotationEncoding = "raw";
  }

  ////////////////////////////////////////////////////////////////////////////////
  // Everything ok, return 0
  ////////////////////////////////////////////////////////////////////////////////
  return 0;
}


/****************************************/
/****************************************/

unsigned int CCI_SBotTurretRotationSensor::GetNumberOfEncodedReadings( void ) {
  if( m_sTurretRotationEncoding == "raw" ) {
    return 1;
  }

  if( m_sTurretRotationEncoding == "invert" ) {
    return 1;
  }

  return 0;
}


/****************************************/
/****************************************/

void CCI_SBotTurretRotationSensor::EncodeTurretRotation( Real* pf_buffer ) {
  if( m_sTurretRotationEncoding == "raw" ) {
    pf_buffer[0] = NormalizeSignedAngle(GetTurretRotation());
    return;
  }

  if( m_sTurretRotationEncoding == "invert" ) {
    pf_buffer[0] = NormalizeSignedAngle(GetTurretRotation(false));
    return;
  }
}


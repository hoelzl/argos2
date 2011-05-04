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
 * @file <common/control_interface/ci_sbot_traction_sensor.cpp>
 *
 * @brief This file provides the control interface for the sbot traction sensor
 * 
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_sbot_traction_sensor.h"
#include <argos2/common/utility/swarmanoid_math.h>

using namespace argos;
using namespace std;


const string CONFIGURATION_SBOT_TRACTION_ENCODING    = "encoding";

/****************************************/
/****************************************/

CCI_SBotTractionSensor::CCI_SBotTractionSensor() {
}


/****************************************/
/****************************************/

CCI_SBotTractionSensor::~CCI_SBotTractionSensor() {

}


/****************************************/
/****************************************/

int CCI_SBotTractionSensor::Init( const TConfigurationTree t_configuration_tree ) {
  if( CCI_Sensor::Init( t_configuration_tree ) != 0 ) return -1;

  // intialise the configuration tree iterator and get the sensor type
  TConfigurationTree::iterator it_root = t_configuration_tree.begin( );
  string s_sensor = it_root->GetNodeName();
  
  ////////////////////////////////////////////////////////////////////////////////
  // init the sensor encoding configuration: one can choose 'raw'
  // (default) or 'sector' readings. 
  ////////////////////////////////////////////////////////////////////////////////
  m_sTractionEncoding = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_SBOT_TRACTION_ENCODING );
  if( (m_sTractionEncoding != "raw") &&
      (m_sTractionEncoding != "angle-intensity") &&
      (m_sTractionEncoding != "turret-angle-intensity") &&
      (m_sTractionEncoding != "chassis-rotation") &&
      (m_sTractionEncoding != "sector") ) {
    CSwarmanoidLogger::LogErr( ) << "[WARNING] Could not recognise value '" << m_sTractionEncoding << "' for tag <" << CONFIGURATION_SBOT_TRACTION_ENCODING << ">" << endl;
    CSwarmanoidLogger::LogErr( ) << "[WARNING] using 'raw' encoding" << endl;
    m_sTractionEncoding = "raw";
  }
  
  ////////////////////////////////////////////////////////////////////////////////
  // Everything ok, return 0
  ////////////////////////////////////////////////////////////////////////////////
  return 0;  
}


/****************************************/
/****************************************/

unsigned int CCI_SBotTractionSensor::GetNumberOfEncodedReadings( void ) {
  if( (m_sTractionEncoding == "raw") ||
      (m_sTractionEncoding == "angle-intensity") ||
      (m_sTractionEncoding == "turret-angle-intensity") ||
      (m_sTractionEncoding == "chassis-rotation") ) {
    return 2;
  }
  
  if( m_sTractionEncoding == "sector" ) {
    return 4;
  }
  
  return 0;
}


/****************************************/
/****************************************/

void CCI_SBotTractionSensor::EncodeRawTraction( Real* pf_buffer ) {
  TVector2D raw_traction;
  if( (m_sTractionEncoding == "turret-angle-intensity") ||
      (m_sTractionEncoding == "chassis-rotation") ) {
    GetSBotTraction( &raw_traction.x, & raw_traction.y, false );    
  }
  else {
    GetSBotTraction( &raw_traction.x, & raw_traction.y );    
  }

  if( m_sTractionEncoding == "raw" ) {
    pf_buffer[0] = raw_traction.x;
    pf_buffer[1] = raw_traction.y;
    return;
  }
  
  if( (m_sTractionEncoding == "angle-intensity") || (m_sTractionEncoding == "turret-angle-intensity") ) {
    pf_buffer[0] = LengthVector2D(raw_traction);
    pf_buffer[1] = (OwnAngleVector2D(raw_traction)+M_PI)/(2.0*M_PI)*GetSensorMaxValue();
    return;
  }
  
  if( m_sTractionEncoding == "chassis-rotation" ) {
    Real traction_intensity = LengthVector2D( raw_traction );
    Real traction_angle     = NormalizeSignedAngle( OwnAngleVector2D( raw_traction ) );
    Real chassis_angle      = NormalizeSignedAngle( GetSBotChassisRotation() );
    Real angle_difference   = (chassis_angle - traction_angle)/(2.0*M_PI);

    pf_buffer[0] = angle_difference >= 0 ?  angle_difference*traction_intensity : 0;
    pf_buffer[1] = angle_difference <  0 ? -angle_difference*traction_intensity : 0;
    return;
  }


  if( m_sTractionEncoding == "sector" ) {
    // Now set the outputs:
    if( raw_traction.y >= 0 ) {
      pf_buffer[0] = raw_traction.y;
      pf_buffer[2] = 0.0;
    } 
    else {
      pf_buffer[2] = -raw_traction.y;
      pf_buffer[0] = 0.0;
    }
    
    if( raw_traction.x >= 0 ) {
      pf_buffer[1] = raw_traction.x;
      pf_buffer[3] = 0.0;
    } 
    else {
      pf_buffer[3] = -raw_traction.x;
      pf_buffer[1] = 0.0;
    }   
  }
}


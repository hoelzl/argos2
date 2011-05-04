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
 * @file <common/control_interface/ci_sbot_binary_sound_sensor.cpp>
 *
 * @brief This file provides the control interface for the sbot binary sound sensors
 * 
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_sbot_binary_sound_sensor.h"
#include <argos2/common/utility/string_utilities.h>

using namespace argos;
using namespace std;


const string CONFIGURATION_SBOTBINARYSOUND_NUM_FREQUENCIES     = "num_frequencies";
const string CONFIGURATION_SBOTBINARYSOUND_TARGET_FREQUENCIES  = "target_frequencies";
const string CONFIGURATION_SBOTBINARYSOUND_INTENSITY_THRESHOLD = "intensity_threshold";
const string CONFIGURATION_SBOTBINARYSOUND_FFT_PRECISION       = "fft_precision";


Real CCI_SBotBinarySoundSensor::BASE_FFT_FREQUENCY = 86.1328125;

/****************************************/
/****************************************/

CCI_SBotBinarySoundSensor::CCI_SBotBinarySoundSensor() {
  m_unNumTargetFrequencies = 1;
  m_pfTargetFrequencies    = NULL;
  m_fIntensityThreshold    = 100;
  m_unFFTLogPrecision      = 9;
}


/****************************************/
/****************************************/

CCI_SBotBinarySoundSensor::~CCI_SBotBinarySoundSensor() {
  if( m_pfTargetFrequencies != NULL ) delete [] m_pfTargetFrequencies;
}


/****************************************/
/****************************************/

int CCI_SBotBinarySoundSensor::Init( const TConfigurationTree t_configuration_tree ) {
  if( CCI_Sensor::Init( t_configuration_tree ) != 0 ) return -1;

  ////////////////////////////////////////////////////////////////////////////////
  // Load number of frequencies
  ////////////////////////////////////////////////////////////////////////////////
  string s_num_frequencies = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_SBOTBINARYSOUND_NUM_FREQUENCIES );
  if( (s_num_frequencies != "") && (StringToUnsignedInt( s_num_frequencies, m_unNumTargetFrequencies ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_SBOTBINARYSOUND_NUM_FREQUENCIES
				 << ">" << s_num_frequencies << " to a valid number" << endl;
    return -1;
  }

  if( m_unNumTargetFrequencies == 0 ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Cannot initialise binary sound sensor with 0 target frequencies" << endl;
    return -1;
  }
  
  ////////////////////////////////////////////////////////////////////////////////
  // init target frequencies vector
  ////////////////////////////////////////////////////////////////////////////////
  m_pfTargetFrequencies = new Real[m_unNumTargetFrequencies];

  ////////////////////////////////////////////////////////////////////////////////
  // Load all tartget frequencies
  ////////////////////////////////////////////////////////////////////////////////
  string s_target_frequencies = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_SBOTBINARYSOUND_TARGET_FREQUENCIES );
  if( s_target_frequencies == "" ) {
    if( m_unNumTargetFrequencies != 1 ) {
      CSwarmanoidLogger::LogErr( ) << "[FATAL] Cannot allocate more than one default frequency" << endl;
      return -1;
    }

    m_pfTargetFrequencies[0] = 1000; // defalt frequency
  }
  else if( CExperimentConfiguration::GetNReals( s_target_frequencies, m_pfTargetFrequencies, m_unNumTargetFrequencies ) == -1 ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_SBOTBINARYSOUND_TARGET_FREQUENCIES
				 << ">" << s_target_frequencies << " to valid numbers" << endl;
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////////////
  // Load intensity threshold
  ////////////////////////////////////////////////////////////////////////////////
  string s_intensity_threshold = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_SBOTBINARYSOUND_INTENSITY_THRESHOLD );
  if( (s_intensity_threshold != "") && (StringToDouble( s_intensity_threshold, m_fIntensityThreshold ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_SBOTBINARYSOUND_INTENSITY_THRESHOLD
				 << ">" << s_intensity_threshold << " to a valid number" << endl;
    return -1;
  }
  

  ////////////////////////////////////////////////////////////////////////////////
  // Load fft precision
  ////////////////////////////////////////////////////////////////////////////////
  string s_fft_precision = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_SBOTBINARYSOUND_FFT_PRECISION );
  if( (s_fft_precision != "") && (StringToUnsignedInt( s_fft_precision, m_unFFTLogPrecision ) == -1) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_SBOTBINARYSOUND_FFT_PRECISION
				 << ">" << s_fft_precision << " to a valid number" << endl;
    return -1;
  }
  

  return 0;
}

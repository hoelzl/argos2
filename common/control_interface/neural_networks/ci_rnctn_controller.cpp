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
 * @file <common/control_interface/ci_ctrnn_multilayer_controller.cpp>
 *
 * @brief This file provides the definition of the CTRNN multilayer
 * neural network controller
 * 
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_rnctn_controller.h"
#include <argos2/common/utility/string_utilities.h>

using namespace argos;


const string CONFIGURATION_RNCTN_NUMHIDDEN = "num_hidden";
const string CONFIGURATION_RNCTN_TIMESTEP  = "integration_step";
const string CONFIGURATION_RNCTN_WEIGHTS   = "weight_range";
const string CONFIGURATION_RNCTN_BIASES    = "bias_range";
const string CONFIGURATION_RNCTN_TAUS      = "tau_range";

CCI_RnctnController::CCI_RnctnController() 
  : CCI_NeuralNetworkController() {
  m_pfInput2HiddenWeights   = NULL;
  m_pfCTN2CTNWeights        = NULL;
  
  m_pfCTNBiases             = NULL;
  m_pfCTNTaus               = NULL;
  m_pfCTNDeltaStates        = NULL;
  m_pfCTNStates             = NULL;

  m_unNumCTNs               = 0;
  m_unNumHidden             = 0;
  m_fTimeStep               = 0.1;

  m_fWeightsBounds[0]       = -4.0;
  m_fWeightsBounds[1]       =  4.0;
  m_fBiasesBounds[0]        = -4.0;
  m_fBiasesBounds[1]        =  4.0;
  m_fTausBounds[0]          = -1.0;
  m_fTausBounds[1]          =  3.0;
}


/****************************************/
/****************************************/

CCI_RnctnController::~CCI_RnctnController() {
}


/****************************************/
/****************************************/

int CCI_RnctnController::Init( const TConfigurationTree t_configuration_tree ) {
  ////////////////////////////////////////////////////////////////////////////////
  // First perform common initialisation from base class
  ////////////////////////////////////////////////////////////////////////////////
  if( CCI_NeuralNetworkController::Init( t_configuration_tree ) != 0 )
    return -1;
  

  ////////////////////////////////////////////////////////////////////////////////
  // Load number of hidden nodes
  ////////////////////////////////////////////////////////////////////////////////
  string s_num_hidden = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_RNCTN_NUMHIDDEN );
  if( s_num_hidden == "" ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Missing required tag <" << CONFIGURATION_RNCTN_NUMHIDDEN << ">" 
				 << " for RNCTN multi-layer initialisation" << endl;
    return -1;
  }

  if( StringToUnsignedInt( s_num_hidden, m_unNumHidden ) != 0 ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_RNCTN_NUMHIDDEN
				 << ">" << s_num_hidden << " to a valid number" << endl;
    return -1;
  }
  
  // compute the number of continuous time neurons as the sum of
  // hidden and output neurons
  m_unNumCTNs = m_unNumHidden + m_unNumberOfOutputs;


  ////////////////////////////////////////////////////////////////////////////////
  // integration step
  ////////////////////////////////////////////////////////////////////////////////
  string s_step_size = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_RNCTN_TIMESTEP );
  if( (s_step_size != "") && (StringToDouble( s_step_size, m_fTimeStep ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_RNCTN_TIMESTEP
				 << ">" << s_step_size << " to a valid number" << endl;
    return -1;
  }
  

  ////////////////////////////////////////////////////////////////////////////////
  // Load upper and lower bounds for weigths, biases and taus
  ////////////////////////////////////////////////////////////////////////////////
  string s_weights_bounds = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_RNCTN_WEIGHTS );
  if( (s_weights_bounds != "") && 
      (CExperimentConfiguration::GetNReals( s_weights_bounds, m_fWeightsBounds, 2 ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_RNCTN_WEIGHTS
				 << ">" << s_weights_bounds << " to valid numbers" << endl;
    return -1;
  }

  string s_biases_bounds = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_RNCTN_BIASES );
  if( (s_biases_bounds != "") && 
      (CExperimentConfiguration::GetNReals( s_biases_bounds, m_fBiasesBounds, 2 ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_RNCTN_BIASES
				 << ">" << s_biases_bounds << " to valid numbers" << endl;
    return -1;
  }

  string s_taus_bounds = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_RNCTN_TAUS );
  if( (s_taus_bounds != "") && 
      (CExperimentConfiguration::GetNReals( s_taus_bounds, m_fTausBounds, 2 ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_RNCTN_TAUS
				 << ">" << s_taus_bounds << " to valid numbers" << endl;
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////////////
  // check and load parameters from file
  ////////////////////////////////////////////////////////////////////////////////
  if( (m_sParamterFile != "") && (LoadNetworkParamters( m_sParamterFile ) != 0) ) 
    return -1;

  return CCI_Controller::RETURN_OK;
}

/****************************************/
/****************************************/

void CCI_RnctnController::Destroy() {
  if( m_pfInput2HiddenWeights ) delete[] m_pfInput2HiddenWeights;
  if( m_pfCTN2CTNWeights )      delete[] m_pfCTN2CTNWeights;
  if( m_pfCTNBiases )           delete[] m_pfCTNBiases;
  if( m_pfCTNTaus )             delete[] m_pfCTNTaus;
  if( m_pfCTNDeltaStates )      delete[] m_pfCTNDeltaStates;
  if( m_pfCTNStates )           delete[] m_pfCTNStates;
}


/****************************************/
/****************************************/

int CCI_RnctnController::LoadNetworkParamters( const string filename ) {
  // open the input file
  ifstream in( filename.c_str(), ios::in );
  if( !in ) {
    CSwarmanoidLogger::LogErr() << "[FATAL] Cannot open file '" << filename << "' for reading" << endl;    
    return -1;
  }

  // first parameter is the number of real-valued weights
  unsigned int un_length = 0;
  if( !(in >> un_length) ) {
    CSwarmanoidLogger::LogErr() << "[FATAL] Cannot read data from file '" << filename << "'" << endl;    
    return -1;
  }
  
  // create weights vector and load it from file
  Real* pfGenes = new Real[un_length];
  for( unsigned int i = 0; i < un_length; i++ ) {
    if( !(in >> pfGenes[i]) ) {
      CSwarmanoidLogger::LogErr() << "[FATAL] Cannot read data from file '" << filename << "'" << endl;          
      delete [] pfGenes;
      return -1;
    }
  }

  // load parameters in the appropriate structures
  if( LoadNetworkParamters( un_length, pfGenes ) != 0 ) {
    delete [] pfGenes;
    return -1;
  }

  delete [] pfGenes;
  return 0;
}


/****************************************/
/****************************************/

int CCI_RnctnController::LoadNetworkParamters( const unsigned int un_num_params, const Real* params ) {
  // check consistency between paramter file and xml declaration
  unsigned int un_num_parameters = 
    m_unNumberOfInputs * m_unNumHidden +   // weights of the input -> hidden layer
    m_unNumCTNs * m_unNumCTNs +                      // wigths of the fully recurrent layer
    m_unNumCTNs * 2;                                 // recurrent layer taus and biases
  

  if( un_num_params != un_num_parameters ) {
    CSwarmanoidLogger::LogErr() << "[FATAL] Number of paramter mismatch: '" 
				<< "passed " << un_num_params << " paramters, while " 
				<< un_num_parameters << " were expected from the xml configuration file" << endl;
    return -1;
  }

  if( m_pfInput2HiddenWeights ) delete[] m_pfInput2HiddenWeights;
  if( m_pfCTN2CTNWeights )      delete[] m_pfCTN2CTNWeights;
  if( m_pfCTNBiases )           delete[] m_pfCTNBiases;
  if( m_pfCTNTaus )             delete[] m_pfCTNTaus;
  if( m_pfCTNDeltaStates )      delete[] m_pfCTNDeltaStates;
  if( m_pfCTNStates )           delete[] m_pfCTNStates;

  unsigned int unChromosomePosition = 0;
  
  m_pfInput2HiddenWeights = new Real[m_unNumberOfInputs * m_unNumHidden];
  for( unsigned int i = 0; i < m_unNumberOfInputs * m_unNumHidden; i++ ) {
    m_pfInput2HiddenWeights[i] = params[unChromosomePosition++]*(m_fWeightsBounds[1] - m_fWeightsBounds[0]) + m_fWeightsBounds[0];
  }

  m_pfCTN2CTNWeights = new Real[m_unNumCTNs * m_unNumCTNs];
  for( unsigned int i = 0; i < m_unNumCTNs * m_unNumCTNs; i++ ) {
    m_pfCTN2CTNWeights[i] = params[unChromosomePosition++]*(m_fWeightsBounds[1] - m_fWeightsBounds[0]) + m_fWeightsBounds[0];
  }

  m_pfCTNBiases = new Real[m_unNumCTNs];
  for( unsigned int i = 0; i < m_unNumCTNs; i++ ) {
    m_pfCTNBiases[i] = params[unChromosomePosition++]*(m_fBiasesBounds[1] - m_fBiasesBounds[0]) + m_fBiasesBounds[0];
  }
  
  m_pfCTNTaus = new Real[m_unNumCTNs];
  for( unsigned int i = 0; i < m_unNumCTNs; i++ ) {
    m_pfCTNTaus[i] = pow(10, (m_fTausBounds[0] + ((m_fTausBounds[1] - m_fTausBounds[0]) * (params[unChromosomePosition++]))) );
  }

  
  m_pfCTNDeltaStates     = new Real[m_unNumCTNs];
  m_pfCTNStates          = new Real[m_unNumCTNs];
  for( unsigned int i = 0; i < m_unNumCTNs; i++ ) {
    m_pfCTNDeltaStates[i] = 0.0;
    m_pfCTNStates[i]      = 0.0;
  }
  
  return 0;
}



/****************************************/
/****************************************/

void CCI_RnctnController::ComputeOutputs( void ) {
  // Update delta state of hidden layer from inputs:
  for( unsigned int i = 0; i < m_unNumCTNs; i++ ) {
    m_pfCTNDeltaStates[i] = -m_pfCTNStates[i];
    
    for( unsigned int j = 0; ((i < m_unNumHidden) && (j < m_unNumberOfInputs)); j++ ) {
      // weight * sigmoid(state)
      m_pfCTNDeltaStates[i] += m_pfInput2HiddenWeights[i * m_unNumberOfInputs + j] * m_pfInputs[j];
    }	  

    // Update delta state from hidden layer, self-recurrent connections:
    for( unsigned int j = 0; j < m_unNumCTNs; j++ ) {
      Real z = (Real(1.0)/(exp(-( m_pfCTNStates[j] + m_pfCTNBiases[j])) + 1.0));
      m_pfCTNDeltaStates[i] += m_pfCTN2CTNWeights[i * m_unNumCTNs + j] * z;
    }
  }
    

  // once all delta state are computed, get the new activation for the
  // hidden unit amd compute the output
  for( unsigned int  i = 0; i < m_unNumCTNs; i++ ) {
    m_pfCTNStates[i] += m_pfCTNDeltaStates[i] * m_fTimeStep/m_pfCTNTaus[i];

    if( i >= m_unNumHidden ) {
      m_pfOutputs[i-m_unNumHidden] = (Real(1.0)/( exp(-( m_pfCTNStates[i] + m_pfCTNBiases[i])) + 1.0 ));
    }
  }
}


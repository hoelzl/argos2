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

#include "ci_ctrnn_multilayer_controller.h"
#include <argos2/common/utility/string_utilities.h>

using namespace argos;


const string CONFIGURATION_CTRNN_NUMHIDDEN = "num_hidden";
const string CONFIGURATION_CTRNN_TIMESTEP  = "integration_step";
const string CONFIGURATION_CTRNN_WEIGHTS   = "weight_range";
const string CONFIGURATION_CTRNN_BIASES    = "bias_range";
const string CONFIGURATION_CTRNN_TAUS      = "tau_range";

CCI_CtrnnMultilayerController::CCI_CtrnnMultilayerController() {
  m_pfInputToHiddenWeights  = NULL;
  m_pfHiddenToHiddenWeights = NULL;
  m_pfHiddenBiases          = NULL;
  m_pfHiddenTaus            = NULL;
  m_pfOutputBiases          = NULL;
  m_pfHiddenToOutputWeights = NULL;
  m_pfHiddenStates          = NULL;
  m_pfHiddenDeltaStates     = NULL;
  m_pfOutputs               = NULL;
  
  m_unNumberOfHiddenNodes = 0;
  m_fTimeStep = 0.1;

  m_fWeightsBounds[0] = -4.0;
  m_fWeightsBounds[1] =  4.0;
  m_fBiasesBounds[0]  = -4.0;
  m_fBiasesBounds[1]  =  4.0;
  m_fTausBounds[0]    = -1.0;
  m_fTausBounds[1]    =  3.0;
}


/****************************************/
/****************************************/

CCI_CtrnnMultilayerController::~CCI_CtrnnMultilayerController() {
}


/****************************************/
/****************************************/

int CCI_CtrnnMultilayerController::Init( const TConfigurationTree t_configuration_tree ) {
  ////////////////////////////////////////////////////////////////////////////////
  // First perform common initialisation from base class
  ////////////////////////////////////////////////////////////////////////////////
  if( CCI_NeuralNetworkController::Init( t_configuration_tree ) != 0 )
    return -1;
  

  ////////////////////////////////////////////////////////////////////////////////
  // Load number of hidden nodes
  ////////////////////////////////////////////////////////////////////////////////
  string s_num_hidden = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_CTRNN_NUMHIDDEN );
  if( s_num_hidden == "" ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Missing required tag <" << CONFIGURATION_CTRNN_NUMHIDDEN << ">" 
				 << " for CTRNN multi-layer initialisation" << endl;
    return -1;
  }

  if( StringToUnsignedInt( s_num_hidden, m_unNumberOfHiddenNodes ) != 0 ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_CTRNN_NUMHIDDEN
				 << ">" << s_num_hidden << " to a valid number" << endl;
    return -1;
  }
  

  ////////////////////////////////////////////////////////////////////////////////
  // integration step
  ////////////////////////////////////////////////////////////////////////////////
  string s_step_size = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_CTRNN_TIMESTEP );
  if( (s_step_size != "") && (StringToDouble( s_step_size, m_fTimeStep ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_CTRNN_TIMESTEP
				 << ">" << s_step_size << " to a valid number" << endl;
    return -1;
  }
  

  ////////////////////////////////////////////////////////////////////////////////
  // Load upper and lower bounds for weigths, biases and taus
  ////////////////////////////////////////////////////////////////////////////////
  string s_weights_bounds = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_CTRNN_WEIGHTS );
  if( (s_weights_bounds != "") && 
      (CExperimentConfiguration::GetNReals( s_weights_bounds, m_fWeightsBounds, 2 ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_CTRNN_WEIGHTS
				 << ">" << s_weights_bounds << " to valid numbers" << endl;
    return -1;
  }

  string s_biases_bounds = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_CTRNN_BIASES );
  if( (s_biases_bounds != "") && 
      (CExperimentConfiguration::GetNReals( s_biases_bounds, m_fBiasesBounds, 2 ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_CTRNN_BIASES
				 << ">" << s_biases_bounds << " to valid numbers" << endl;
    return -1;
  }

  string s_taus_bounds = CExperimentConfiguration::GetNodeValue( t_configuration_tree, CONFIGURATION_CTRNN_TAUS );
  if( (s_taus_bounds != "") && 
      (CExperimentConfiguration::GetNReals( s_taus_bounds, m_fTausBounds, 2 ) != 0) ) {
    CSwarmanoidLogger::LogErr( ) << "[FATAL] Could not convert tag <" << CONFIGURATION_CTRNN_TAUS
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

void CCI_CtrnnMultilayerController::Destroy() {
  if( m_pfInputToHiddenWeights )  delete[] m_pfInputToHiddenWeights;
  if( m_pfHiddenToHiddenWeights ) delete[] m_pfHiddenToHiddenWeights;
  if( m_pfHiddenBiases )          delete[] m_pfHiddenBiases;
  if( m_pfHiddenToOutputWeights ) delete[] m_pfHiddenToOutputWeights;
  if( m_pfOutputBiases )          delete[] m_pfOutputBiases;
  if( m_pfHiddenTaus )            delete[] m_pfHiddenTaus;
  if( m_pfHiddenDeltaStates )     delete[] m_pfHiddenDeltaStates;
  if( m_pfHiddenStates )          delete[] m_pfHiddenStates;
}


/****************************************/
/****************************************/

int CCI_CtrnnMultilayerController::LoadNetworkParamters( const string filename ) {
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

int CCI_CtrnnMultilayerController::LoadNetworkParamters( const unsigned int un_num_params, const Real* params ) {
  // check consistency between paramter file and xml declaration
  unsigned int un_num_parameters = 
    m_unNumberOfHiddenNodes * (m_unNumberOfInputs + 1)  +
    m_unNumberOfHiddenNodes * m_unNumberOfHiddenNodes   +
    m_unNumberOfOutputs * (m_unNumberOfHiddenNodes + 1) +
    m_unNumberOfHiddenNodes;
  
  if( un_num_params != un_num_parameters ) {
    CSwarmanoidLogger::LogErr() << "[FATAL] Number of paramter mismatch: '" 
				<< "passed " << un_num_params << " paramters, while " 
				<< un_num_parameters << " were expected from the xml configuration file" << endl;
    return -1;
  }

  if( m_pfInputToHiddenWeights )  delete[] m_pfInputToHiddenWeights;
  if( m_pfHiddenToHiddenWeights ) delete[] m_pfHiddenToHiddenWeights;
  if( m_pfHiddenBiases )          delete[] m_pfHiddenBiases;
  if( m_pfHiddenToOutputWeights ) delete[] m_pfHiddenToOutputWeights;
  if( m_pfOutputBiases )          delete[] m_pfOutputBiases;
  if( m_pfHiddenTaus )            delete[] m_pfHiddenTaus;
  if( m_pfHiddenDeltaStates )     delete[] m_pfHiddenDeltaStates;
  if( m_pfHiddenStates )          delete[] m_pfHiddenStates;

  unsigned int unChromosomePosition = 0;
  
  m_pfInputToHiddenWeights = new Real[m_unNumberOfInputs * m_unNumberOfHiddenNodes];
  for( unsigned int i = 0; i < m_unNumberOfInputs * m_unNumberOfHiddenNodes; i++ ) {
    m_pfInputToHiddenWeights[i] = params[unChromosomePosition++]*(m_fWeightsBounds[1] - m_fWeightsBounds[0] ) + m_fWeightsBounds[0];
  }

  m_pfHiddenToHiddenWeights = new Real[m_unNumberOfHiddenNodes * m_unNumberOfHiddenNodes];
  for( unsigned int i = 0; i < m_unNumberOfHiddenNodes * m_unNumberOfHiddenNodes; i++ ) {
    m_pfHiddenToHiddenWeights[i] = params[unChromosomePosition++]*(m_fWeightsBounds[1] - m_fWeightsBounds[0] ) + m_fWeightsBounds[0];
  }

  m_pfHiddenBiases = new Real[m_unNumberOfHiddenNodes];
  for( unsigned int i = 0; i < m_unNumberOfHiddenNodes; i++ ) {
    m_pfHiddenBiases[i] = params[unChromosomePosition++]*(m_fBiasesBounds[1] - m_fBiasesBounds[0] ) + m_fBiasesBounds[0];
  }

  m_pfHiddenTaus = new Real[m_unNumberOfHiddenNodes];
  for( unsigned int i = 0; i < m_unNumberOfHiddenNodes; i++ ) {
    m_pfHiddenTaus[i] = pow(10, (m_fTausBounds[0] + ((m_fTausBounds[1]-m_fTausBounds[0]) * (params[unChromosomePosition++]))));
  }

  m_pfHiddenToOutputWeights = new Real[m_unNumberOfHiddenNodes * m_unNumberOfOutputs];
  for( unsigned int i = 0; i < m_unNumberOfHiddenNodes * m_unNumberOfOutputs; i++ ) {
    m_pfHiddenToOutputWeights[i] = params[unChromosomePosition++]*(m_fWeightsBounds[1] - m_fWeightsBounds[0] ) + m_fWeightsBounds[0];
  }

  m_pfOutputBiases = new Real[m_unNumberOfOutputs];
  for( unsigned int i = 0; i < m_unNumberOfOutputs; i++ ) {
    m_pfOutputBiases[i] = params[unChromosomePosition++]*(m_fBiasesBounds[1] - m_fBiasesBounds[0] ) + m_fBiasesBounds[0];
    m_pfOutputs[i]      = 0.0;
  }
  
  m_pfHiddenDeltaStates     = new Real[m_unNumberOfHiddenNodes];
  m_pfHiddenStates          = new Real[m_unNumberOfHiddenNodes];
  for( unsigned int i = 0; i < m_unNumberOfHiddenNodes; i++ ) {
    m_pfHiddenDeltaStates[i] = 0.0;
    m_pfHiddenStates[i]      = 0.0;
  }

  return 0;
}



/****************************************/
/****************************************/

void CCI_CtrnnMultilayerController::ComputeOutputs( void ) {
  // Update delta state of hidden layer from inputs:
  for( unsigned int i = 0; i < m_unNumberOfHiddenNodes; i++ ) {
    m_pfHiddenDeltaStates[i] = -m_pfHiddenStates[i];
    
    for( unsigned int j = 0; j < m_unNumberOfInputs; j++ ) {
      // weight * sigmoid(state)
      m_pfHiddenDeltaStates[i] += m_pfInputToHiddenWeights[i * m_unNumberOfInputs + j] * m_pfInputs[j] ;	  
    }	  

    // Update delta state from hidden layer, self-recurrent connections:
    for( unsigned int j = 0; j < m_unNumberOfHiddenNodes; j++ ) {
      Real z = (Real(1.0)/(exp(-( m_pfHiddenStates[j] + m_pfHiddenBiases[j])) + 1.0));
      m_pfHiddenDeltaStates[i] += m_pfHiddenToHiddenWeights[i * m_unNumberOfHiddenNodes + j] * z;
    }
  }
    

  // once all delta state are computed, get the new activation for the hidden unit
  for( unsigned int  i = 0; i < m_unNumberOfHiddenNodes; i++ ) {
    m_pfHiddenStates[i] += m_pfHiddenDeltaStates[i] * m_fTimeStep/m_pfHiddenTaus[i];
  }

  // Update the outputs layer::
  for( unsigned int i = 0; i < m_unNumberOfOutputs; i++ ) {
    
    // Initialise to 0
    m_pfOutputs[i] = 0.0;
    
    // Sum over all the hidden nodes
    for( unsigned int j = 0; j < m_unNumberOfHiddenNodes; j++ ) {
      Real z = (Real(1.0)/( exp(-( m_pfHiddenStates[j] + m_pfHiddenBiases[j])) + 1.0 ));
      m_pfOutputs[i] += m_pfHiddenToOutputWeights[i * m_unNumberOfHiddenNodes + j] * z;
    }

    // Compute the activation function immediately, since this is
    // what we return and since the output layer is not recurrent:
    m_pfOutputs[i] = (Real(1.0)/( exp(-( m_pfOutputs[i] + m_pfOutputBiases[i])) + 1.0 ));
  }
}


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
 * @file <common/control_interface/ci_neural_network_controller.h>
 *
 * @brief This file provides the definition of the neural network controller
 * 
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */



#include "ci_perceptron_controller.h"

using namespace argos;




#define PARAMETER_FILE          "parameter_file"


CCI_PerceptronController::CCI_PerceptronController (  ) {
  m_pfWeights = NULL;
}


/****************************************/
/****************************************/

CCI_PerceptronController::~CCI_PerceptronController (  ) {
}


/****************************************/
/****************************************/

int CCI_PerceptronController::Init( const TConfigurationTree t_tree ) {

  /* First perform common initialisation from base class */
  if( CCI_NeuralNetworkController::Init( t_tree ) != 0 )
    return -1;
  
  if( (m_sParamterFile != "") && (LoadNetworkParamters( m_sParamterFile ) != 0) ) 
    return -1;

  return CCI_Controller::RETURN_OK;
}

/****************************************/
/****************************************/

void CCI_PerceptronController::Destroy() {
  if( m_pfWeights ) delete [] m_pfWeights;
}


/****************************************/
/****************************************/

int CCI_PerceptronController::LoadNetworkParamters( const string filename ) {

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

  // check consistency between paramter file and xml declaration
  m_unNumberOfWeights = (m_unNumberOfInputs + 1)*(m_unNumberOfOutputs);
  if( un_length != m_unNumberOfWeights ) {
    CSwarmanoidLogger::LogErr() << "[FATAL] Number of paramter mismatch: '" 
				<< filename << "' contains " << un_length << " paramters, while " 
				<< m_unNumberOfWeights << " were expected from the xml configuration file" << endl;    
    return -1;
  }


  // create weights vector and load it from file
  m_pfWeights = new Real[m_unNumberOfWeights];
  for( unsigned int i = 0; i < m_unNumberOfWeights; i++ ) {
    if( !(in >> m_pfWeights[i] ) ) {
      CSwarmanoidLogger::LogErr() << "[FATAL] Cannot read data from file '" << filename << "'" << endl;          
      return -1;
    }
  }

  return 0;
}


/****************************************/
/****************************************/

int CCI_PerceptronController::LoadNetworkParamters( const unsigned int un_num_params, const Real* params ) {
  // check consistency between paramters and xml declaration
  m_unNumberOfWeights = (m_unNumberOfInputs + 1)*(m_unNumberOfOutputs);
  if( un_num_params != m_unNumberOfWeights ) {
    CSwarmanoidLogger::LogErr() << "[FATAL] Number of paramter mismatch: '" 
				<< "passed " << un_num_params << " paramters, while " 
				<< m_unNumberOfWeights << " were expected from the xml configuration file" << endl;    
    return -1;
  }


  // create weights vector and load it from file
  m_pfWeights = new Real[m_unNumberOfWeights];
  for( unsigned int i = 0; i < m_unNumberOfWeights; i++ ) {
    m_pfWeights[i] = params[i];
  }

  return 0;
}



/****************************************/
/****************************************/

void CCI_PerceptronController::ComputeOutputs( void ) {
  for( unsigned int i = 0; i < m_unNumberOfOutputs; i++ ) {
    // Add the bias (weighted by the first weight to the i'th output node)
    m_pfOutputs[i] = m_pfWeights[i * (m_unNumberOfInputs + 1)];
    
    for( unsigned int j = 0; j < m_unNumberOfInputs; j++ ) {
      // Compute the weight number
      unsigned int ji = i * (m_unNumberOfInputs + 1) + (j + 1);
      // Add the weighted input
      m_pfOutputs[i] += m_pfWeights[ji] * m_pfInputs[j];

    }
        
    // Apply the transfer function (sigmoid with output in [0,1])
    m_pfOutputs[i] = 1.0/( 1 + exp( -m_pfOutputs[i]) );
  }
}


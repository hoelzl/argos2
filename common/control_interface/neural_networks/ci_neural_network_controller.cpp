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



#include "ci_neural_network_controller.h"
#include <argos2/common/utility/string_utilities.h>

using namespace argos;


const string NNCONTROLLER_PARAMETER_FILE = "parameter_file";
const string NNCONTROLLER_SENSOR_LIST    = "sensor_list";
const string NNCONTROLLER_ACTUATOR_LIST  = "actuator_list";


CCI_NeuralNetworkController::CCI_NeuralNetworkController (  ) {
  m_unNumberOfInputs  = 0;
  m_unNumberOfOutputs = 0;
  m_pfInputs          = NULL;
  m_pfOutputs         = NULL;
}


/****************************************/
/****************************************/

CCI_NeuralNetworkController::~CCI_NeuralNetworkController (  ) {
  if( m_pfInputs )  delete [] m_pfInputs;
  if( m_pfOutputs ) delete [] m_pfOutputs;
}


/****************************************/
/****************************************/

int CCI_NeuralNetworkController::Init( const TConfigurationTree t_tree ) {

  // get the sensors and actuators that pertain to the neural network
  m_tMapSensors = GetRobot()->GetAllSensors();
  m_tMapActuators = GetRobot()->GetAllActuators();

  // load the sensor list (ordering of the neural inputs). If no list
  // is explicitly given, include in the neural network list all robot
  // sensors
  string sensor_list = CExperimentConfiguration::GetNodeValue( t_tree, NNCONTROLLER_SENSOR_LIST );
  if( sensor_list != "" ) {
    Tokenize( sensor_list, m_vecSensors, ", ");
  }
  else {
    for( TSensorsMap::iterator it_sensors = m_tMapSensors.begin(); it_sensors != m_tMapSensors.end(); it_sensors++ ) {
      m_vecSensors.push_back( it_sensors->first );      
    }
  }

  // Compute the number of inputs, and initialise the input vector
  m_unNumberOfInputs = 0;
  for( vector<string>::iterator it_sensors = m_vecSensors.begin(); it_sensors != m_vecSensors.end(); it_sensors++ ) {
    m_unNumberOfInputs += m_tMapSensors[*it_sensors]->GetNumberOfSensorReadings();
  }

  m_pfInputs = new Real[m_unNumberOfInputs];
  for( unsigned int i = 0; i < m_unNumberOfInputs; i++ ) {
    m_pfInputs[i] = 0.0;
  }



  // load the actuator list (ordering of the neural outputs). If no
  // list is explicitly given, include in the neural network list all
  // robot actuators
  string actuator_list = CExperimentConfiguration::GetNodeValue( t_tree, NNCONTROLLER_ACTUATOR_LIST );
  if( actuator_list != "" ) {
    Tokenize( actuator_list, m_vecActuators, ", ");
  }
  else {
    for( TActuatorsMap::iterator it_actuators = m_tMapActuators.begin(); it_actuators != m_tMapActuators.end(); it_actuators++ ) {
      m_vecActuators.push_back( it_actuators->first );
    }
  }

  // Compute the number of outputs, and initialise the output vector
  m_unNumberOfOutputs = 0;
  for( vector<string>::iterator it_actuators = m_vecActuators.begin(); it_actuators != m_vecActuators.end(); it_actuators++ ) {
    m_unNumberOfOutputs += m_tMapActuators[*it_actuators]->GetNumberOfActuatorOutputs();
   }

  m_pfOutputs = new Real[m_unNumberOfOutputs];
  for( unsigned int i = 0; i < m_unNumberOfOutputs; i++ ) {
    m_pfOutputs[i] = 0.0;
  }
  


  // name of the parameter file
  m_sParamterFile = CExperimentConfiguration::GetNodeValue( t_tree, NNCONTROLLER_PARAMETER_FILE );

  return CCI_Controller::RETURN_OK;
}

/****************************************/
/****************************************/

void CCI_NeuralNetworkController::AddSensor( string s_sensor_id, CCI_Sensor* pc_sensor ) {
  if( m_tMapSensors.find( s_sensor_id) == m_tMapSensors.end() ) {
    m_tMapSensors[s_sensor_id] = pc_sensor;
    m_vecSensors.push_back( s_sensor_id );

    // resize vector
    m_unNumberOfInputs += pc_sensor->GetNumberOfSensorReadings();
    delete [] m_pfInputs;
    m_pfInputs = new Real[m_unNumberOfInputs];
  }
}


/****************************************/
/****************************************/

CCI_Sensor* CCI_NeuralNetworkController::RemoveSensor( string s_sensor_id ) {
  CCI_Sensor* pc_sensor = NULL;
  if( m_tMapSensors.find(s_sensor_id) != m_tMapSensors.end() ) {
    pc_sensor = m_tMapSensors[s_sensor_id];
    m_tMapSensors.erase(s_sensor_id);
    
    // resize vector
    m_unNumberOfInputs -= pc_sensor->GetNumberOfSensorReadings();
    delete [] m_pfInputs;
    m_pfInputs = new Real[m_unNumberOfInputs];
  }

  for( vector<string>::iterator it = m_vecSensors.begin(); it != m_vecSensors.end(); it++ ) {
    if( *it == s_sensor_id ) {
      m_vecSensors.erase(it);
      break;
    }
  }

  return pc_sensor;
}


/****************************************/
/****************************************/

void CCI_NeuralNetworkController::SetSensorList( string s_sensor_list ) {
  m_vecSensors.clear();
  Tokenize( s_sensor_list, m_vecSensors, ", ");

  // Compute the number of inputs, and initialise the input vector
  m_unNumberOfInputs = 0;
  for( vector<string>::iterator it_sensors = m_vecSensors.begin(); it_sensors != m_vecSensors.end(); it_sensors++ ) {
    m_unNumberOfInputs += m_tMapSensors[*it_sensors]->GetNumberOfSensorReadings();
  }

  // resize vector
  delete [] m_pfInputs;
  m_pfInputs = new Real[m_unNumberOfInputs];
  for( unsigned int i = 0; i < m_unNumberOfInputs; i++ ) {
    m_pfInputs[i] = 0.0;
  }
}



/****************************************/
/****************************************/

void CCI_NeuralNetworkController::AddActuator( string s_actuator_id, CCI_Actuator* pc_actuator ) {
  if( m_tMapActuators.find( s_actuator_id) == m_tMapActuators.end() ) {
    m_tMapActuators[s_actuator_id] = pc_actuator;
    m_vecActuators.push_back( s_actuator_id );

    // resize vector
    m_unNumberOfOutputs -= pc_actuator->GetNumberOfActuatorOutputs();
    delete [] m_pfOutputs;
    m_pfOutputs = new Real[m_unNumberOfOutputs];
  }
}


/****************************************/
/****************************************/

CCI_Actuator* CCI_NeuralNetworkController::RemoveActuator( string s_actuator_id ) {
  CCI_Actuator* pc_actuator = NULL;
  if( m_tMapActuators.find(s_actuator_id) != m_tMapActuators.end() ) {
    pc_actuator = m_tMapActuators[s_actuator_id];
    m_tMapActuators.erase(s_actuator_id);

    // resize vector
    m_unNumberOfOutputs -= pc_actuator->GetNumberOfActuatorOutputs();
    delete [] m_pfOutputs;
    m_pfOutputs = new Real[m_unNumberOfOutputs];
  }

  for( vector<string>::iterator it = m_vecActuators.begin(); it != m_vecActuators.end(); it++ ) {
    if( *it == s_actuator_id ) {
      m_vecActuators.erase(it);
      break;
    }
  }

  return pc_actuator;
}



/****************************************/
/****************************************/

void CCI_NeuralNetworkController::SetActuatorList( string s_actuator_list ) {
  m_vecActuators.clear();
  Tokenize( s_actuator_list, m_vecActuators, ", ");

  // Compute the number of inputs, and initialise the input vector
  m_unNumberOfOutputs = 0;
  for( vector<string>::iterator it_actuators = m_vecActuators.begin(); it_actuators != m_vecActuators.end(); it_actuators++ ) {
    m_unNumberOfOutputs += m_tMapActuators[*it_actuators]->GetNumberOfActuatorOutputs();
  }

  // resize vector
  delete [] m_pfOutputs;
  m_pfOutputs = new Real[m_unNumberOfOutputs];
  for( unsigned int i = 0; i < m_unNumberOfOutputs; i++ ) {
    m_pfOutputs[i] = 0.0;
  }
}



/****************************************/
/****************************************/

void CCI_NeuralNetworkController::ControlStep( void ) {
  // update sensor inputs
  unsigned int un_input = 0;
  for( vector<string>::iterator it_sensors = m_vecSensors.begin(); it_sensors != m_vecSensors.end(); it_sensors++ ) {
    m_tMapSensors[*it_sensors]->GetAllNormalisedSensorReadings( m_pfInputs + un_input );
    un_input += m_tMapSensors[*it_sensors]->GetNumberOfSensorReadings();
  }


  // compute outputs
  ComputeOutputs();

  // update actuator outputs
  unsigned int un_output = 0;
  for( vector<string>::iterator it_actuators = m_vecActuators.begin(); it_actuators != m_vecActuators.end(); it_actuators++ ) {
    m_tMapActuators[*it_actuators]->SetAllNormalisedActuatorOutputs( m_pfOutputs + un_output );
    un_output += m_tMapActuators[*it_actuators]->GetNumberOfActuatorOutputs();;
  }

}



/****************************************/
/****************************************/

void CCI_NeuralNetworkController::SetOnlineParameters( const unsigned int un_num_params, const Real* pf_params ) {
  LoadNetworkParamters( un_num_params, pf_params );
}

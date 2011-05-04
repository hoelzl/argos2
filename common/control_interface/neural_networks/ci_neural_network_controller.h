/* -*- Mode: C++ -*- 
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


#ifndef _CCI_NEURALNETWORKCONTROLLER_H_
#define _CCI_NEURALNETWORKCONTROLLER_H_

/* To avoid dependency problems when including */
namespace argos {
  class CCI_NeuralNetworkController;
  class CCI_Controller;
};


#include "ci_controller.h"

using namespace argos;
using namespace std;

namespace argos {

  class CCI_NeuralNetworkController : public CCI_Controller {
  protected:

    unsigned int   m_unNumberOfInputs;
    unsigned int   m_unNumberOfOutputs;

    Real*        m_pfInputs;
    Real*        m_pfOutputs;

    TActuatorsMap  m_tMapActuators;
    vector<string> m_vecActuators;

    TSensorsMap    m_tMapSensors;
    vector<string> m_vecSensors;

    string         m_sParamterFile;

  public:
    CCI_NeuralNetworkController();
    virtual ~CCI_NeuralNetworkController();

    virtual int  Init( const TConfigurationTree t_tree );
    virtual void ControlStep( void );

    virtual void Destroy() = 0;
    virtual int  LoadNetworkParamters( const string filename ) = 0;
    virtual int  LoadNetworkParamters( const unsigned int un_num_params, const Real* params ) = 0;
    virtual void ComputeOutputs( void ) = 0;

    virtual void          AddSensor( string s_sensor_id, CCI_Sensor* pc_sensor );
    virtual CCI_Sensor*   RemoveSensor( string s_sensor_id );
    virtual void          SetSensorList( string s_sensor_list );

    virtual void          AddActuator( string s_actuator_id, CCI_Actuator* pc_actuator );
    virtual CCI_Actuator* RemoveActuator( string s_actuator_id );
    virtual void          SetActuatorList( string s_actuator_list );

    
    inline  unsigned int GetNumberOfInputs( void ) { return m_unNumberOfInputs; };
    inline  void SetNumberOfInputs( unsigned int un_inputs ) { m_unNumberOfInputs = un_inputs; };
    inline  const Real* GetInputs( void ) { return m_pfInputs; };

    inline  unsigned int GetNumberOfOutputs( void ) { return m_unNumberOfOutputs; };
    inline  void SetNumberOfOutputs( unsigned int un_outputs ) { m_unNumberOfOutputs = un_outputs; };
    inline  const Real* GetOutputs( void ) { return m_pfOutputs; };

    virtual void SetOnlineParameters( const unsigned int un_num_params, const Real* pf_params );
  };
};


#endif

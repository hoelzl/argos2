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
 * @file <common/control_interface/ci_ctrnn_multilayer_controller.h>
 *
 * @brief This file provides the definition of the CTRNN multilayer
 * neural network controller
 * 
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */


#ifndef _CCI_CTRNNMULTILAYERCONTROLLER_H_
#define _CCI_CTRNNMULTILAYERCONTROLLER_H_

/* To avoid dependency problems when including */
namespace argos {
  class CCI_CtrnnMultilayerController;
  class CCI_NerualNetworkController;
};

#include <math.h>

#include "ci_neural_network_controller.h"

using namespace argos;
using namespace std;

namespace argos {

  class CCI_CtrnnMultilayerController : public CCI_NeuralNetworkController {
  protected:

    Real*       m_pfInputToHiddenWeights;
    
    Real*       m_pfHiddenBiases;
    Real*       m_pfHiddenTaus;
    Real*       m_pfHiddenDeltaStates;
    Real*       m_pfHiddenStates;

    Real*       m_pfHiddenToHiddenWeights;
    Real*       m_pfHiddenToOutputWeights;

    Real*       m_pfOutputBiases;
    Real*       m_pfOutputTaus;

    unsigned int  m_unNumberOfHiddenNodes;
    Real        m_fTimeStep;

    Real        m_fWeightsBounds[2];
    Real        m_fBiasesBounds[2];
    Real        m_fTausBounds[2];

  public:
    CCI_CtrnnMultilayerController();
    virtual ~CCI_CtrnnMultilayerController();

    virtual int  Init( const TConfigurationTree t_tree );

    virtual void Destroy();
    virtual int  LoadNetworkParamters( const string filename );
    virtual int  LoadNetworkParamters( const unsigned int un_num_params, const Real* pf_params );
    virtual void ComputeOutputs( void );


    inline  unsigned int  GetNumberOfHiddenNodes( void ) { return m_unNumberOfHiddenNodes; };
    inline  const Real* GetHiddenStates( void )        { return m_pfHiddenStates;        };
    inline  const Real* GetHiddenTaus( void )          { return m_pfHiddenTaus;          };
    inline  const Real* GetHiddenBias( void )          { return m_pfHiddenBiases;        };
    inline  const Real* GetOutputBias( void )          { return m_pfOutputBiases;        };

  };
};


#endif

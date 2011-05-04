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


#ifndef _CCI_RNCTNCONTROLLER_H_
#define _CCI_RNCTNCONTROLLER_H_

/* To avoid dependency problems when including */
namespace argos {
  class CCI_RnctnController;
  class CCI_NerualNetworkController;
};

#include <math.h>

#include "ci_neural_network_controller.h"

using namespace argos;
using namespace std;

namespace argos {

  class CCI_RnctnController : public CCI_NeuralNetworkController {
  protected:

    Real*       m_pfInput2HiddenWeights;
    Real*       m_pfCTN2CTNWeights;
    
    Real*       m_pfCTNBiases;
    Real*       m_pfCTNTaus;
    Real*       m_pfCTNDeltaStates;
    Real*       m_pfCTNStates;

    unsigned int  m_unNumHidden;
    unsigned int  m_unNumCTNs;
    Real        m_fTimeStep;

    Real        m_fWeightsBounds[2];
    Real        m_fBiasesBounds[2];
    Real        m_fTausBounds[2];

  public:
    CCI_RnctnController();
    virtual ~CCI_RnctnController();

    virtual int  Init( const TConfigurationTree t_tree );

    virtual void Destroy();
    virtual int  LoadNetworkParamters( const string filename );
    virtual int  LoadNetworkParamters( const unsigned int un_num_params, const Real* pf_params );
    virtual void ComputeOutputs( void );


    inline  unsigned int  GetNumberOfHiddenNodes( void ) { return m_unNumHidden; };
    inline  const Real* GetCTNStates( void )           { return m_pfCTNStates; };
    inline  const Real* GetCTNTaus( void )             { return m_pfCTNTaus;   };
    inline  const Real* GetCTNBias( void )             { return m_pfCTNBiases; };

  };
};


#endif

/**
 * This file comes from an external source and has been copied inside the ARGoS project.
 *
 * See http://iridia-dev.ulb.ac.be/projects/argos/trac/wiki/ExternalCode for rules about
 * copying code from external sources and a listing of all code from external sources
 * inside ARGoS.
 *
 * Description: This file is distributed as part of the FSMPP library.FSMPP library is a framework to build Deterministic Finite State Machines in C++
 * Source: http://sourceforge.net/projects/fsmpp
 * Date: 27.03.2009
 * Copied by: Nithin Mathews
 * License: FSMPP-0.3 is distributed under the MIT License
 */

//////////////////////////////////////////////////////////////////////////////////
// This file is distributed as part of the FSMPP library.
// FSMPP library is a framework to build Deterministic Finite State
// Machines in C++.
//
// Copyright (c) 2007, 2008 Siva Chandra
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
// In case you would like to contact the author, use the following
// e-mail address: sivachandra_br@yahoo.com
//////////////////////////////////////////////////////////////////////////////////

/**
 * @file <common/control_interface/behvaioral_toolkit/utility_classes/fsm/transition.h>
 *
 * @brief This file provides the definition a transaction used by the fsm.h
 *
 * This class encapsulates a state transition. This class will never be used
 * explicitly by a user of FSM. However, this class is used implicitly
 * whenever a user specifies a transition through the member function
 * fsm::State::AddTransition.
 *
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 */


#ifndef TRANSITION_H
#define TRANSITION_H

#include <argos2/common/control_interface/behavioral_toolkit/utility_classes/fsm/action.h>
#include <argos2/common/utility/datatypes/datatypes.h>


namespace btfsm {

    template <typename InputType>
    class State;

    template <typename InputType>

    class Transition {

        public:

            /**
            * Constructor.
            */
            Transition();

            /**
            * Constructor.
            */
            Transition(State<InputType> *pc_next_state, Action<InputType> *c_act);

            /**
            * Constructor.
            */
            Transition(const Transition<InputType> &tr);

            /**
            * Destructor.
            */
            virtual ~Transition() {}

            /**
            * @brief State transition.
            */
            virtual State<InputType>* Transit(const InputType& t_input);

        private:

            State<InputType> *m_pcState;
            Action<InputType> *m_pcAction;

    };

    template <typename InputType>
    Transition<InputType>::Transition(State<InputType> *pc_nxt_state,
                                      Action<InputType> *pc_act) {
        m_pcState = pc_nxt_state;
        m_pcAction = pc_act;
    }

    template <typename InputType>
    Transition<InputType>::Transition()
    {
        m_pcState = NULL;
        m_pcAction = NULL;
    }

    template <typename InputType>
    Transition<InputType>::Transition(const Transition<InputType> &pc_transition) :
        m_pcState(pc_transition.m_pcState),
        m_pcAction(pc_transition.m_pcAction) {}

    template <typename InputType>
    State<InputType>* Transition<InputType>::Transit(const InputType& t_input)
    {
        if (m_pcAction != NULL)
            m_pcAction->Perform(t_input);

        return m_pcState;
    }

}

#endif

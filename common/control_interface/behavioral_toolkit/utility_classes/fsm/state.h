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
 * @file <common/control_interface/behavioral_toolkit/utility_classes/fsm/state.h>
 *
 * @brief This file provides the definition a state used by the fsm.h
 *
 * A template class which encapsulates a state of a finite state machine.
 * A state transition is triggered by an input to the state. The data type
 * of the transition triggering inputs should be provided as the template
 * argument.
 *
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 */


#ifndef STATE_H
#define STATE_H

#include <map>
#include <iostream>
#include <string>
#include <argos2/common/control_interface/behavioral_toolkit/utility_classes/fsm/transition.h>
#include <argos2/common/utility/datatypes/datatypes.h>

namespace btfsm {

    template <typename InputType>
    class FSM;


    template <typename InputType>
    class State {

        public:


            /**
             * Constructor.
             *
             * @param pc_parent Pointer to the  parent fsm::FSM object. Every state
             * should have a parent btfsm::FSM which has this state as one of its
             * constituents. NOTE: parent cannot be NULL or 0.
             * @param n_id An integral ID for the state. Each state of an FSM should
             * have its own unique integral ID. This helps a user trace the running
             * of an FSM.
             */
            State(FSM<InputType> *pc_parent, argos::SInt32 n_id);

            /**
             * Constructor.
             *
             * @param pc_parent Pointer to the  parent fsm::FSM object. Every state
             * should have a parent btfsm::FSM which has this state as one of its
             * constituents. NOTE: parent cannot be NULL or 0.
             * @param n_id An integral ID for the state. Each state of an FSM should
             * have its own unique integral ID. This helps a user trace the running
             * of an FSM.
             * @param str_name string name for the state
             */
            State(FSM<InputType> *pc_parent, argos::SInt32 n_id, std::string str_name);

            /**
             * Copy Constructor.
             */
            State(const State& c_state);

            /**
             * Destructor.
             */
            ~State();

            /**
             * @brief Adds a state transition corresponding to an input.
             *
             * Each transition might also require a certain action to be performed.
             * This action should be encapsulated into a btfsm::Action object and
             * passed as the third argument to this function.
             *
             * @param t_input The input which triggers the state transition.
             * @param pc_next_state  Pointer to the next state.
             * @param pc_action Pointer to the lcs::Action object corresponding
             *  to the transition.
             */
            void AddTransition(const InputType t_input, State<InputType> *pc_next_state, Action<InputType> *pc_action = NULL);

            /**
             * @brief Sets the default state transition.
             *
             * A default transition occurs when an unspecified input is passed to the state.
             * A transition to the current state with no action is considered to be
             * the default transition.
             *
             * @param pc_default The state to which the default transition should occur to.
             * @param pc_action The action object corresponding to the action to be
             * taken during a default transition.
             */
            void DefaultTransition(State<InputType> *pc_default, Action<InputType> *pc_action = NULL);

            /**
             * @brief Used to trigger a state with an input.
             *
             * A call to this function calls State::operator<< internally.
             * It returns the next state resulting from a transition corresponding to the passed
             * input. The action corresponding to the transition is also executed.
             *
             * @param t_input The input to trigger a state transition.
             * @return the next state of the FSM
             */
            State<InputType>* Trigger(const InputType& t_input) {
                State<InputType>::operator<<(t_input);
            }

            /**
             * @brief Returns the numeric id of this state.
             *
             * @return the id of the state
             */
            argos::SInt32 GetId(void) const {
                return m_nId;
            }

            /**
             * @brief Returns the name of this state.
             *
             * @return the string id of the state
             */
            std::string GetName(void) const {
                return m_strName;
            }

            /**
             * @brief Short hand notation for triggering a state with an input
             * @see State::trigger for more information.
             */
            State<InputType>* operator<<(const InputType& input);

        private:

            /** Numeric id of the state */
            argos::SInt32 m_nId;
            /** String id of the state */
            std::string m_strName;
            /** Transitions */
            std::map< InputType, Transition<InputType> > m_mapTrantisions;
            /** Default state */
            State<InputType> *m_pcDefState;
            /** Default action */
            Action<InputType> *m_pcDefAction;

            /**
            * Constructor.
            */
            State() {}

    };

    template <typename InputType>
    State<InputType>::~State() {}

    template <typename InputType>
    State<InputType>* State<InputType>::operator<<(const InputType& t_input)
    {

        if (m_mapTrantisions.end() == m_mapTrantisions.find(t_input)) {
            if (m_pcDefAction != NULL)
                m_pcDefAction->Perform(t_input);

            return m_pcDefState;
        }
        else {
            Transition<InputType> transition(m_mapTrantisions[t_input]);
            return transition.Transit(t_input);
        }
    }

    template <typename InputType>
    void State<InputType>::AddTransition(const InputType t_input,
                                         State<InputType> *pc_next_state,
                                         Action<InputType> *pc_action)
    {
        m_mapTrantisions[t_input] = Transition<InputType>(pc_next_state, pc_action);
    }

    template <typename InputType>
    void State<InputType>::DefaultTransition(State<InputType> *pc_def, Action<InputType> *pc_action)
    {
        m_pcDefState = pc_def;
        m_pcDefAction = pc_action;
    }

}

#endif


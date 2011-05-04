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
 * @file <common/control_interface/behvaioral_toolkit/utility_classes/fsm/state.h>
 *
 * @brief This file provides the definition of the finite state machine, which is derived
 * by all behaviors.
 *
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 *
 * A template class which encapsulates a Finite State Machine. A user of the FSM
 * can either use this class directly, or derive a suitable class which encapsulates
 * a finite state machine of their choice.
 *
 */


#ifndef FSM_H
#define FSM_H

#include <list>
#include <argos2/common/control_interface/behavioral_toolkit/utility_classes/fsm/state.h>
#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/common/utility/logging/argos_log.h>


namespace btfsm {

    template <typename InputType>
    class FSM {

        public:

            /**
             *
             * Constructor.
             *
             **/
            FSM();

            /**
             *
             * Destructor.
             *
             **/
            virtual ~FSM();

            /**
             *
             * @brief Used to initialize the state. Returns the newly created state object.
             *
             * @param pc_parent  Pointer to the  parent fsm::FSM object. Every state
             * should have a parent fsm::FSM which has this state as one of its
             * constituents. NOTE: parent cannot be NULL or 0.
             *
             * @param n_id An integral ID for the state.
             *
             * @param str_name A name for the state
             *
             * @return The newly created state.
             **/
            State<InputType>* InitializeState(FSM<InputType> *pc_parent, argos::SInt32 n_id, std::string str_name);

            /**
             *
             * @brief Sets the start state of the FSM.
             *
             * @param pc_start_state  Pointer to the start state object.
             *
             **/
            void SetStartState(State<InputType> *pc_start_state) {
                m_pcStartState = pc_start_state;
                m_pcCurrState = pc_start_state;
            }

            /**
             *
             * @brief Sets the current state of the FSM.
             *
             * @param pc_current_state  Pointer to the start state object, to be set as current.
             *
             **/
            void SetCurrentState(State<InputType> *pc_current_state) {
                m_pcCurrState = pc_current_state;
            }

            /**
             *
             * @brief Sets a transition that can be triggered from all the states.
             *
             * @param t_input input that triggers the transition.
             *
             * @param pc_target_state  Pointer to the target state for the transition.
             *
             **/
            void AddTransitionFromAllStates(const InputType t_input, State<InputType> *pc_target_state);

            /**
             *
             * @brief Overloaded operator defines the procedure in which an input can be
             * passed to an FSM object. The state of FSM changes according to the input
             * specified as an argument to this function.
             *
             * @param param t_input The input to the FSM
             *
             **/
            void operator<<(const InputType& t_input);

            /**
             *
             * @brief Internal function to register state objects.
             *
             * @param pc_state state to be registered
             *
             **/
            void EnList(State<InputType> *pc_state);

            /**
             *
             * @brief Internal function to register action objects.
             *
             * @param pc_action state to be registered
             *
             **/
            void EnList(Action<InputType> *pc_action);

            /**
             *
             * @brief Returns the Id of the current state
             *
             * @return Current state Id.
             *
             **/
            argos::UInt32 GetStateID();

            /**
             *
             * @brief Returns the name of the current state
             *
             * @return Current state name.
             *
             **/
            std::string GetStateName();

            /**
             *
             * @brief Returns the name of a given state
             *
             * @param n_state_id state id of which the name must be returned
             *
             * @return Current state Id.
             *
             **/
            std::string GetStateName(argos::SInt32 n_state_id);

            /**
             *
             * @brief Sets FSM state to the starting state
             *
             **/
            void ResetFSM() {
                m_pcCurrState = m_pcStartState;
            }

            // Method to add an input to the FSM without having to use the overloaded operator <<
            /**
             *
             * @brief Adds an input to the FSM.
             *
             * @param t_input Input to the FSM
             *
             **/
            void Input(const InputType& t_input);

        private:
            State<InputType> *m_pcStartState, *m_pcCurrState;
            std::list< State<InputType>* > m_listStates;
            std::list< Action<InputType>* > m_listActions;

    };


    template <typename InputType>
    State<InputType>::State(FSM<InputType> *pc_parent_fsm, argos::SInt32 n_id) :
        State(pc_parent_fsm, n_id, "NOT_DEFINED") {}


    template <typename InputType>
    State<InputType>::State(FSM<InputType> *pc_parent_fsm, argos::SInt32 n_id, std::string str_name) :
                            m_nId(n_id),
                            m_strName(str_name),
                            m_mapTrantisions(std::map< InputType, Transition<InputType> >())
    {
        if (pc_parent_fsm != NULL)
            pc_parent_fsm->EnList(this);
        else
            argos::LOGERR << "[ERROR] BTFSM::State::Constructor2: Invalid Parent. A state should have a non-NULL parent." << std::endl;

        m_pcDefState = this;
        m_pcDefAction = NULL;
    }

    template <typename InputType>
    State<InputType>* FSM<InputType>::InitializeState(FSM<InputType> *pc_parent,
                                                      argos::SInt32 n_id,
                                                      std::string str_name)
    {
        return new State<InputType> (pc_parent, n_id, str_name);
    }


    template <typename InputType>
    Action<InputType>::Action(FSM<InputType> *pc_parent)
    {
        if (pc_parent != NULL)
            pc_parent->EnList(this);
        else
            argos::LOGERR << "[ERROR] BTFSM::Action::Constructor: Invalid Parent. An action should have a non-NULL parent." << std::endl;
    }

    template <typename InputType>
    FSM<InputType>::FSM(void):
        m_pcStartState(NULL),
        m_pcCurrState(NULL),
        m_listStates(std::list< State<InputType>* >()),
        m_listActions(std::list< Action<InputType>* >()) {}

    template <typename InputType>
    FSM<InputType>::~FSM()
    {

        typename std::list< State<InputType>* >::iterator itStates = m_listStates.begin();
        typename std::list< Action<InputType>* >::iterator itActions = m_listActions.begin();

        argos::SInt32 nStateListSize = m_listStates.size();
        argos::SInt32 nActionListSize = m_listActions.size();

        for (argos::SInt32 i = 0; i < nStateListSize; i++) {
            delete *itStates;
            itStates++;
        }

        for (argos::SInt32 i = 0; i < nActionListSize; i++) {
            delete *itActions;
            itActions++;
        }
    }

    template <typename InputType>
    void FSM<InputType>::operator<<(const InputType& t_input)
    {

        if (m_pcCurrState == NULL) {
            argos::LOGERR << "[ERROR]  Current state of the FSM is NULL. Cannot accept inputs!" << std::endl;
            return;
        }

        m_pcCurrState = (*m_pcCurrState << t_input);
    }

    template <typename InputType>
    void FSM<InputType>::Input(const InputType& t_input)
    {

        if (m_pcCurrState == NULL) {
            argos::LOGERR << "[ERROR]  Current state of the FSM is NULL. Cannot accept inputs!" << std::endl;
            return;
        }

        m_pcCurrState = (*m_pcCurrState << t_input);
    }

    template <typename InputType>
    void FSM<InputType>::EnList(State<InputType> *pc_state)
    {

        if (pc_state != NULL)
            m_listStates.push_back(pc_state);

    }

    template <typename InputType>
    void FSM<InputType>::EnList(Action<InputType> *pc_action)
    {
        if (pc_action != NULL)
            m_listActions.push_back(pc_action);
    }

    template <typename InputType>
    unsigned int FSM<InputType>::GetStateID(void)
    {

        if (m_pcCurrState == NULL) {
            argos::LOGERR << "[ERROR]  Current state of the FSM is NULL. Cannot retrieve state ID!" << std::endl;
            return 0;
        }

        return m_pcCurrState->GetId();
    }

    template <typename InputType>
    std::string FSM<InputType>::GetStateName(void)
    {

        if (m_pcCurrState == NULL) {
            argos::LOGERR << "[ERROR] Current state of the FSM is NULL. Cannot retrieve state name!" << std::endl;
            return "";
        }

        return m_pcCurrState->GetName();
    }

    template <typename InputType>
    std::string FSM<InputType>::GetStateName(argos::SInt32 n_id)
    {

        typename std::list< State<InputType>* >::iterator itStateList = m_listStates.begin();
        argos::SInt32 nStateListSize = m_listStates.size();

        for (argos::UInt32 i = 0; i < nStateListSize; i++) {

            State<InputType>* pcState = *itStateList;

            if (pcState->GetId() == n_id)
                return pcState->GetName();

            itStateList++;
        }

        argos::LOGERR << "[ERROR] Requested state ID not found. Cannot retrieve state name!" << std::endl;
        return "";
    }

    template <typename InputType>
    void FSM<InputType>::AddTransitionFromAllStates(const InputType t_input, State<InputType> *pc_state)
    {

        typename std::list< State<InputType>* >::iterator itStateList = m_listStates.begin();
        argos::SInt32 nStateListSize = m_listStates.size();

        for (argos::UInt32 i = 0; i < nStateListSize; i++) {
            State<InputType>* pcState = *itStateList;
            pcState->AddTransition(t_input, pc_state);
            itStateList++;
        }

    }

}

#endif

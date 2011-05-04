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
 * @file <common/control_interface/behvaioral_toolkit/utility_classes/fsm/action.h>
 *
 * @brief This file provides the definition an action used by the fsm.h
 *
 * A class derived from this class should encapsulate an action corresponding
 * to a state transition.
 *
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 */

#ifndef ACTION_H
#define ACTION_H

#include <argos2/common/utility/datatypes/datatypes.h>

namespace btfsm {

    template <typename InputType>
    class FSM;


    template <typename InputType>
    class Action {

        public:

            /**
             *
             * Constructor.
             *
             * @param pc_parent Pointer to the parent btfsm::FSM object of the action
             *
             */
            Action(FSM<InputType> *pc_parent);

            /**
             *
             * Destructor.
             *
             */
            virtual ~Action() {}

            /**
             *
            * Perform the action corresponding to the state
            * transition for which the object is an action object.
            * This function should be overloaded in the derived class.
            *
            * @param t_input input
            *
            */
            virtual void Perform(const InputType& t_input) = 0;

    };

}

#endif

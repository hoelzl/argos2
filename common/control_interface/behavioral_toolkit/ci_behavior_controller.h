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
 * @file <common/control_interface/behavioral_toolkit/ci_behavior_controller.h>
 *
 * @brief This file provides the control interface for a behavior based robot
 * controller. This class contains the root behavior, which is the one containing
 * all possible other sub-behaviors. Hence, the correct use of the behavioral
 * toolkit requires that the top controller logic has to be implemented inside the
 * root behavior and not here.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 * @author Giovanni Pini   - <gpini@iridia.ulb.ac.be>
 */

#ifndef CI_BEHAVIOR_CONTROLLER_H
#define CI_BEHAVIOR_CONTROLLER_H

namespace argos {
    template<class TRobotState> class CCI_BehaviorController;
}

#include <argos2/common/control_interface/ci_controller.h>
#include <argos2/common/control_interface/behavioral_toolkit/ci_behavior.h>
#include <argos2/common/control_interface/behavioral_toolkit/ci_robot_data.h>
#include <argos2/common/control_interface/behavioral_toolkit/ci_robot_state.h>

namespace argos {

    template<class TRobotState> class CCI_BehaviorController: public CCI_Controller {

        public:

            /**
             * Constructor.
             */
            CCI_BehaviorController() :
                m_pcRobotData(NULL),
                m_pcRootBehavior(NULL),
                m_pcState(NULL) {}

            /**
             * Destructor.
             */
            virtual ~CCI_BehaviorController() {}

            /**
             * @brief Initializes the behavior controller.
             * @param t_tree The configuration used to read the configuration of the controller.
             */
            virtual void Init( TConfigurationNode& t_tree) {
                m_pcState->ReadState();
                m_pcRootBehavior->Init(*m_pcState);
                m_pcState->ApplyState();
            }

            /**
             * @brief Performs the control step of the controller.
             *
             * The control step of a behavior controller first reads from the sensors
             * and writes to the state object. Then, it executes the root behavior step, that
             * might trigger the step of all its sub-behaviors, in order to modify the robot
             * state. At the end, the modified actuator state is applied using the actuators.
             *
             */
            virtual void ControlStep() {
                m_pcState->ReadState();
                m_pcRootBehavior->Step(*m_pcState);
                m_pcState->ApplyState();
                m_pcRobotData->ClearTemporary();
            }

            /**
             * The cleanup method of the behavior controller.
             */
            virtual void Destroy() {
                m_pcState->ReadState();
                m_pcRootBehavior->Destroy(*m_pcState);
                m_pcState->ApplyState();
                m_pcRobotData->Destroy();
            }

        protected:

            CCI_RobotData<TRobotState>* m_pcRobotData;
            CCI_Behavior<TRobotState>* m_pcRootBehavior;
            TRobotState* m_pcState;

    };

}

#endif

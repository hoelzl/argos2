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
 * @file <common/control_interface/behavioral_toolkit/ci_robot_data.h>
 *
 * @brief This file provides the robot data object, used for data sharing in the behavioral toolkit.
 * This class is used for sharing global data across a robot's different behaviors.
 * All behaviors of a single robot share the same CCI_RobotData object. Thus, data can
 * be stored in one of two maps available to the programmer:
 *  1) the persistent map
 *     holds persistent data like variables, statistics and configuration data
 *  2) the temporary map
 *     holds temporary data like cached computation results etc
 *     the temporary map get's cleaned out at the beginning of each time step
 * The maps are basically a ripoff of type boost::any, named argos::any.
 * Thus, all types can be inserted in the maps and
 * requested in a type-safe manner. For helper functions to set and get values
 * see CCI_Behavior::Set*InMap and CCI_Behavior::Get..FromMap.
 * Additionally, the robot data object holds common data like pointers to the robot's
 * controller, root behavior and the XML configuration tree.
 *
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#ifndef CI_ROBOT_DATA_H
#define CI_ROBOT_DATA_H

namespace argos {
    template<class TRobotState> class CCI_RobotData;
}

#include <map>
#include <string>
#include <argos2/common/utility/datatypes/any.h>

#include <argos2/common/control_interface/ci_robot.h>
#include <argos2/common/control_interface/ci_controller.h>

#include <argos2/common/control_interface/behavioral_toolkit/ci_behavior.h>
#include <argos2/common/control_interface/behavioral_toolkit/ci_behavior_controller.h>
#include <argos2/common/control_interface/behavioral_toolkit/ci_robot_data.h>
#include <argos2/common/control_interface/behavioral_toolkit/ci_robot_state.h>

namespace argos {

    typedef std::map<const std::string, argos::any> TAnyPropertyMap;

    template<class TRobotState> class CCI_RobotData {

        public:

            /**
             * @brief Constructor.
             * @param  pc_robot              the robot the data object is associated with
             * @param  pc_controller         the robot's controller
             * @param  t_configuration_tree  the robot's XML configuration tree
             */
            CCI_RobotData(CCI_Robot& pc_robot,
                          CCI_BehaviorController<TRobotState>* pc_controller,
                          const TConfigurationNode t_configuration_tree) :
                m_pcRobot(&pc_robot),
                m_pcController(pc_controller),
                m_pcRootBehavior(NULL),
                m_tConfigurationTree(t_configuration_tree) {
                m_tTemporaryMap["CCI_RobotData<TRobotState>::sMapName"]  = std::string("CCI_RobotData<TRobotState>::m_tTemporaryMap");
                m_tPersistentMap["CCI_RobotData<TRobotState>::sMapName"] = std::string("CCI_RobotData<TRobotState>::m_tPersistentMap");
            }

            /**
             * @brief Destructor.
             */
            ~CCI_RobotData() {}

            /**
             * @brief Destroy method.
             * Clears out all data in the maps.
            */
            inline void Destroy() {
                m_tPersistentMap.clear();
                m_tTemporaryMap.clear();
            }

            /**
             * @brief Clears all data in the temporary map.
             * This function is called from BehaviorController::Step().
             */
            inline void ClearTemporary() {
                m_tTemporaryMap.clear();
                m_tTemporaryMap["CCI_RobotData<TRobotState>::sMapName"] = std::string("CCI_RobotData<TRobotState>::m_tTemporaryMap");
            }

            /**
             * @brief Returns the robot.
             * @return robot
             */
            inline CCI_Robot* GetRobot() {
                return m_pcRobot;
            }

            /**
             * @brief Returns the robot's id.
             * @return robot id
             */
            inline const std::string& GetRobotId() {
                return m_pcRobot->GetRobotId();
            }

            /**
             * @brief Returns the controller of the robot.
             * @return controller of robot
             */
            inline CCI_BehaviorController<TRobotState>* GetController() {
                return m_pcController;
            }

            /**
             * @brief Returns the root behavior of the robot.
             * It has to be set upon initializing the root behavior in the controllers Init() function.
             * @return root behavior
             */
            inline CCI_Behavior<TRobotState>* GetRootBehavior() {
                return m_pcRootBehavior;
            }

            /**
             * @brief Sets the root behavior of this robot.
             * This function should be called after initializing the root behavior.
             * @parameter pc_root_behavior  root behavior of this robot
             */
            inline void SetRootBehavior(CCI_Behavior<TRobotState>* pc_root_behavior) {
                m_pcRootBehavior = pc_root_behavior;
            }

            /**
             * @brief Returns the XML configuration tree of the robot.
             * @return XML configuration tree
             */
            inline const TConfigurationNode& GetConfigurationTree() {
                return m_tConfigurationTree;
            }

            /**
             * @brief Returns the temporary map of the robot's data.
             * The temporary map is designed to hold temporary data, like compution results.
             * Thus, it will be cleaned before every TimeStep.
             * @return temporary map of type <string,any>
             */
            inline TAnyPropertyMap& GetTemporaryMap() {
                return m_tTemporaryMap;
            }

            /**
             * @brief Returns the persistent map of the robot's data.
             * The persistent map is designed to hold persistent data, like
             * global variables, statistics and confgurationd data.
             * @return persistent map of type <string,any>
             */
            inline TAnyPropertyMap& GetPersistentMap() {
                return m_tPersistentMap;
            }


        protected:

            /** The robot. */
            CCI_Robot* m_pcRobot;

            /** The robot's controller. */
            CCI_BehaviorController<TRobotState>* m_pcController;

            /** The robot's root behavior. */
            CCI_Behavior<TRobotState>* m_pcRootBehavior;

            /** The robot's XML configuration. */
            TConfigurationNode m_tConfigurationTree;

            /** Map for storing temporary data of the robot. */
            TAnyPropertyMap m_tTemporaryMap;

            /** Map for storing persistent data of the robot. */
            TAnyPropertyMap m_tPersistentMap;

    };

}

#endif

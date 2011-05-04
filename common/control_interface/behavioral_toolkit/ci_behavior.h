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
 * @file <common/control_interface/behavioral_toolkit/ci_behavior.h>
 *
 * @brief This file provides the control interface definition for a robot behavior.
 * A behavior can be composed by other behaviors.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Nithin Mathews  - <nmathews@ulb.ac.be>
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Giovanni Pini   - <gpini@iridia.ulb.ac.be>
 */

#ifndef CI_BEHAVIOR_H
#define CI_BEHAVIOR_H

namespace argos {
    template<class TRobotState> class CCI_Behavior;
}

#include <map>
#include <string>

#include <argos2/common/control_interface/behavioral_toolkit/ci_robot_data.h>

namespace argos {

    template<class TRobotState> class CCI_Behavior {

        public:

            /**
             * Constructor.
             * @param  pc_robot_data         robot data object, to store information accessible to all the behaviors
             * @param  str_behavior_id       Id of the behavior
             */
            CCI_Behavior(CCI_RobotData<TRobotState>* pc_robot_data,
                         const std::string& str_behavior_id) :
                m_pcRobotData(pc_robot_data),
                m_strBehaviorId(str_behavior_id) {}

            /**
             * @brief Destructor.
             */
            virtual ~CCI_Behavior() {}

            /**
             * @brief Performs initialization of the behavior.
             */
            virtual void Init(TRobotState& c_robot_state) = 0;

            /**
             * @brief resets the behavior.
             */
            inline void Reset(TRobotState& c_robot_state) {
                Init(c_robot_state);
            }

            /**
             * @brief Adds a behavior in the sub-behaviors map.
             * @param pc_behavior the behavior to be added.
             */
            inline void AddSubBehavior(CCI_Behavior* pc_behavior) {
                m_tSubBehaviors.insert(std::pair<std::string, CCI_Behavior<TRobotState>*> (pc_behavior->GetBehaviorId(), pc_behavior));
            }

            /**
             * @brief The main behavior method. It reads from and can write to the robot state.
             * Any change to actuator values are written by the behavior_controller only after
             * the execution of all behaviors steps. If no actual change in the actuators is
             * wanted, then a state copy should be used instead of the actual state.
             * @param c_robot_state The current state of the robot (sensors and actuators)
             */
            virtual void Step(TRobotState& c_robot_state) = 0;

            /**
             * @brief The cleanup method of the behavior.
             * @param c_robot_state The current state of the robot (sensors and actuators)
             */
            virtual void Destroy(TRobotState& c_robot_state) = 0;

            /**
             * @brief Returns the ID of the behavior.
             * @return ID of the behavior as specified in the constructor
             */
            inline const std::string GetBehaviorId() const {
                return m_strBehaviorId;
            }

            /**
             * @brief Sets an object in a TAnyPropertyMap map.
             * @parameter  c_map   map to set the value in
             * @parameter  str_key  key to store the value under (string)
             * @parameter  t_value  the value
             */
            template<typename T> void SetValueInMap(TAnyPropertyMap& t_property_map,
                                                    const std::string& str_key,
                                                    const T& t_value) {
            	t_property_map[str_key] = t_value;
            }

            /**
             * @brief Returns an object stored in a TAnyPropertyMap map.
             * The method exits with an error message when a non-existent key is requested.
             * @parameter  c_map   map to get the value from
             * @parameter  str_key  key the value is stored under (string)
             * @return     the value if exists
             */
            template<typename T> T GetValueFromMap(TAnyPropertyMap& t_property_map,
                                                   const std::string& str_key) const {
                return any_cast<T>(t_property_map[str_key]);
            }

            /**
             * @brief Sets a boolean in a TAnyPropertyMap map.
             * @parameter  c_map   map to set the value in
             * @parameter  str_key  key to store the value under (string)
             * @parameter  b_value  boolean value
             */
            inline void SetBooleanInMap(TAnyPropertyMap& t_property_map,
                                        const std::string& str_key,
                                        const bool b_value) {
            	t_property_map[str_key] = b_value;
            }

            /**
             * @brief Returns a boolean value stored in a TAnyPropertyMap map.
             * The method exits with an error message when a non-existent key is requested.
             * @parameter  c_map   map to get the value from
             * @parameter  str_key    key the value is stored under (string)
             * @return boolean value if exists
             */
            inline bool GetBooleanFromMap(TAnyPropertyMap& t_property_map,
                                          const std::string& str_key) const {
                return any_cast<bool>(t_property_map[str_key]);
            }

        protected:


            typedef std::map<const std::string, CCI_Behavior<TRobotState>*> TSubBehaviors;

            TSubBehaviors m_tSubBehaviors;

            CCI_RobotData<TRobotState>* m_pcRobotData;

            const std::string& m_strBehaviorId;

    };
}

#endif

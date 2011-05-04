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
 * @file <common/control_interface/behavioral_toolkit/ci_robot_state.h>
 *
 * @brief This file provides the control interface definition for the robot state
 * needed by the behavioral toolkit. In particular, this type represents
 * a generalization of the different robot state objects. Therefore, it
 * should encapsulate all the methods for accessing sensors and
 * actuators that are common to all the robots
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Nithin Mathews  - <nmathews@ulb.ac.be>
 * @author Giovanni Pini   - <gpini@iridia.ulb.ac.be>
 */

#ifndef CI_ROBOT_STATE_H
#define CI_ROBOT_STATE_H

namespace argos {
    class CCI_RobotState;
}

#include <argos2/common/control_interface/behavioral_toolkit/utility_classes/helper.h>
#include <argos2/common/control_interface/ci_robot.h>
#include <argos2/common/control_interface/ci_clock_sensor.h>

namespace argos {

    class CCI_RobotState {

        public:

            /**
            * Constructor.
            * @param  pc_robot the robot object
            */
            CCI_RobotState(CCI_Robot& c_robot) :
                m_pcRobot(&c_robot),
                m_pcClockSensor(NULL),
                m_bIsUsingClockSensor(false),
                m_fClockTickLength(0.0) {
            }

            /**
            * Copy constructor.
            */
            CCI_RobotState(const CCI_RobotState& c_state) {
                *this = c_state;
            }

            /**
             * @brief Operator =.
             */
            CCI_RobotState& operator=(const CCI_RobotState& c_state) {

                if (this != &c_state) {
                    m_pcRobot = c_state.m_pcRobot;
                    m_pcClockSensor = c_state.m_pcClockSensor;
                    m_bIsUsingClockSensor = c_state.m_bIsUsingClockSensor;
                    m_fClockTickLength = c_state.m_fClockTickLength;
                }

                return *this;
            }

            /**
             * @brief Destructor.
             */
            virtual ~CCI_RobotState() {
            }

            /**
             *
             * @brief Initializes sensors and actuators declared in the XMl configuration
             *
             **/
            virtual void Init();

            /**
             *
             * @brief Reads sensor data and sets the robot state accordingly
             *
             **/
            virtual void ReadState() {
            }

            /**
             *
             * @brief Applies the actuator commands using the information in the robot state
             *
             **/
            virtual void ApplyState();

            /**
             *
             * @brief Returns the ID of the robot
             * @return The id of the robot
             *
             **/
            virtual inline const std::string& GetRobotId() const {
                return m_pcRobot->GetRobotId();
            }

            /**
             *
             * @brief Returns a pointer to the CI robot object
             * @return Pointer to the CI robot object
             *
             **/
            virtual inline CCI_Robot& GetRobot() {
                return *m_pcRobot;
            }

            /**
             *
             * @brief Returns the time since the controller was started
             * @return Elapsed time since controller started running
             *
             **/
            virtual inline const Real GetElapsedTime() {
                CHECK_IS_SENSOR_USED_HELPER(CLOCK_SENSOR_XML_NAME,m_bIsUsingClockSensor,"GetElapsedTime");
                return m_pcClockSensor->GetElapsedTime();
            }

            /**
             *
             * @brief Checks if a given time period is elapsed since the step buffer was initialized or reset
             * @see CCI_ClockSensor
             * @see InitialiseClockSensorActionPeriodCounter()
             * @see ResetClockSensorActionPeriodCounter()
             * @param f_seconds amount of time that should be checked as elapsed period
             * @param n_current_step_buffer counter used to evaluate time
             * @return CCI_ClockSensor constant to indicate whether the period as passed or not
             **/
            virtual inline const SInt32 DoActionForPeriod(Real f_seconds,
                                                          SInt32* n_current_step_buffer) {
                CHECK_IS_SENSOR_USED_HELPER(CLOCK_SENSOR_XML_NAME,m_bIsUsingClockSensor,"DoActionForPeriod");
                return m_pcClockSensor->DoActionForPeriod(f_seconds,
                                                          n_current_step_buffer);
            }

            /**
             *
             * @brief Initializes a counter used for evaluating time
             * @see CCI_ClockSensor
             * @see ResetClockSensorActionPeriodCounter()
             * @see DoActionForPeriod()
             * @param n_counter counter used to evaluate time, which will be initialized
             **/
            virtual inline void InitialiseClockSensorActionPeriodCounter(SInt32* n_counter) {
                CHECK_IS_SENSOR_USED_HELPER(CLOCK_SENSOR_XML_NAME,m_bIsUsingClockSensor,"InitialiseClockSensorActionPeriodCounter");
                m_pcClockSensor->InitialiseActionPeriodCounter(n_counter);
            }

            /**
             *
             * @brief Resets a counter used for evaluating time
             * @see CCI_ClockSensor
             * @see InitialiseClockSensorActionPeriodCounter()
             * @see DoActionForPeriod()
             * @param n_counter counter used to evaluate time, which will be initialized
             **/
            virtual inline void ResetClockSensorActionPeriodCounter(SInt32* n_counter) {
                CHECK_IS_SENSOR_USED_HELPER(CLOCK_SENSOR_XML_NAME,m_bIsUsingClockSensor,"ResetClockSensorActionPeriodCounter");
                m_pcClockSensor->ResetActionPeriodCounter(n_counter);
            }

        protected:

            //Pointers to robot object
            CCI_Robot* m_pcRobot;

            //Pointers to sensors objects
            CCI_ClockSensor* m_pcClockSensor;

            //Sensors booleans: which sensors are declared in XMl and can be used
            bool m_bIsUsingClockSensor;

            //Other variables related to sensors
            Real m_fClockTickLength;

            /* XML sensor names */
            static const std::string CLOCK_SENSOR_XML_NAME;

    };

}

#endif

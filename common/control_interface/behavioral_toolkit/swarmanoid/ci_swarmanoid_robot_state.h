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
 * @file <common/control_interface/behavioral_toolkit/swarmanoid/ci_swarmanoid_robot_state.h>
 *
 * @brief This file provides the definition for the behavioral toolkit state of the swarmanoid robots.
 * It is intended to provide all the functionalities that are shared by the swarmanoid robots, such
 * as the range and bearing support
 *
 * @author Giovanni Pini  - <gpini@iridia.ulb.ac.be>
 */

#ifndef CI_SWARMANOID_ROBOT_STATE_H
#define CI_SWARMANOID_ROBOT_STATE_H

namespace argos {
    class CCI_SwarmanoidRobotState;
}

#include <argos2/common/control_interface/ci_robot.h>
#include <argos2/common/control_interface/behavioral_toolkit/ci_robot_state.h>
#include <argos2/common/control_interface/behavioral_toolkit/utility_classes/helper.h>
#include <argos2/common/control_interface/swarmanoid/ci_range_and_bearing_sensor.h>
#include <argos2/common/control_interface/swarmanoid/ci_battery_sensor.h>
#include <argos2/common/control_interface/swarmanoid/ci_range_and_bearing_actuator.h>

namespace argos {

    class CCI_SwarmanoidRobotState : public CCI_RobotState {

        public:

            /**
             * Constructor.
             *
             * @param pc_robot Pointer to the robot object
             *
             */
            CCI_SwarmanoidRobotState(CCI_Robot& pc_robot) :
                CCI_RobotState(pc_robot),

                /** Initialize all the sensors*/
                m_pcRABSensor              (NULL),
                m_pcBatterySensor          (NULL),

                /** Initialize all sensors booleans */
                m_bIsUsingRABSensor        (false),
                m_bIsUsingBatterySensor    (false),

                /** Initialize sensor variables */
                m_unRABLastCheckedPacketId (0),

                /** Initialize all the actuators */
                m_pcRABActuator            (NULL),

                /** Initialize all actuators booleans */
                m_bIsUsingRABActuator      (false),

                /** Initialize the actuated values */
                m_bIsLastRABPacketSent     (true) {
                ::memset(m_tRABPacketDataToSend, 0, sizeof(TRangeAndBearingReceivedPacket::TRangeAndBearingData));
            }

            /**
             *
             * Copy constructor.
             *
             **/
            CCI_SwarmanoidRobotState(const CCI_SwarmanoidRobotState& c_state) : CCI_RobotState(c_state) {
                *this = c_state;
            }

            /**
             *
             * = operator overriding. Used with the same semantic of the copy constructor
             *
             **/
            CCI_SwarmanoidRobotState& operator=(const CCI_SwarmanoidRobotState& c_state) {

                if (this != &c_state) {

                    CCI_RobotState::operator=(c_state);

                    /** Copy the references to the sensors */
                    m_pcRABSensor     = c_state.m_pcRABSensor;
                    m_pcBatterySensor = c_state.m_pcBatterySensor;

                    /** Copy the sensors booleans */
                    m_bIsUsingRABSensor     = c_state.m_bIsUsingRABSensor;
                    m_bIsUsingBatterySensor = c_state.m_bIsUsingBatterySensor;

                    /** Copy the sensors variables */
                    m_unRABLastCheckedPacketId = c_state.m_unRABLastCheckedPacketId;

                    /** Copy the references to the actuators */
                    m_pcRABActuator = c_state.m_pcRABActuator;

                    /** Copy the actuators booleans */
                    m_bIsUsingRABActuator = c_state.m_bIsUsingRABActuator;

                    /** Copy the actuated commands */
                    m_bIsLastRABPacketSent  = c_state.m_bIsLastRABPacketSent;
                    *m_tRABPacketDataToSend = *c_state.m_tRABPacketDataToSend;

                    /** Copy others actuator variables */
                    m_fBatteryMinSafeValue = c_state.m_fBatteryMinSafeValue;

                }

                return *this;
            }

            /**
             *
             * Destructor.
             *
             **/
            virtual ~CCI_SwarmanoidRobotState() {
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////
            //   MISC FUNCTIONS
            /////////////////////////////////////////////////////////////////////////////////////////////////

            /**
             *
             * @brief Initializes all the sensors and actuators declared in the XML.
             *
             **/
            virtual void Init();

            /**
             *
             * @brief Reads sensor data and sets the robot state accordingly.
             *
             **/
            virtual void ReadState();

            /**
             *
             * @brief Apply the actuator commands with the robot state ones.
             *
             **/
            virtual void ApplyState();

            /////////////////////////////////////////////////////////////////////////////////////////////////
            //   SENSORS GETTER METHODS, SENSOR READINGS
            /////////////////////////////////////////////////////////////////////////////////////////////////

            /**
             *
             * @brief Returns the id of the last received RAB packet.
             *
             * @return the packed id of the last received RAB packet.
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline const UInt64 GetRABLatestPacketId() {
                CHECK_IS_SENSOR_USED_HELPER(RAB_SENSOR_XML_NAME,m_bIsUsingRABSensor,"GetRABLatestPacketId");
                return m_pcRABSensor->GetLatestPacketId();
            }

            /**
             *
             * @brief Returns the id of the last checked RAB packet.
             *
             * @return the packed id of the last checked RAB packet.
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline const UInt64 GetRABLastCheckedPacketId() {
                CHECK_IS_SENSOR_USED_HELPER(RAB_SENSOR_XML_NAME,m_bIsUsingRABSensor,"GetRABLastCheckedPacketId");
                return m_unRABLastCheckedPacketId;
            }

            /**
             *
             * @brief Returns the id of the last received RAB packets.
             *
             * @return RAB map of last received packets.
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline const CCI_RangeAndBearingSensor::TLastReceivedPackets GetRABLastReceivedPackets() {
                CHECK_IS_SENSOR_USED_HELPER(RAB_SENSOR_XML_NAME,m_bIsUsingRABSensor,"GetRABLastReceivedPackets");
                m_unRABLastCheckedPacketId = m_pcRABSensor->GetLatestPacketId();
                return m_pcRABSensor->GetLastReceivedPackets();
            }

            /**
             *
             * @brief Returns the RAB id corresponding to the string id passed as parameter.
             *
             * @param str_robot_id string id to be converted into RAB id
             *
             * @return the RAB id corresponding to the string id given.
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline const UInt8 GetRABRabIdFromRobotId(const std::string str_robot_id) {
                CHECK_IS_SENSOR_USED_HELPER(RAB_SENSOR_XML_NAME,m_bIsUsingRABSensor,"GetRABRabIdFromRobotId");
                return m_pcRABSensor->GetRabIdFromRobotId(str_robot_id);
            }

            /**
             *
             * @brief Returns the robot id corresponding to the RAB id passed as parameter.
             *
             * @param un_rab_id RAB id to be converted into robot id
             *
             * @return the robot id corresponding to the given RAB id.
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline const std::string GetRABRobotIdFromRabId(const UInt8 un_rab_id) {
                CHECK_IS_SENSOR_USED_HELPER(RAB_SENSOR_XML_NAME,m_bIsUsingRABSensor,"GetRABRobotIdFromRabId");
                return m_pcRABSensor->GetRobotIdFromRabId(un_rab_id);
            }

            /**
             *
             * @brief Returns the current battery voltage
             *
             * @return the voltage on the battery
             * @see CCI_BatterySensor
             *
             **/
            virtual inline const Real GetBatteryVoltage() {
                CHECK_IS_SENSOR_USED_HELPER(BATTERY_SENSOR_XML_NAME,m_bIsUsingBatterySensor,"GetBatteryVoltage");
                return m_pcBatterySensor->GetVoltage();
            }

            /**
             *
             * @brief Returns the minimum safe battery voltage
             *
             * @return safe voltage for the battery
             * @see CCI_BatterySensor
             *
             **/
            virtual inline const Real GetBatteryMinSafeVoltage() {
                CHECK_IS_SENSOR_USED_HELPER(BATTERY_SENSOR_XML_NAME,m_bIsUsingBatterySensor,"GetBatteryMinSafeVoltage");
                return m_fBatteryMinSafeValue;
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////
            //   ACTUATORS SETTERS METHODS
            /////////////////////////////////////////////////////////////////////////////////////////////////

            /**
             *
             * @brief Sets the data to be send through range and bearing
             * The data represents the 10 bytes RAB packet payload
             * @param t_data RAB data to send
             *
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline void SetRABPacketDataToSend( TRangeAndBearingReceivedPacket::TRangeAndBearingData& t_data) {
                CHECK_IS_ACTUATOR_USED_HELPER(RAB_ACTUATOR_XML_NAME,m_bIsUsingRABActuator,"SetRABPacketDataToSend");
                ::memcpy(m_tRABPacketDataToSend, t_data, sizeof(TRangeAndBearingReceivedPacket::TRangeAndBearingData));
                m_bIsLastRABPacketSent = false;
            }

            /**
             *
             * @brief Clears the data to be send by RAB
             * The method should be called at the beginning of the control step by the root behavior
             *
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline void ClearRABPacketData() {
                CHECK_IS_ACTUATOR_USED_HELPER(RAB_ACTUATOR_XML_NAME,m_bIsUsingRABActuator,"ClearRABPacketData");
                ::memset(m_tRABPacketDataToSend, 0, sizeof(TRangeAndBearingReceivedPacket::TRangeAndBearingData));
                m_bIsLastRABPacketSent = true;
            }

            /* Clears the messages received from the range and bearing. Call this at the end of your
             * time-step to be sure that at each time-step you only have the most recently received packets
             *
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline void ClearRABReceivedPackets() {
                assert(m_bIsUsingRABSensor);
                m_pcRABSensor->ClearRABReceivedPackets();
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////
            //   ACTUATORS GETTERS METHODS
            /////////////////////////////////////////////////////////////////////////////////////////////////


            /**
             *
             * @brief Checks if the last RAB data that was set has been send already
             *
             * @return true if the last RAB data was send
             *
             **/
            virtual inline bool IsLastRABPacketSent() {
                CHECK_IS_ACTUATOR_USED_HELPER(RAB_ACTUATOR_XML_NAME,m_bIsUsingRABActuator,"IsLastRABPacketSent");
                return m_bIsLastRABPacketSent;
            }

            /**
             *
             * @brief Gets the current RAB data to be send
             *
             * @return payload that will be set for the next RAB packet to send
             * @see CCI_RangeAndBearingSensor
             *
             **/
            virtual inline const TRangeAndBearingReceivedPacket::TRangeAndBearingData& GetRABPacketDataToSend() {
                CHECK_IS_ACTUATOR_USED_HELPER(RAB_ACTUATOR_XML_NAME,m_bIsUsingRABActuator,"GetRABPacketDataToSend");
                return m_tRABPacketDataToSend;
            }

        protected:

            /////////////////////////////////////////////////////////////////////////////////////////////////
            //    SENSORS
            /////////////////////////////////////////////////////////////////////////////////////////////////

            /** References to the sensors */
            CCI_RangeAndBearingSensor* m_pcRABSensor;
            CCI_BatterySensor*         m_pcBatterySensor;

            /** Sensors booleans */
            bool m_bIsUsingRABSensor;
            bool m_bIsUsingBatterySensor;

            /** Sensors readings variables */
            UInt64 m_unRABLastCheckedPacketId;

            /* XML sensor names */
            static const std::string RAB_SENSOR_XML_NAME;
            static const std::string BATTERY_SENSOR_XML_NAME;

            /////////////////////////////////////////////////////////////////////////////////////////////////
            //    ACTUATORS
            /////////////////////////////////////////////////////////////////////////////////////////////////

            /** References to the actuators */
            CCI_RangeAndBearingActuator* m_pcRABActuator;

            /** Actuators booleans */
            bool m_bIsUsingRABActuator;

            /** Actuators commands variables */
            bool m_bIsLastRABPacketSent;
            TRangeAndBearingReceivedPacket::TRangeAndBearingData m_tRABPacketDataToSend;

            /** Other actuators variables */
            Real  m_fBatteryMinSafeValue;

            /* XML actuator names */
            static const std::string RAB_ACTUATOR_XML_NAME;

    };

}

#endif

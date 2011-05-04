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
 * @file <common/control_interface/behavioral_toolkit/swarmanoid/footbot/ci_footbot_state.h>
 *
 * @brief This file provides the control interface behavioral toolkit definition for a foot-bot state.
 * Check file ci_robot_state.h for the full explanation.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#ifndef CI_FOOTBOT_STATE_H
#define CI_FOOTBOT_STATE_H

namespace argos {
    class CCI_FootBotState;
}

#include <argos2/common/control_interface/behavioral_toolkit/swarmanoid/ci_swarmanoid_robot_state.h>
#include <argos2/common/utility/math/angles.h>

/** Sensors includes */
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_base_ground_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_proximity_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_distance_scanner_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_encoder_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_light_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_motor_ground_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_wheel_speed_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_torque_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_encoder_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_gripper_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_ceiling_camera_sensor.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_omnidirectional_camera_sensor.h>

/** Actuators includes */
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_beacon_actuator.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_wheels_actuator.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_gripper_actuator.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_leds_actuator.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_actuator.h>
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_distance_scanner_actuator.h>

namespace argos {

    class CCI_FootBotState: public CCI_SwarmanoidRobotState {

    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //    CONSTRUCTORS
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         * Constructor.
         *
         * @param pc_robot Pointer to the robot object
         *
         */
        CCI_FootBotState(CCI_Robot& pc_robot) :
            CCI_SwarmanoidRobotState(pc_robot),

            /** Initialize all the sensors */
            m_pcBaseGroundSensor            (NULL),
            m_pcProximitySensor             (NULL),
            m_pcDistanceScannerSensor       (NULL),
            m_pcEncoderSensor               (NULL),
            m_pcLightSensor                 (NULL),
            m_pcMotorGroundSensor           (NULL),
            m_pcWheelSpeedSensor            (NULL),
            m_pcTurretTorqueSensor          (NULL),
            m_pcTurretEncoderSensor         (NULL),
            m_pcGripperSensor               (NULL),
            m_pcCeilingCameraSensor         (NULL),
            m_pcOmnidirectionalCameraSensor (NULL),

            /** Initialize all sensors booleans */
            m_bIsUsingBaseGroundSensor              (false),
            m_bIsUsingProximitySensor               (false),
            m_bIsUsingDistanceScannerSensor         (false),
            m_bIsUsingEncoderSensor                 (false),
            m_bIsUsingLightSensor                   (false),
            m_bIsUsingMotorGroundSensor             (false),
            m_bIsUsingWheelSpeedSensor              (false),
            m_bIsUsingTurretTorqueSensor            (false),
            m_bIsUsingTurretEncoderSensor           (false),
            m_bIsUsingGripperSensor                 (false),
            m_bIsUsingCeilingCameraSensor           (false),
            m_bIsUsingOmnidirectionalCameraSensor   (false),

            /** Initialize other sensor related variables */
            m_bResetEncoderSensor                   (false),

            /** Initialize all the actuators */
            m_pcBeaconActuator          (NULL),
            m_pcWheelsActuator          (NULL),
            m_pcGripperActuator         (NULL),
            m_pcLedsActuator            (NULL),
            m_pcTurretActuator          (NULL),
            m_pcDistanceScannerActuator (NULL),

            /** Initialize all actuators booleans */
            m_bIsUsingBeacon                  (false),
            m_bIsUsingWheelsActuator          (false),
            m_bIsUsingGripperActuator         (false),
            m_bIsUsingLeds                    (false),
            m_bIsUsingTurretActuator          (false),
            m_bIsUsingDistanceScannerActuator (false),

            /** Initialize all actuators refresh booleans */
            m_bRefreshBeacon                       (false),
            m_bRefreshWheelsActuator               (false),
            m_bRefreshGripperActuator              (false),
            m_bRefreshLeds                         (false),
            m_bRefreshTurretActuator               (false),
            m_bRefreshDistanceScannerEnabled       (false),
            m_bRefreshDistanceScannerActuatorAngle (false),
            m_bRefreshDistanceScannerActuatorRPM   (false),
            m_bRefreshProximityCalibration         (false),
            m_bRefreshBaseGroundSensorCalibration  (false),

            /** Initialize the actuated values */
            m_cActuatedBeaconColor            (CColor::BLACK),
            m_fActuatedLeftWheelSpeed         (0.0),
            m_fActuatedRightWheelSpeed        (0.0),
            m_cActuatedGripperAperture        (CCI_FootBotGripperActuator::UNLOCKED),
            m_eActuatedTurretMode             (CCI_FootBotTurretActuator::MODE_PASSIVE),
            m_cActuatedTurretRotation         (0.0),
            m_nActuatedTurretRotationSpeed    (0),
            m_bActuatedDistanceScannerEnabled (false),
            m_fActuatedDistanceScannerAngle   (0.0),
            m_fActuatedDistanceScannerRPM     (0.0) {

            m_tActuatedLedColors = CCI_FootBotLedsActuator::TLedSettings(NUM_LEDS);
            for (UInt8 i = 0; i < NUM_LEDS; i++)
                m_tActuatedLedColors[i] = CColor::BLACK;
        }

        /**
         *
         * Copy Constructor.
         *
         */
        CCI_FootBotState(const CCI_FootBotState& c_footbot_state) : CCI_SwarmanoidRobotState(c_footbot_state)
        {
            *this = c_footbot_state;
        }

        /**
         *
         * = operator overriding. Used with the same semantic of the copy constructor
         *
         */
        CCI_FootBotState& operator=(const CCI_FootBotState& c_footbot_state)
        {

            if (this != &c_footbot_state) {

                CCI_SwarmanoidRobotState::operator=(c_footbot_state);

                /** Copy the references to the sensors */
                m_pcBaseGroundSensor            = c_footbot_state.m_pcBaseGroundSensor;
                m_pcProximitySensor             = c_footbot_state.m_pcProximitySensor;
                m_pcDistanceScannerSensor       = c_footbot_state.m_pcDistanceScannerSensor;
                m_pcEncoderSensor               = c_footbot_state.m_pcEncoderSensor;
                m_pcLightSensor                 = c_footbot_state.m_pcLightSensor;
                m_pcMotorGroundSensor           = c_footbot_state.m_pcMotorGroundSensor;
                m_pcWheelSpeedSensor            = c_footbot_state.m_pcWheelSpeedSensor;
                m_pcTurretTorqueSensor          = c_footbot_state.m_pcTurretTorqueSensor;
                m_pcTurretEncoderSensor         = c_footbot_state.m_pcTurretEncoderSensor;
                m_pcCeilingCameraSensor         = c_footbot_state.m_pcCeilingCameraSensor;
                m_pcOmnidirectionalCameraSensor = c_footbot_state.m_pcOmnidirectionalCameraSensor;

                /** Copy the sensors booleans */
                m_bIsUsingBaseGroundSensor              = c_footbot_state.m_bIsUsingBaseGroundSensor;
                m_bIsUsingProximitySensor               = c_footbot_state.m_bIsUsingProximitySensor;
                m_bIsUsingDistanceScannerSensor         = c_footbot_state.m_bIsUsingDistanceScannerSensor;
                m_bIsUsingEncoderSensor                 = c_footbot_state.m_bIsUsingEncoderSensor;
                m_bIsUsingLightSensor                   = c_footbot_state.m_bIsUsingLightSensor;
                m_bIsUsingMotorGroundSensor             = c_footbot_state.m_bIsUsingMotorGroundSensor;
                m_bIsUsingWheelSpeedSensor              = c_footbot_state.m_bIsUsingWheelSpeedSensor;
                m_bIsUsingTurretTorqueSensor            = c_footbot_state.m_bIsUsingTurretTorqueSensor;
                m_bIsUsingTurretEncoderSensor           = c_footbot_state.m_bIsUsingTurretEncoderSensor;
                m_bIsUsingCeilingCameraSensor           = c_footbot_state.m_bIsUsingCeilingCameraSensor;
                m_bIsUsingOmnidirectionalCameraSensor   = c_footbot_state.m_bIsUsingOmnidirectionalCameraSensor;

                /** Copy other sensor related variables */
                m_bResetEncoderSensor     = c_footbot_state.m_bResetEncoderSensor;
                m_tLightSensorReadings    = c_footbot_state.m_tLightSensorReadings;

                /** Copy the references to the actuators */
                m_pcBeaconActuator          = c_footbot_state.m_pcBeaconActuator;
                m_pcWheelsActuator          = c_footbot_state.m_pcWheelsActuator;
                m_pcGripperActuator         = c_footbot_state.m_pcGripperActuator;
                m_pcLedsActuator            = c_footbot_state.m_pcLedsActuator;
                m_pcTurretActuator          = c_footbot_state.m_pcTurretActuator;
                m_pcDistanceScannerActuator = c_footbot_state.m_pcDistanceScannerActuator;

                /** Copy the actuators booleans */
                m_bIsUsingBeacon                  = c_footbot_state.m_bIsUsingBeacon;
                m_bIsUsingWheelsActuator          = c_footbot_state.m_bIsUsingWheelsActuator;
                m_bIsUsingGripperActuator         = c_footbot_state.m_bIsUsingGripperActuator;
                m_bIsUsingLeds                    = c_footbot_state.m_bIsUsingLeds;
                m_bIsUsingTurretActuator          = c_footbot_state.m_bIsUsingTurretActuator;
                m_bIsUsingDistanceScannerActuator = c_footbot_state.m_bIsUsingDistanceScannerActuator;

                /** Copy the actuators refresh booleans */
                m_bRefreshBeacon                       = c_footbot_state.m_bRefreshBeacon;
                m_bRefreshWheelsActuator               = c_footbot_state.m_bRefreshWheelsActuator;
                m_bRefreshGripperActuator              = c_footbot_state.m_bRefreshGripperActuator;
                m_bRefreshLeds                         = c_footbot_state.m_bRefreshLeds;
                m_bRefreshTurretActuator               = c_footbot_state.m_bRefreshTurretActuator;
                m_bRefreshDistanceScannerEnabled       = c_footbot_state.m_bRefreshDistanceScannerEnabled;
                m_bRefreshDistanceScannerActuatorAngle = c_footbot_state.m_bRefreshDistanceScannerActuatorAngle;
                m_bRefreshDistanceScannerActuatorRPM   = c_footbot_state.m_bRefreshDistanceScannerActuatorRPM;

                /** Copy the actuated commands */
                m_cActuatedBeaconColor                = c_footbot_state.m_cActuatedBeaconColor;
                m_fActuatedLeftWheelSpeed             = c_footbot_state.m_fActuatedLeftWheelSpeed;
                m_fActuatedRightWheelSpeed            = c_footbot_state.m_fActuatedRightWheelSpeed;
                m_cActuatedGripperAperture            = c_footbot_state.m_cActuatedGripperAperture;
                m_tActuatedLedColors                  = c_footbot_state.m_tActuatedLedColors;
                m_eActuatedTurretMode                 = c_footbot_state.m_eActuatedTurretMode;
                m_cActuatedTurretRotation             = c_footbot_state.m_cActuatedTurretRotation;
                m_nActuatedTurretRotationSpeed        = c_footbot_state.m_nActuatedTurretRotationSpeed;
                m_bActuatedDistanceScannerEnabled     = c_footbot_state.m_bActuatedDistanceScannerEnabled;
                m_fActuatedDistanceScannerAngle       = c_footbot_state.m_fActuatedDistanceScannerAngle;
                m_fActuatedDistanceScannerRPM         = c_footbot_state.m_fActuatedDistanceScannerRPM;
                m_bRefreshProximityCalibration        = c_footbot_state.m_bRefreshProximityCalibration;
                m_bRefreshBaseGroundSensorCalibration = c_footbot_state.m_bRefreshBaseGroundSensorCalibration;
            }

            return *this;
        }

        /**
         *
         * Destructor.
         *
         **/
        virtual ~CCI_FootBotState()
        {
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
        virtual void ReadState() {}

        /**
         *
         * @brief Applies the actuator commands with the robot state ones.
         *
         **/
        virtual void ApplyState();


        /** Number of sensor readings (for those sensors returning arrays of values) */
        static const UInt32 NUM_BASE_GROUND_SENSOR_READINGS;
        static const UInt32 NUM_PROXIMITY_SENSOR_READINGS;
        static const UInt32 NUM_LIGHT_SENSOR_READINGS;
        static const UInt32 NUM_MOTOR_GROUND_SENSOR_READINGS;

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //   SENSORS GETTER METHODS, SENSOR READINGS
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Returns the base ground sensors readings
         * The 8 base ground sensors are positioned underneath the LED ring, where the proximity sensors are.
         *
         * @return the base ground sensors readings
         * @see CCI_FootBotBaseGroundSensor
         *
         **/
        inline virtual const CCI_FootBotBaseGroundSensor::TReadings& GetBaseGroundSensorReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(BASE_GROUND_SENSOR_XML_NAME, m_bIsUsingBaseGroundSensor, "GetBaseGroundSensorReadings");
            return m_pcBaseGroundSensor->GetReadings();
        }

        /**
         *
         * @brief Returns the proximity sensors readings
         *
         * @return the proximity sensors readings
         * @see CCI_FootBotProximitySensor
         *
         **/
        inline virtual const CCI_FootBotProximitySensor::TReadings& GetProximitySensorReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(PROXIMITY_SENSORS_XML_NAME, m_bIsUsingProximitySensor, "GetProximitySensorReadings");
            return m_pcProximitySensor->GetReadings();
        }

        /**
         *
         * @brief Returns the map with all the long range distance scanner readings of the latest
         * 6 quartets of readings  ordered by angle
         *
         * @return the distance scanner readings
         * @see CCI_FootBotDistanceScannerSensor
         *
         **/
        inline virtual const CCI_FootBotDistanceScannerSensor::TReadingsMap& GetDistanceScannerLongReadingsMap()
        {
            CHECK_IS_SENSOR_USED_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME, m_bIsUsingDistanceScannerSensor, "GetDistanceScannerLongReadingsMap");
            return m_pcDistanceScannerSensor->GetLongReadingsMap();
        }

        /**
         *
         * @brief Returns the map with all the short range distance scanner readings of the latest
         * 6 quartets of readings  ordered by angle
         *
         * @return the distance scanner readings
         * @see CCI_FootBotDistanceScannerSensor
         *
         **/
        inline virtual const CCI_FootBotDistanceScannerSensor::TReadingsMap& GetDistanceScannerShortReadingsMap()
        {
            CHECK_IS_SENSOR_USED_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME, m_bIsUsingDistanceScannerSensor, "GetDistanceScannerShortReadingsMap");
            return m_pcDistanceScannerSensor->GetShortReadingsMap();
        }

        /**
         *
         * @brief Returns the map with all the distance scanner readings of the latest
         * 6 quartets of readings  ordered by angle
         *
         * @return the distance scanner readings
         * @see CCI_FootBotDistanceScannerSensor
         *
         **/
        inline virtual const CCI_FootBotDistanceScannerSensor::TReadingsMap& GetDistanceScannerReadingsMap()
        {
            CHECK_IS_SENSOR_USED_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME, m_bIsUsingDistanceScannerSensor, "GetDistanceScannerReadingsMap");
            return m_pcDistanceScannerSensor->GetReadingsMap();
        }

        /**
         *
         * @brief Returns the encoder readings
         *
         * @return the encoder's readings
         * @see CCI_FootBotEncoderSensor
         *
         **/
        inline virtual const CCI_FootBotEncoderSensor::SReading& GetEncoderSensorReading()
        {
            CHECK_IS_SENSOR_USED_HELPER(ENCODER_SENSOR_XML_NAME, m_bIsUsingEncoderSensor, "GetEncoderSensorReading");
            return m_pcEncoderSensor->GetReading();
        }

        /**
         *
         * @brief Sets the encoder sensor readings to 0
         *
         * @return
         * @see CCI_FootBotEncoderSensor
         *
         **/
        inline virtual void ResetEncoderSensorReading()
        {
            CHECK_IS_SENSOR_USED_HELPER(ENCODER_SENSOR_XML_NAME, m_bIsUsingEncoderSensor, "ResetEncoderSensorReading");
            m_bResetEncoderSensor = true;
        }

        /**
         *
         * @brief Returns the light sensors readings and angles
         *
         * @return the light sensors readings and angles
         * @see CCI_FootBotLightSensor
         *
         **/
        inline virtual const CCI_FootBotLightSensor::TReadings& GetLightSensorReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(LIGHT_SENSOR_XML_NAME, m_bIsUsingLightSensor, "GetLightSensorReadings");
            return m_pcLightSensor->GetReadings();
        }

        /**
         *
         * @brief Returns the motor ground sensors readings
         * The 4 motor ground sensors are positioned underneath the foot-bot, between the 2 tracks
         *
         * @return the motor ground sensors readings
         * @see CCI_FootBotMotorGroundSensor
         *
         **/
        inline virtual const CCI_FootBotMotorGroundSensor::TReadings& GetMotorGroundSensorReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(MOTOR_GROUND_SENSOR_XML_NAME, m_bIsUsingMotorGroundSensor, "GetMotorGroundSensorReadings");
            return m_pcMotorGroundSensor->GetReadings();
        }

        /**
         *
         * @brief Returns the wheels speed
         * The wheels speed is expressed as cm/s
         *
         * @return the wheels speed
         * @see CCI_FootBotWheelSpeedSensor
         *
         **/
        inline virtual const CCI_FootBotWheelSpeedSensor::TReading& GetWheelsSpeed()
        {
            CHECK_IS_SENSOR_USED_HELPER(WHEEL_SPEED_SENSOR_XML_NAME, m_bIsUsingWheelSpeedSensor, "GetWheelsSpeed");
            return m_pcWheelSpeedSensor->GetReading();
        }

        /**
         *
         * @brief Returns the turret rotation (LED ring-gripper)
         * The turret rotation is expressed in radians. Looking from above positive values correspond to a clockwise rotation.
         * The rotation is zero when the gripper faces the forward direction of the tracks.
         *
         * @return the turret rotation angle
         * @see CCI_FootBotTurretEncoderSensor
         *
         **/
        inline virtual const CRadians& GetTurretRotation()
        {
            CHECK_IS_SENSOR_USED_HELPER(TURRET_ENCODER_SENSOR_XML_NAME, m_bIsUsingTurretEncoderSensor, "GetTurretRotation");
            return m_pcTurretEncoderSensor->GetRotation();
        }

        /**
         *
         * @brief Returns the torque on the turret (LED ring-gripper)
         * Notice that the torque can be measured only if the turret is in active mode.
         *
         * @return the torque on the turret
         * @see CCI_FootBotTurretTorqueSensor
         *
         **/
        inline virtual Real GetTurretTorque()
        {
            CHECK_IS_SENSOR_USED_HELPER(TURRET_TORQUE_SENSOR_XML_NAME, m_bIsUsingTurretTorqueSensor, "GetTurretTorque");
            return (m_pcTurretTorqueSensor->GetReading()).EngineTorque;
        }

        /**
         *
         * @brief Returns the XY traction on the turret (LED ring-gripper)
         * Traction is expressed as value along the XY axis of the robot.
         *
         * @return the traction on the turret, XY components
         * @see CCI_FootBotTurretTorqueSensor
         *
         **/
        inline virtual const CVector2& GetTractionXY()
        {
            CHECK_IS_SENSOR_USED_HELPER(TURRET_TORQUE_SENSOR_XML_NAME, m_bIsUsingTurretTorqueSensor, "GetTractionXY");
            return (m_pcTurretTorqueSensor->GetReading()).TractionXY;
        }

        /**
         *
         * @brief Returns the polar traction on the turret (LED ring-gripper)
         * Traction is expressed as angle and magnitude
         *
         * @return the traction on the turret, polar components
         * @see CCI_FootBotTurretTorqueSensor
         *
         **/
        inline virtual const CCI_FootBotTurretTorqueSensor::SReading::STractionPolar& GetTractionPolar()
        {
            CHECK_IS_SENSOR_USED_HELPER(TURRET_TORQUE_SENSOR_XML_NAME, m_bIsUsingTurretTorqueSensor, "GetTractionPolar");
            return (m_pcTurretTorqueSensor->GetReading()).TractionPolar;
        }

        /**
         *
         * @brief Returns the current gripper aperture
         * The aperture is expressed in radians
         *
         * @return current gripper aperture
         * @see CCI_FootBotGripperSensor
         *
         **/
        inline virtual const CRadians& GetGripperAperture()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_SENSOR_XML_NAME, m_bIsUsingGripperSensor, "GetGripperAperture");
            return m_pcGripperSensor->GetReading().GripperAperture;
        }

        /**
         *
         * @brief Check if an object is grippable
         *
         *
         * @return true if an object is grippable
         * @see CCI_FootBotGripperSensor
         *
         **/
        //            inline virtual const bool IsObjectInGripper() {
        //                CHECK_IS_SENSOR_USED_HELPER(GRIPPER_SENSOR_XML_NAME, m_bIsUsingGripperSensor, "IsObjectInGripper");
        //                return m_pcGripperSensor->IsObjectInGripper();
        //            }


        /**
         * TODO: this methods might not be needed/possible to use in the BT. Evaluate. Arne 28/05/2010
            inline virtual void EnableCeilingCamera() {
                CHECK_IS_SENSOR_USED_HELPER(CEILING_CAMERA_SENSOR_XML_NAME, m_bIsUsingCeilingCameraSensor, "EnableCeilingCamera");
                return m_pcCeilingCameraSensor->Enable();
            }
            inline virtual void DisableCeilingCamera() {
                CHECK_IS_SENSOR_USED_HELPER(CEILING_CAMERA_SENSOR_XML_NAME, m_bIsUsingCeilingCameraSensor, "DisableCeilingCamera");
                return m_pcCeilingCameraSensor->Disable();
            }
            inline virtual void EnableOmnidirectionalCamera() {
                CHECK_IS_SENSOR_USED_HELPER(OMNIDIRECTIONAL_CAMERA_SENSOR_XML_NAME, m_bIsUsingOmnidirectionalCameraSensor, "EnableOmnidirectionalCamera");
                return m_pcOmnidirectionalCameraSensor->Enable();
            }
            inline virtual void DisableOmnidirectionalCamera() {
                CHECK_IS_SENSOR_USED_HELPER(OMNIDIRECTIONAL_CAMERA_SENSOR_XML_NAME, m_bIsUsingOmnidirectionalCameraSensor, "DisableOmnidirectionalCamera");
                return m_pcOmnidirectionalCameraSensor->Disable();
            }
         */

        virtual inline const CCI_CameraSensor::SCameraReadings& GetCeilingCameraReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(CEILING_CAMERA_SENSOR_XML_NAME, m_bIsUsingCeilingCameraSensor, "GetCeilingCameraBlobs");
            return m_pcCeilingCameraSensor->GetCameraReadings();
        }

        virtual inline const CCI_CameraSensor::SCameraReadings& GetOmnidirectionalCameraReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(OMNIDIRECTIONAL_CAMERA_SENSOR_XML_NAME, m_bIsUsingOmnidirectionalCameraSensor, "GetOmnidirectionalCameraBlobs");
            return m_pcOmnidirectionalCameraSensor->GetCameraReadings();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //   ACTUATORS SETTERS METHODS
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Sets the beacon color
         * notice that the actual color will be set in the ApplyState() method
         *
         * @param c_color color to be set
         * @see CColor
         *
         **/
        inline virtual void SetBeaconColor(const CColor& c_color)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "SetBeaconColor");
            m_bRefreshBeacon = true;
            m_cActuatedBeaconColor = c_color;
        }

        /**
         *
         * @brief Sets the beacon intensity
         * notice that the actual intensity will be set in the ApplyState() method
         *
         * @param un_intensity intensity to be set
         * @see CColor
         *
         **/
        inline virtual void SetBeaconIntensity(UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "SetBeaconIntensity");
            m_bRefreshBeacon = true;
            m_cActuatedBeaconColor.SetAlpha(un_intensity);
        }

        /**
         *
         * @brief Sets the color for the specified LED
         * notice that the actual color will be set in the ApplyState() method
         *
         * @param un_index index of the LED to be set
         * @param c_color color to be set
         * @see CColor
         *
         **/
        inline virtual void SetSingleLedColor(UInt8 un_index, const CColor& c_color)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetSingleLedColor");
            m_bRefreshLeds = true;
            m_tActuatedLedColors[un_index] = CColor(c_color.GetRed(), c_color.GetGreen(), c_color.GetBlue(), c_color.GetAlpha());
        }

        /**
         *
         * @brief Sets the color for all the LEDs
         * notice that the actual color will be set in the ApplyState() method
         *
         * @param c_color color to be set
         * @see CColor
         *
         **/
        inline virtual void SetAllLedsColor(const CColor& c_color)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetAllLedsColor");
            m_bRefreshLeds = true;
            for (UInt8 i = 0; i < NUM_LEDS; i++) {
                m_tActuatedLedColors[i] = CColor(c_color.GetRed(), c_color.GetGreen(), c_color.GetBlue(), c_color.GetAlpha());
            }
        }

        /**
         *
         * @brief Sets the intensity for the specified LED
         * notice that the actual intensity will be set in the ApplyState() method
         *
         * @param un_index index of the LED to be set
         * @param un_intensity intensity of the color (0-255)
         * @see CColor
         * @see CCI_FootBotLedsActuator
         *
         **/
        inline virtual void SetSingleLedIntensity(UInt8 un_index, UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetSingleLedIntensity");
            m_bRefreshLeds = true;
            m_tActuatedLedColors[un_index].SetAlpha(un_intensity);
        }

        /**
         *
         * @brief Sets the intensity for all the LEDs
         * notice that the actual intensity will be set in the ApplyState() method
         *
         * @param un_intensity intensity of the color (0-255)
         * @see CColor
         * @see CCI_FootBotLedsActuator
         *
         **/
        inline virtual void SetAllLedsIntensity(UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetAllLedsIntensity");
            m_bRefreshLeds = true;
            for (UInt32 i=0; i < NUM_LEDS; i++) {
                m_tActuatedLedColors[i].SetAlpha(un_intensity);
            }
        }

        /**
         *
         * @brief Sets the wheels speeds
         * speeds are linear and expressed in cm/s
         * notice that the actual speeds will be set in the ApplyState() method
         *
         * @param f_left_velocity linear speed for the left wheel
         * @param f_right_velocity linear speed for the right wheel
         * @see CCI_FootBotWheelSpeedSensor
         * @see CCI_FootBotWheelsActuator
         *
         **/
        inline virtual void SetWheelsLinearVelocity(Real f_left_velocity, Real f_right_velocity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(WHEELS_ACTUATOR_XML_NAME, m_bIsUsingWheelsActuator, "SetWheelsLinearVelocity");
            m_bRefreshWheelsActuator = true;
            m_fActuatedLeftWheelSpeed  = f_left_velocity;
            m_fActuatedRightWheelSpeed = f_right_velocity;
        }

        /**
         *
         * @brief Sets the gripper aperture
         * aperture is expressed in radians
         * notice that the actual gripper aperture will be set in the ApplyState() method
         *
         * @param c_aperture gripper aperture
         *
         *
         **/
        inline virtual void SetGripperAperture(const CRadians& c_aperture)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(GRIPPER_ACTUATOR_XML_NAME, m_bIsUsingGripperActuator, "SetGripperAperture");
            m_bRefreshGripperActuator = true;
            m_cActuatedGripperAperture = c_aperture;
        }

        /**
         *
         * @brief Sets the gripper to unlocked
         * notice that the actual gripper aperture will be set in the ApplyState() method
         *
         * @see CCI_FootBotGripperActuator
         *
         **/
        inline virtual void SetGripperUnlocked()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(GRIPPER_ACTUATOR_XML_NAME, m_bIsUsingGripperActuator, "SetGripperUnlocked");
            m_bRefreshGripperActuator = true;
            m_cActuatedGripperAperture = CCI_FootBotGripperActuator::UNLOCKED;
        }

        /**
         *
         * @brief Sets the gripper to locked positive
         * notice that the actual gripper aperture will be set in the ApplyState() method
         *
         * @see CCI_FootBotGripperActuator
         *
         **/
        inline virtual void SetGripperLockedPositive()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(GRIPPER_ACTUATOR_XML_NAME, m_bIsUsingGripperActuator, "SetGripperLockedPositive");
            m_bRefreshGripperActuator = true;
            m_cActuatedGripperAperture = CCI_FootBotGripperActuator::LOCKED_POSITIVE;
        }

        /**
         *
         * @brief Sets the gripper to locked negative
         * notice that the actual gripper aperture will be set in the ApplyState() method
         *
         * @see CCI_FootBotGripperActuator
         *
         **/
        inline virtual void SetGripperLockedNegative()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(GRIPPER_ACTUATOR_XML_NAME, m_bIsUsingGripperActuator, "SetGripperLockedNegative");
            m_bRefreshGripperActuator = true;
            m_cActuatedGripperAperture = CCI_FootBotGripperActuator::LOCKED_NEGATIVE;
        }

        /**
         *
         * @brief Enables the distance scanner
         *
         *
         **/
        inline virtual void SetDistanceScannerEnabled(bool b_scanner_on)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(DISTANCE_SCANNER_ACTUATOR_XML_NAME, m_bIsUsingDistanceScannerActuator, "SetDistanceScannerEnabled");
            m_bRefreshDistanceScannerEnabled = true;
            m_bActuatedDistanceScannerEnabled = b_scanner_on;
        }

        /**
         *
         * @brief Sets the angle of the distance scanner
         *
         * @param c_angle angle to be set
         * @see CRadians
         *
         **/
        inline virtual void SetDistanceScannerAngle(const CRadians& c_angle)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(DISTANCE_SCANNER_ACTUATOR_XML_NAME, m_bIsUsingDistanceScannerActuator, "SetDistanceScannerAngle");
            m_bRefreshDistanceScannerActuatorAngle = true;
            m_fActuatedDistanceScannerAngle = c_angle;
        }

        /**
         *
         * @brief Sets the RPM of the distance scanner for continuous rotation
         *
         * @param f_rpm speed to be set (rad/s)
         * @see Real
         *
         **/
        inline virtual void SetDistanceScannerRPM(Real f_rpm)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(DISTANCE_SCANNER_ACTUATOR_XML_NAME, m_bIsUsingDistanceScannerActuator, "SetDistanceScannerRPM");
            m_bRefreshDistanceScannerActuatorRPM = true;
            m_fActuatedDistanceScannerRPM = f_rpm;
        }

        /**
         *
         * @brief Starts short calibration of the proximity sensor
         *
         */
        inline virtual void SetProximityCalibrate()
        {
            CHECK_IS_SENSOR_USED_HELPER(PROXIMITY_SENSORS_XML_NAME, m_bIsUsingProximitySensor, "SetProximityCalibrate");
            m_bRefreshProximityCalibration = true;
        }

        /**
         *
         * @brief Triggers calibration of the base ground sensors
         *
         */
        inline virtual void RefreshBaseGroungSensorsCalibrationData()
        {
            CHECK_IS_SENSOR_USED_HELPER(BASE_GROUND_SENSOR_XML_NAME, m_bIsUsingBaseGroundSensor, "RefreshBaseGroungSensorsCalibrationData");
            m_bRefreshBaseGroundSensorCalibration = true;
        }

        /**
         *
         * @brief Sets the turret mode to active position control
         * notice that the method calls the actuator's method directly, thus the turret is set to position control mode when the method is called
         * if the turret sensor is used (declared in XML), the rotation of the gripper is also set to the reading of the sensor
         * this means the turret becomes active, but it does not move from the current rotation.
         * If the sensor is not used (not declared in XML), the last actuated turret rotation will be set (it could make the turret move from the current position)
         *
         * @see CCI_FootBotTurretActuator
         * @see SetTurretActiveModeAndRotation
         * @see SetTurretPassiveMode
         *
         **/
        inline virtual void SetTurretPositionControlMode()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "SetTurretPositionControlMode");
            m_eActuatedTurretMode = CCI_FootBotTurretActuator::MODE_POSITION_CONTROL;
            if (m_bIsUsingTurretTorqueSensor || m_bIsUsingTurretEncoderSensor) {
                m_cActuatedTurretRotation = GetTurretRotation();
            }
            m_pcTurretActuator->SetActiveWithRotation(m_cActuatedTurretRotation);
        }

        /**
         *
         * @brief Sets the turret to active position control and specifies the desired rotation
         * notice that the actual turret rotation will be set in the ApplyState() method
         *
         * @param c_rotation target turret rotation
         * @see CCI_FootBotTurretActuator
         *
         **/
        inline virtual void SetTurretPositionControlModeAndRotation(const CRadians& c_rotation)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "SetTurretPositionControlModeAndRotation");
            m_eActuatedTurretMode = CCI_FootBotTurretActuator::MODE_POSITION_CONTROL;
            m_pcTurretActuator->SetMode(m_eActuatedTurretMode);
            SetTurretRotation(c_rotation);
        }

        /**
         *
         * @brief Sets the turret mode to active speed control
         * notice that the method calls the actuator's method directly, thus the turret is set to speed control mode when the method is called
         * The target rotation speed is set to zero when the method is called
         *
         * @see CCI_FootBotTurretActuator
         * @see SetTurretPassiveMode
         *
         **/
        inline virtual void SetTurretSpeedControlMode()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "SetTurretSpeedControlMode");
            m_eActuatedTurretMode = CCI_FootBotTurretActuator::MODE_SPEED_CONTROL;
            m_nActuatedTurretRotationSpeed = 0;
            m_pcTurretActuator->SetMode(m_eActuatedTurretMode);
        }

        /**
         *
         * @brief Sets the turret mode to passive
         * notice that the method calls the actuator's method directly, thus the turret is set to passive when the method is called
         *
         * @see CCI_FootBotTurretActuator
         * @see SetTurretActiveMode
         *
         **/
        inline virtual void SetTurretPassiveMode()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "SetTurretPassiveMode");
            m_eActuatedTurretMode = CCI_FootBotTurretActuator::MODE_PASSIVE;
            m_pcTurretActuator->SetMode(m_eActuatedTurretMode);
        }

        /**
         *
         * @brief Specifies the desired turret rotation
         * notice that the actual turret rotation will be set in the ApplyState() method
         * if the turret is in passive mode the method will change the target position, but the turret will not move
         *
         * @param c_angle target turret rotation
         * @see CCI_FootBotTurretActuator
         * @see SetTurretPositionControlMode
         * @see SetTurretPassiveMode
         *
         **/
        inline virtual void SetTurretRotation(const CRadians& c_angle)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "SetTurretRotation");
            m_bRefreshTurretActuator = true;
            m_cActuatedTurretRotation = c_angle;
        }

        /**
         *
         * @brief Specifies the desired turret rotation speed
         * notice that the actual turret rotation will be set in the ApplyState() method
         * if the turret is in passive mode the method will change the target rotation speed, but the turret will not move
         *
         * @param c_speed_rad_sec target turret rotation speed in motor pulses
         * @see CCI_FootBotTurretActuator
         * @see SetTurretSpeedControlMode
         * @see SetTurretPassiveMode
         *
         **/
        inline virtual void SetTurretRotationSpeed(SInt32 n_speed_pulses)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "SetTurretRotationSpeed");
            m_bRefreshTurretActuator = true;
            m_nActuatedTurretRotationSpeed = n_speed_pulses;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////
        //   ACTUATORS GETTERS METHOD
        //   WARNING: many of these methods return the actuated commands that are going to be send.
        //            Therefore the values are not measures of the real state of the robot.
        ///////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Returns the current target beacon color
         * notice that the actual beacon color could be different
         *
         * @return target beacon color
         * @see CColor
         *
         **/
        inline virtual CColor GetActuatedBeaconColor()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "GetActuatedBeaconColor");
            return m_cActuatedBeaconColor;
        }

        /**
         *
         * @brief Returns the current target color for the specified LED
         * notice that the actual color could be different
         *
         * @param un_index index of the target LED
         * @return target led color
         * @see CColor
         * @see CCI_FootBotLedsActuator
         *
         **/
        inline virtual CColor GetActuatedSingleLedColor(UInt8 un_index)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "GetSingleActuatedLedColor");
            return m_tActuatedLedColors[un_index];
        }

        /**
         *
         * @brief Returns the current target color for all the LEDs
         * notice that the actual colors could be different
         *
         * @return target led color
         * @see CColor
         * @see CCI_FootBotLedsActuator
         *
         **/
        inline virtual CCI_FootBotLedsActuator::TLedSettings& GetActuatedAllLedColors()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "GetAllActuatedLedColors");
            return m_tActuatedLedColors;
        }

        /**
         *
         * @brief Returns the whether the distance scanner is currently set to be enabled
         * notice that the actual enabling might be different
         *
         * @return bool: whether or not the distance scanner is set to enabled
         *
         **/
        inline virtual bool GetActuatedDistanceScannerEnabled()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(DISTANCE_SCANNER_ACTUATOR_XML_NAME, m_bIsUsingDistanceScannerActuator, "GetActuatedDistanceScannerEnabled");
            return m_bActuatedDistanceScannerEnabled;
        }

        /**
         *
         * @brief Returns the current RPM of the distance scanner for continuous rotation
         * notice that the actual RPM of the distance scanner could be different
         *
         * @return f_rpm speed to be set (rad/s)
         * @see Real
         *
         **/
        inline virtual Real GetActuatedDistanceScannerRPM()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(DISTANCE_SCANNER_ACTUATOR_XML_NAME, m_bIsUsingDistanceScannerActuator, "GetActuatedDistanceScannerRPM");
            return m_fActuatedDistanceScannerRPM;
        }

        /**
         *
         * @brief Returns the current target left wheel speed
         * notice that the actual speed could be different
         * speed is expressed in cm/s
         *
         * @return target left wheel speed
         * @see CCI_FootBotWheelSpeedSensor
         * @see CCI_FootBotWheelsActuator
         *
         **/
        inline virtual Real GetActuatedLeftWheelVelocity()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(WHEELS_ACTUATOR_XML_NAME, m_bIsUsingWheelsActuator, "GetActuatedLeftWheelVelocity");
            return m_fActuatedLeftWheelSpeed;
        }

        /**
         *
         * @brief Returns the current target right wheel speed
         * notice that the actual speed could be different
         * speed is expressed in cm/s
         *
         * @return target right wheel speed
         * @see CCI_FootBotWheelSpeedSensor
         * @see CCI_FootBotWheelsActuator
         *
         **/
        inline virtual Real GetActuatedRightWheelVelocity()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(WHEELS_ACTUATOR_XML_NAME, m_bIsUsingWheelsActuator, "GetActuatedRightWheelVelocity");
            return m_fActuatedRightWheelSpeed;
        }

        /**
         *
         * @brief Returns the current target gripper aperture
         * notice that the actual aperture could be different
         * aperture is expressed in radians.
         *
         * @return target gripper aperture
         * @see CCI_FootBotGripperSensor
         * @see CCI_FootBotGripperActuator
         *
         **/
        inline virtual const CRadians& GetActuatedGripperAperture()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(GRIPPER_ACTUATOR_XML_NAME, m_bIsUsingGripperActuator, "GetActuatedGripperAperture");
            return m_cActuatedGripperAperture;
        }

        /**
         *
         * @brief Returns the current target turret mode
         * notice that the actual mode could be different
         *
         * @return target turret mode
         * @see CCI_FootBotTurretSensor
         * @see CCI_FootBotTurretActuator
         *
         **/
        inline virtual UInt8 GetActuatedTurretMode()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "GetActuatedTurretMode");
            return m_eActuatedTurretMode;
        }

        /**
         *
         * @brief Returns the current target turret rotation
         * notice that the actual mode could be different
         * rotation is expressed in radians
         *
         * @return target turret rotation in radians
         * @see CCI_FootBotTurretSensor
         * @see CCI_FootBotTurretActuator
         *
         **/
        inline virtual const CRadians& GetActuatedTurretRotation()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "GetActuatedTurretRotation");
            return m_cActuatedTurretRotation;
        }

        /**
         *
         * @brief Returns the current target turret rotation speed
         * notice that the actual mode could be different
         * rotation speed is expressed in motor pulses
         *
         * @return target turret rotation speed in motor pulses
         * @see CCI_FootBotTurretSensor
         * @see CCI_FootBotTurretActuator
         *
         **/
        inline virtual SInt32 GetActuatedTurretRotationSpeed()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "GetActuatedTurretRotationSpeed");
            return m_nActuatedTurretRotationSpeed;
        }

        /**
         *
         * @brief Returns the current status of the routine that checks if an object is gripped
         *
         * Possible status of the routine are "in progress", when the check is being performed,
         * "object gripped" when an object is currently gripped, and "object not gripped" when
         * no object is gripped.
         * When the routine is in progress the turret does not accept commands,
         * as turret control is needed for the check.
         *
         * @return check gripped object routine status
         *
         * @see CCI_FootBotGripperSensor
         *
         *
         **/
       inline virtual CCI_FootBotGripperSensor::EGripPhase GetGripPhase()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_SENSOR_XML_NAME, m_bIsUsingGripperSensor, "GetGripPhase");
            return m_pcGripperSensor->GetGripPhase();
        }

        /**
         *
         * @brief Returns true if the turret can be actively controlled
         * and the object gripping routine is not running
         *
         * @return true if the turret can be actively controlled
         * @see CCI_FootBotTurretActuator
         *
         **/
        inline virtual bool IsTurretAvailableForCommands()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(TURRET_ACTUATOR_XML_NAME, m_bIsUsingTurretActuator, "IsTurretAvailableForCommands");
            return m_pcTurretActuator->IsTurretAvailableForCommands();
        }

        /** Number of LEDs */
        static const UInt8 NUM_LEDS;


    protected:

        /////////////
        //    SENSORS
        /////////////

        /** References to the sensors */
        CCI_FootBotBaseGroundSensor*            m_pcBaseGroundSensor;
        CCI_FootBotProximitySensor*             m_pcProximitySensor;
        CCI_FootBotDistanceScannerSensor*       m_pcDistanceScannerSensor;
        CCI_FootBotEncoderSensor*               m_pcEncoderSensor;
        CCI_FootBotLightSensor*                 m_pcLightSensor;
        CCI_FootBotMotorGroundSensor*           m_pcMotorGroundSensor;
        CCI_FootBotWheelSpeedSensor*            m_pcWheelSpeedSensor;
        CCI_FootBotTurretTorqueSensor*          m_pcTurretTorqueSensor;
        CCI_FootBotTurretEncoderSensor*         m_pcTurretEncoderSensor;
        CCI_FootBotGripperSensor*               m_pcGripperSensor;
        CCI_FootBotCeilingCameraSensor*         m_pcCeilingCameraSensor;
        CCI_FootBotOmnidirectionalCameraSensor* m_pcOmnidirectionalCameraSensor;

        /** Sensors booleans */
        bool m_bIsUsingBaseGroundSensor;
        bool m_bIsUsingProximitySensor;
        bool m_bIsUsingDistanceScannerSensor;
        bool m_bIsUsingEncoderSensor;
        bool m_bIsUsingLightSensor;
        bool m_bIsUsingMotorGroundSensor;
        bool m_bIsUsingWheelSpeedSensor;
        bool m_bIsUsingTurretTorqueSensor;
        bool m_bIsUsingTurretEncoderSensor;
        bool m_bIsUsingGripperSensor;
        bool m_bIsUsingCeilingCameraSensor;
        bool m_bIsUsingOmnidirectionalCameraSensor;

        /** Variables related to sensors */
        bool m_bResetEncoderSensor;
        const CCI_FootBotLightSensor::TReadings*    m_tLightSensorReadings;

        /* XML sensor names */
        static const std::string BASE_GROUND_SENSOR_XML_NAME;
        static const std::string PROXIMITY_SENSORS_XML_NAME;
        static const std::string DISTANCE_SCANNER_SENSOR_XML_NAME;
        static const std::string ENCODER_SENSOR_XML_NAME;
        static const std::string LIGHT_SENSOR_XML_NAME;
        static const std::string MOTOR_GROUND_SENSOR_XML_NAME;
        static const std::string WHEEL_SPEED_SENSOR_XML_NAME;
        static const std::string TURRET_TORQUE_SENSOR_XML_NAME;
        static const std::string TURRET_ENCODER_SENSOR_XML_NAME;
        static const std::string GRIPPER_SENSOR_XML_NAME;
        static const std::string CEILING_CAMERA_SENSOR_XML_NAME;
        static const std::string OMNIDIRECTIONAL_CAMERA_SENSOR_XML_NAME;

        ///////////////
        //    ACTUATORS
        ///////////////

        /** References to the actuators */
        CCI_FootBotBeaconActuator*          m_pcBeaconActuator;
        CCI_FootBotWheelsActuator*          m_pcWheelsActuator;
        CCI_FootBotGripperActuator*         m_pcGripperActuator;
        CCI_FootBotLedsActuator*            m_pcLedsActuator;
        CCI_FootBotTurretActuator*          m_pcTurretActuator;
        CCI_FootBotDistanceScannerActuator* m_pcDistanceScannerActuator;

        /** Actuators booleans */
        bool m_bIsUsingBeacon;
        bool m_bIsUsingWheelsActuator;
        bool m_bIsUsingGripperActuator;
        bool m_bIsUsingLeds;
        bool m_bIsUsingTurretActuator;
        bool m_bIsUsingDistanceScannerActuator;

        /** Actuator refresh booleans */
        bool m_bRefreshBeacon;
        bool m_bRefreshWheelsActuator;
        bool m_bRefreshGripperActuator;
        bool m_bRefreshLeds;
        bool m_bRefreshTurretActuator;
        bool m_bRefreshDistanceScannerEnabled;
        bool m_bRefreshDistanceScannerActuatorAngle;
        bool m_bRefreshDistanceScannerActuatorRPM;
        bool m_bRefreshProximityCalibration;
        bool m_bRefreshBaseGroundSensorCalibration;

        /** Actuators commands variables */
        CColor                                  m_cActuatedBeaconColor;
        Real                                    m_fActuatedLeftWheelSpeed;
        Real                                    m_fActuatedRightWheelSpeed;
        CRadians                                m_cActuatedGripperAperture;
        CCI_FootBotLedsActuator::TLedSettings   m_tActuatedLedColors;
        CCI_FootBotTurretActuator::ETurretModes m_eActuatedTurretMode;
        CRadians                                m_cActuatedTurretRotation;
        SInt32                                  m_nActuatedTurretRotationSpeed;
        bool                                    m_bActuatedDistanceScannerEnabled;
        CRadians                                m_fActuatedDistanceScannerAngle;
        Real                                    m_fActuatedDistanceScannerRPM;

        /* XML actuator names */
        static const std::string BEACON_ACTUATOR_XML_NAME;
        static const std::string WHEELS_ACTUATOR_XML_NAME;
        static const std::string GRIPPER_ACTUATOR_XML_NAME;
        static const std::string LEDS_ACTUATOR_XML_NAME;
        static const std::string TURRET_ACTUATOR_XML_NAME;
        static const std::string DISTANCE_SCANNER_ACTUATOR_XML_NAME;

    };

}

#endif

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
 * @file <common/control_interface/behavioral_toolkit/swarmanoid/handbot/ci_handbot_state.h>
 *
 * @brief This file provides the control interface behavioral toolkit definition for a hand-bot state.
 * Check file ci_robot_state.h for the full explanation.
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#ifndef CI_HANDBOT_STATE_H
#define CI_HANDBOT_STATE_H

namespace argos {
    class CCI_HandBotState;
}

#include <argos2/common/control_interface/behavioral_toolkit/swarmanoid/ci_swarmanoid_robot_state.h>
#include <argos2/common/utility/math/angles.h>

/** Sensors includes */
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_arm_encoders_sensor.h>
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_proximity_sensor.h>
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_gripper_cameras.h>
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_head_camera_sensor.h>

/** Actuators includes */
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_beacon_leds_actuator.h>
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_leds_actuator.h>
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_arms_actuator.h>
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_retrieve_book_actuator.h>

namespace argos {

    class CCI_HandBotState: public CCI_SwarmanoidRobotState {

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

        CCI_HandBotState(CCI_Robot& pc_robot) :
            CCI_SwarmanoidRobotState(pc_robot),

            /** Initialize all the sensors */
            m_pcArmEncodersSensor      (NULL),
            m_pcProximitySensor        (NULL),
            m_pcGripperCameras         (NULL),
            m_pcHeadCamera             (NULL),

            /** Initialize all sensors booleans */
            m_bIsUsingArmEncodersSensor (false),
            m_bIsUsingProximitySensor   (false),
            m_bIsUsingGripperCameras    (false),
            m_bIsUsingHeadCamera        (false),

            /** Initialize other sensors related variables */
            m_unLeftGripperCameraLineToFetch  (7),
            m_unRightGripperCameraLineToFetch (7),

            /** Initialize all the actuators */
            m_pcBeaconActuator       (NULL),
            m_pcLedsActuator         (NULL),
            m_pcArmsActuator         (NULL),
            m_pcRetrieveBookActuator (NULL),

            /** Initialize all actuators booleans */
            m_bIsUsingBeacon               (false),
            m_bIsUsingLeds                 (false),
            m_bIsUsingArms                 (false),
            m_bIsUsingRetrieveBookActuator (false),

            /** Initialize all actuators refresh booleans */
            m_bRefreshBeacon (false),
            m_bRefreshLeds   (false),
            m_bRefreshArms   (false),

            /** Initialize the actuated values */
            m_cActuatedHeadRotation         (0.0),
            m_cActuatedLeftArmAperture      (CCI_HandBotArmsActuator::ARM_RETRACTED),
            m_cActuatedRightArmAperture     (CCI_HandBotArmsActuator::ARM_RETRACTED),
            m_cActuatedLeftGripperRotation  (CCI_HandBotArmsActuator::WRIST_PERPENDICULAR),
            m_cActuatedRightGripperRotation (CCI_HandBotArmsActuator::WRIST_PERPENDICULAR),
            m_cActuatedLeftGripperAperture  (CCI_HandBotArmsActuator::GRIPPER_OPEN),
            m_cActuatedRightGripperAperture (CCI_HandBotArmsActuator::GRIPPER_OPEN)

        {

            m_tActuatedLedColors   = CCI_HandBotLedsActuator::TLedSettings(NUM_LEDS);
            m_tActuatedBeaconLedColors = CCI_HandBotBeaconLedsActuator::TLedSettings(NUM_BEACON_LEDS);

            for (UInt8 i = 0; i < NUM_LEDS; i++)
                m_tActuatedLedColors[i] = CColor::BLACK;

            for (UInt8 i = 0; i < NUM_BEACON_LEDS; i++)
                m_tActuatedBeaconLedColors[i] = CColor::BLACK;

        }


        /**
         *
         * Copy Constructor.
         *
         */
        CCI_HandBotState(const CCI_HandBotState& c_handbot_state) : CCI_SwarmanoidRobotState(c_handbot_state)
        {
            *this = c_handbot_state;
        }

        /**
         *
         * = operator overriding. Used with the same semantic of the copy constructor
         *
         */
        CCI_HandBotState& operator=(const CCI_HandBotState& c_handbot_state) {

            if (this != &c_handbot_state) {

                CCI_SwarmanoidRobotState::operator=(c_handbot_state);

                /** Copy the references to the sensor */
                m_pcProximitySensor = c_handbot_state.m_pcProximitySensor;
                m_pcGripperCameras  = c_handbot_state.m_pcGripperCameras;
                m_pcHeadCamera      = c_handbot_state.m_pcHeadCamera;

                /** Copy the sensors booleans */
                m_bIsUsingProximitySensor = c_handbot_state.m_bIsUsingProximitySensor;
                m_bIsUsingGripperCameras  = c_handbot_state.m_bIsUsingGripperCameras;
                m_bIsUsingHeadCamera      = c_handbot_state.m_bIsUsingHeadCamera;

                /** Copy the references to the actuators */
                m_pcBeaconActuator       = c_handbot_state.m_pcBeaconActuator;
                m_pcLedsActuator         = c_handbot_state.m_pcLedsActuator;
                m_pcArmsActuator         = c_handbot_state.m_pcArmsActuator;
                m_pcRetrieveBookActuator = c_handbot_state.m_pcRetrieveBookActuator;

                /** Copy the actuators booleans */
                m_bIsUsingBeacon = c_handbot_state.m_bIsUsingBeacon;
                m_bIsUsingLeds   = c_handbot_state.m_bIsUsingLeds;
                m_bIsUsingArms   = c_handbot_state.m_bIsUsingArms;

                /** Copy the actuators refresh booleans */
                m_bRefreshBeacon = c_handbot_state.m_bRefreshBeacon;
                m_bRefreshLeds   = c_handbot_state.m_bRefreshLeds;
                m_bRefreshArms   = c_handbot_state.m_bRefreshArms;

                /** Copy the actuated commands */
                m_tActuatedLedColors            = c_handbot_state.m_tActuatedLedColors;
                m_tActuatedBeaconLedColors      = c_handbot_state.m_tActuatedBeaconLedColors;
                m_cActuatedHeadRotation         = c_handbot_state.m_cActuatedHeadRotation;
                m_cActuatedLeftArmAperture      = c_handbot_state.m_cActuatedLeftArmAperture;
                m_cActuatedRightArmAperture     = c_handbot_state.m_cActuatedRightArmAperture;
                m_cActuatedLeftGripperRotation  = c_handbot_state.m_cActuatedLeftGripperRotation;
                m_cActuatedRightGripperRotation = c_handbot_state.m_cActuatedRightGripperRotation;
                m_cActuatedLeftGripperAperture  = c_handbot_state.m_cActuatedLeftGripperAperture;
                m_cActuatedRightGripperAperture = c_handbot_state.m_cActuatedRightGripperAperture;

            }

            return *this;
        }


        /**
         *
         * Destructor.
         *
         **/
        virtual ~CCI_HandBotState() {
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
        virtual void ReadState(){}

        /**
         *
         * @brief Applies the actuator commands with the robot state ones.
         *
         **/
        virtual void ApplyState();

        /** Number of sensor readings (for those sensors returning arrays of values) */
        static const UInt32 NUM_PROXIMITY_SENSOR_READINGS_PER_HAND;

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //   SENSORS GETTER METHODS, SENSOR READINGS
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Returns the arm encoders readings
         * The encoder readings include the rotation of the head, the aperture of the 2 arms, the aperture and rotation of the 2 grippers
         *
         * @return arms encoders readings
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CCI_HandBotArmEncodersSensor::TReading GetAllArmEncodersReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetAllArmEncodersReadings");
            return m_pcArmEncodersSensor->GetAllReadings();
        }

        /**
         *
         * @brief Returns the rotation of the head
         * The rotation is expressed in radians. Positive rotations are clockwise,
         * from the robot's perspective (looking the same direction at the camera does).
         * The zero position is with the arms parallel to the ground.
         * TODO: add limits
         *
         * @return head rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CRadians GetHeadRotation()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetHeadRotation");
            return m_pcArmEncodersSensor->GetHeadRotation();
        }

        /**
         *
         * @brief Returns the aperture of the left arm
         * The aperture is expressed in radians. Positive values stretch the arms.
         * The zero position is when the two arms lay on the same line
         * TODO: add limits
         *
         * @return left arm aperture in radians
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CRadians GetLeftArmAperture()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetLeftArmAperture");
            return m_pcArmEncodersSensor->GetLeftArmAperture();
        }

        /**
         *
         * @brief Returns the aperture of the right arm
         * The aperture is expressed in radians. Positive values stretch the arms.
         * The zero position is when the two arms lay on the same line
         * TODO: add limits
         *
         * @return right arm aperture in radians
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CRadians GetRightArmAperture()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetRightArmAperture");
            return m_pcArmEncodersSensor->GetRightArmAperture();
        }

        /**
         *
         * @brief Returns the rotation of the left gripper
         * The rotation is expressed in radians. Positive rotations are clockwise,
         * from the robot's perspective (looking the same direction at the camera does).
         * The zero position is with the gripper claws parallel to the ground.
         * TODO: add limits
         *
         * @return left gripper rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CRadians GetLeftGripperRotation()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetLeftGripperRotation");
            return m_pcArmEncodersSensor->GetLeftGripperRotation();
        }

        /**
         *
         * @brief Returns the rotation of the right gripper
         * The rotation is expressed in radians. Positive rotations are clockwise,
         * from the robot's perspective (looking the same direction at the camera does).
         * The zero position is with the gripper claws parallel to the ground.
         * TODO: add limits
         *
         * @return right gripper rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CRadians GetRightGripperRotation()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetRightGripperRotation");
            return m_pcArmEncodersSensor->GetRightGripperRotation();
        }

        /**
         *
         * @brief Returns the aperture of the left gripper
         * The aperture is expressed in radians.
         * TODO: check limits, values
         *
         * @return left gripper aperture in radians
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CRadians GetLeftGripperAperture()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetLeftGripperAperture");
            return m_pcArmEncodersSensor->GetLeftGripperAperture();
        }

        /**
         *
         * @brief Returns the aperture of the right gripper
         * The aperture is expressed in radians.
         * TODO: check limits, values
         *
         * @return right gripper aperture in radians
         * @see CCI_HandBotArmEncodersSensor
         *
         **/
        virtual inline const CRadians GetRightGripperAperture()
        {
            CHECK_IS_SENSOR_USED_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, m_bIsUsingArmEncodersSensor, "GetRightGripperAperture");
            return m_pcArmEncodersSensor->GetRightGripperAperture();
        }

        /**
         *
         * @brief Returns the proximity sensors readings of both the grippers
         *
         * @return the proximity sensors readings
         * @see CCI_HandBotProximitySensor
         *
         **/
        virtual inline const CCI_HandBotProximitySensor::TReadings GetAllProximitySensorReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(PROXIMITY_SENSORS_XML_NAME, m_bIsUsingProximitySensor, "GetAllProximitySensorReadings");
            return m_pcProximitySensor->GetAllReadings();
        }

        /**
         *
         * @brief Returns the proximity sensors readings of the left gripper
         *
         * @return the proximity sensors readings for the left gripper
         * @see CCI_HandBotProximitySensor
         *
         **/
        virtual inline const CCI_HandBotProximitySensor::THandReadings GetLeftHandProximityReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(PROXIMITY_SENSORS_XML_NAME, m_bIsUsingProximitySensor, "GetLeftHandProximityReadings");
            return m_pcProximitySensor->GetReadingsLeft();
        }

        /**
         *
         * @brief Returns the proximity sensors readings of the right gripper
         *
         * @return the proximity sensors readings for the right gripper
         * @see CCI_HandBotProximitySensor
         *
         **/
        virtual inline const CCI_HandBotProximitySensor::THandReadings GetRightHandProximityReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(PROXIMITY_SENSORS_XML_NAME, m_bIsUsingProximitySensor, "GetRightHandProximityReadings");
            return m_pcProximitySensor->GetReadingsRight();
        }

        /**
         *
         * @brief Returns the camera readings of both the grippers
         *
         * @return the gripper camera readings
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline const CCI_HandBotGripperCameras::TReadings GetAllGripperCamerasReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "GetAllGripperCamerasReadings");
            return m_pcGripperCameras->GetAllReadings();
        }

        /**
         *
         * @brief Returns the left gripper camera readings
         *
         * @return the left gripper camera readings
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline const CCI_HandBotGripperCameras::THandReadings GetLeftGripperCameraReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "GetLeftGripperCameraReadings");
            return (m_pcGripperCameras->GetAllReadings()).Left;
        }

        /**
         *
         * @brief Returns the right gripper camera readings
         *
         * @return the right gripper camera readings
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline const CCI_HandBotGripperCameras::THandReadings GetRightGripperCameraReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "GetRightGripperCameraReadings");
            return (m_pcGripperCameras->GetAllReadings()).Right;
        }

        /**
         *
         * @brief Returns the vector of shelf edges detected by the camera
         * Edges are detected only if the edge detection filter has been activated first
         *
         * @return the list of the perceived shelf edges
         * @see CCI_HandBotHeadCameraSensor
         * @see IsShelEdgeDetectionActive
         * @see EnableShelfEdgeDetection
         * @see DisableShelfEdgeDetection
         *
         **/
        virtual inline CCI_HandBotHeadCameraSensor::TShelfEdgeList GetShelfEdgeList()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "GetShelfEdgeList");
            return m_pcHeadCamera -> GetShelfEdgeList();
        }

        /**
         *
         * @brief Returns the list of blobs detected by the camera
         * Blobs are detected only if the blob detection filter has been activated first
         *
         * @return the list of the perceived blobs
         * @see CCI_HandBotHeadCameraSensor
         * @see IsBlobDetectionActive
         * @see EnableBlobDetection
         * @see DisableBlobDetection
         *
         **/
        virtual inline const CCI_CameraSensor::SCameraReadings& GetHeadCameraReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "GetHeadCameraReadings");
            return m_pcHeadCamera->GetCameraReadings();
        }

        /**
         *
         * @brief Returns the size of the head image
         * Activated only if the camera has been activated first
         *
         * @return the size of the image
         *
         **/
        virtual inline CCI_HandBotHeadCameraSensor::TCameraSizeVector GetImageSize()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "GetImageSizeVector");
            return m_pcHeadCamera -> GetImageSize();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //   SENSORS GETTER METHODS, MISC VARIABLES
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Returns the image line that will be fetched by the left gripper camera
         *
         * @return the camera line that will be fetched by the camera in the left gripper
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline UInt32 GetLeftGripperCameraLineToFetch()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "GetLeftGripperCameraLineToFetch");
            return m_unLeftGripperCameraLineToFetch;
        }

        /**
         *
         * @brief Returns the image line that will be fetched by the right gripper camera
         *
         * @return the camera line that will be fetched by the camera in the right gripper
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline UInt32 GetRightGripperCameraLineToFetch()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "GetRightGripperCameraLineToFetch");
            return m_unRightGripperCameraLineToFetch;
        }

        /**
         *
         * @brief Returns true if data sending is enabled for gripper cameras
         *
         * @return true if data sending is enabled
         * @see CCI_HandBotGripperCameras
         * @see EnableGripperCamerasDataSending
         * @see DisableGripperCamerasDataSending
         *
         **/
        virtual inline bool IsGripperCamerasDataSendingEnabled()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "IsGripperCamerasDataSendingEnabled");
            return m_pcGripperCameras -> IsDataSendingEnabled();
        }

        /**
         *
         * @brief Returns true if shelf edge is active
         *
         * @return true if shelf edge is active
         * @see CCI_HandBotHeadCameraSensor
         * @see EnableShelfEdgeDetection
         * @see DisableShelfEdgeDetection
         *
         **/
        virtual inline bool IsShelfEdgeDetectionEnabled()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "IsShelfEdgeDetectionEnabled");
            return m_pcHeadCamera -> IsShelfEdgeDetectionEnabled();
        }


        /**
         *
         * @brief Returns true if blob detection is active
         *
         * @return true if blob detection is active
         * @see CCI_HandBotHeadCameraSensor
         * @see EnableBlobDetection
         * @see DisableBlobDetection
         *
         **/
        virtual inline bool IsBlobDetectionEnabled()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "IsBlobDetectionEnabled");
            return m_pcHeadCamera -> IsBlobDetectionEnabled();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //   SENSORS SETTER METHODS
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Selects the image line that will be fetched by the left gripper camera
         *
         * @param un_line the camera line that will be fetched by the camera in the left gripper
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline void SetLeftGripperCameraLineToFetch(UInt32 un_line)
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "SetLeftGripperCameraLineToFetch");
            m_unLeftGripperCameraLineToFetch = un_line;
            m_pcGripperCameras->SetLineToFetchLeft(m_unLeftGripperCameraLineToFetch);
        }

        /**
         *
         * @brief Selects the image line that will be fetched by the right gripper camera
         *
         * @param un_line the camera line that will be fetched by the camera in the right gripper
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline void SetRightGripperCameraLineToFetch(UInt32 un_line)
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "SetRightGripperCameraLineToFetch");
            m_unRightGripperCameraLineToFetch = un_line;
            m_pcGripperCameras->SetLineToFetchRight(m_unLeftGripperCameraLineToFetch);
        }

        /**
         *
         * @brief Sets the gripper cameras color mode to RGB
         *
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline void SetGripperCamerasRGBMode()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "SetGripperCamerasRGBMode");
            m_pcGripperCameras->SetRGBColorMode();
        }

        /**
         *
         * @brief Sets the gripper cameras color mode to HSV
         *
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline void SetGripperCamerasHSVMode()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "SetGripperCamerasHSVMode");
            m_pcGripperCameras->SetHSVColorMode();
        }

        /**
         *
         * @brief Enables gripper cameras data sending
         *
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline void EnableGripperCamerasDataSending()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "EnableGripperCamerasDataSending");
            m_pcGripperCameras->EnableDataSending();
        }

        /**
         *
         * @brief Disables gripper cameras data sending
         *
         * @see CCI_HandBotGripperCameras
         *
         **/
        virtual inline void DisableGripperCamerasDataSending()
        {
            CHECK_IS_SENSOR_USED_HELPER(GRIPPER_CAMERAS_XML_NAME, m_bIsUsingGripperCameras, "DisableGripperCamerasDataSending");
            m_pcGripperCameras->DisableDataSending();
        }

        /**
         *
         * @brief Enables shelf edge detection
         *
         * @see CCI_HandBotHeadCameraSensor
         *
         **/
        virtual inline void EnableShelfEdgeDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "EnableShelfEdgeDetection");
            m_pcHeadCamera -> EnableShelfEdgeDetection();
        }

        /**
         *
         * @brief Disables shelf edge detection
         *
         * @see CCI_HandBotHeadCameraSensor
         *
         **/
        virtual inline void DisableShelfEdgeDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "DisableShelfEdgeDetection");
            m_pcHeadCamera -> DisableShelfEdgeDetection();
        }

        /**
         *
         * @brief Enables blob detection
         *
         * @see CCI_HandBotHeadCameraSensor
         *
         **/
        virtual inline void EnableBlobDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "EnableBlobDetection");
            m_pcHeadCamera -> EnableBlobDetection();
        }

        /**
         *
         * @brief Disables blob detection
         *
         * @see CCI_HandBotHeadCameraSensor
         *
         **/
        virtual inline void DisableBlobDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "DisableBlobDetection");
            m_pcHeadCamera -> DisableBlobDetection();
        }

        /**
         *
         * @brief Enables the head camera
         *
         * @see CCI_HandBotHeadCameraSensor
         *
         **/
        virtual inline void EnableHeadCamera()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "EnableHeadCamera");
            m_pcHeadCamera -> Enable();
        }

        /**
         *
         * @brief Disables the head camera
         *
         * @see CCI_HandBotHeadCameraSensor
         *
         **/
        virtual inline void DisableHeadCamera()
        {
            CHECK_IS_SENSOR_USED_HELPER(HEAD_CAMERA_XML_NAME, m_bIsUsingHeadCamera, "DisableHeadCamera");
            m_pcHeadCamera -> Disable();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //   ACTUATORS SETTERS METHODS
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Sets the color for the specified beacon LED
         * notice that the actual color will be set in the ApplyState() method
         *
         * @param un_index index of the LED to be set
         * @param c_color color to be set
         * @see CColor
         * @see CCI_HandBotBeaconActuator
         *
         **/
        virtual inline void SetBeaconSingleLedColor(UInt8 un_index, CColor c_color)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "SetBeaconSingleLedColor");
            m_bRefreshBeacon = true;
            m_tActuatedBeaconLedColors[un_index] = CColor(c_color.GetRed(), c_color.GetGreen(), c_color.GetBlue(), c_color.GetAlpha() );
        }

        /**
         *
         * @brief Sets the color for all the beacon LEDs
         * notice that the actual color will be set in the ApplyState() method
         *
         * @param c_color color to be set
         * @see CColor
         * @see CCI_HandBotBeaconActuator
         *
         **/
        virtual inline void SetBeaconAllLedsColor(CColor c_color)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "SetBeaconAllLedsColor");
            m_bRefreshBeacon = true;
            for(UInt8 i = 0; i < NUM_BEACON_LEDS; i++) {
                m_tActuatedBeaconLedColors[i] = CColor(c_color.GetRed(), c_color.GetGreen(), c_color.GetBlue(), c_color.GetAlpha() );
            }
        }

        /**
         *
         * @brief Sets the intensity for the specified beacon LED
         * notice that the actual intensity will be set in the ApplyState() method
         *
         * @param un_index index of the LED to be set
         * @param un_intensity intensity of the color (0-255)
         * @see CColor
         * @see CCI_HandBotBeaconActuator
         *
         **/
        virtual inline void SetBeaconSingleLedIntensity(UInt8 un_index, UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "SetBeaconSingleLedIntensity");
            m_bRefreshBeacon = true;
            m_tActuatedBeaconLedColors[un_index].SetAlpha(un_intensity);
        }

        /**
         *
         * @brief Sets the intensity for all the beacon LEDs
         * notice that the actual intensity will be set in the ApplyState() method
         *
         * @param un_intensity intensity of the color (0-255)
         * @see CColor
         * @see CCI_HandBotBeaconActuator
         *
         **/
        virtual inline void SetBeaconAllLedsIntensity(UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "SetBeaconAllLedsIntensity");
            m_bRefreshBeacon = true;
            for (UInt32 i=0; i < NUM_BEACON_LEDS; i++) {
                m_tActuatedBeaconLedColors[i].SetAlpha(un_intensity);
            }
        }

        /**
         *
         * @brief Sets the color for the specified LED
         * notice that the actual color will be set in the ApplyState() method
         *
         * @param un_index index of the LED to be set
         * @param c_color color to be set
         * @see CColor
         * @see CCI_HandBotLedsActuator
         *
         **/
        virtual inline void SetSingleLedColor(UInt8 un_index, CColor c_color)
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
         * @see CCI_HandBotLedsActuator
         *
         **/
        virtual inline void SetAllLedsColor(CColor c_color)
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
         * @see CCI_HandBotLedsActuator
         *
         **/
        virtual inline void SetSingleLedIntensity(UInt8 un_index, UInt8 un_intensity)
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
         * @see CCI_HandBotLedsActuator
         *
         **/
        virtual inline void SetAllLedsIntensity(UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetAllLedsIntensity");
            m_bRefreshLeds = true;
            for (UInt32 i=0; i < NUM_LEDS; i++) {
                m_tActuatedLedColors[i].SetAlpha(un_intensity);
            }
        }

        /**
         *
         * @brief Sets the rotation of the head
         *
         * @param c_head_rotation head rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see GetHeadRotation
         *
         **/
        virtual inline void SetHeadRotation(CRadians c_head_rotation)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "SetHeadRotation");
            m_bRefreshArms = true;
            m_cActuatedHeadRotation = c_head_rotation;
        }

        /**
         *
         * @brief Sets the aperture of the left arm
         *
         * @param c_left_arm_aperture left arm aperture in radians
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see GetLeftArmAperture
         *
         **/
        virtual inline void SetLeftArmAperture(CRadians c_left_arm_aperture)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "SetLeftArmAperture");
            m_bRefreshArms = true;
            m_cActuatedLeftArmAperture = c_left_arm_aperture;
        }

        /**
         *
         * @brief Sets the aperture of the right arm
         *
         * @param c_right_arm_aperture right arm aperture in radians
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see GetRightArmAperture
         *
         **/
        virtual inline void SetRightArmAperture(CRadians c_right_arm_aperture)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "SetRightArmAperture");
            m_bRefreshArms = true;
            m_cActuatedRightArmAperture = c_right_arm_aperture;
        }

        /**
         *
         * @brief Sets the rotation of the left gripper
         *
         * @param c_left_gripper_rotation left gripper rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see GetLeftGripperRotation
         *
         **/
        virtual inline void SetLeftGripperRotation(CRadians c_left_gripper_rotation)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "SetLeftGripperRotation");
            m_bRefreshArms = true;
            m_cActuatedLeftGripperRotation = c_left_gripper_rotation;
        }

        /**
         *
         * @brief Sets the rotation of the right gripper
         *
         * @param c_right_gripper_rotation right gripper rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see GetRightGripperRotation
         *
         **/
        virtual inline void SetRightGripperRotation(CRadians c_right_gripper_rotation)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "SetRightGripperRotation");
            m_bRefreshArms = true;
            m_cActuatedRightGripperRotation = c_right_gripper_rotation;
        }

        /**
         *
         * @brief Sets the aperture of the left gripper
         *
         * @param c_left_gripper_rotation left gripper rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see GetLeftGripperAperture
         *
         **/
        virtual inline void SetLeftGripperAperture(CRadians c_left_gripper_aperture)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "SetLeftGripperAperture");
            m_bRefreshArms = true;
            m_cActuatedLeftGripperAperture = c_left_gripper_aperture;
        }

        /**
         *
         * @brief Sets the aperture of the right gripper
         *
         * @param c_right_gripper_rotation right gripper rotation in radians
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see GetRightGripperAperture
         *
         **/
        virtual inline void SetRightGripperAperture(CRadians c_right_gripper_aperture)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "SetRightGripperAperture");
            m_bRefreshArms = true;
            m_cActuatedRightGripperAperture = c_right_gripper_aperture;
        }

        /**
         *
         * @brief Triggers the retrieve book routine
         *
         * @param f_climb_height target height to climb to
         * @see CCI_HandBotRetrieveBookActuator
         *
         **/
        virtual inline void RetrieveBook(UInt8 un_target_shelf, UInt32 un_starting_gripper)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(RETRIEVE_BOOK_ACTUATOR_XML_NAME, m_bIsUsingRetrieveBookActuator, "RetrieveBook");
            m_pcRetrieveBookActuator -> RetrieveBook(un_target_shelf, un_starting_gripper);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        //   ACTUATORS GETTERS METHOD
        //   WARNING: these methods return the actuated commands that are going to be send.
        //            Therefore the values are not measures of the real state of the robot.
        ////////////////////////////////////////////////////////////////////////////////////


        /**
         *
         * @brief Returns the current target color for the specified LED
         * notice that the actual color could be different
         *
         * @param un_index index of the target LED
         * @return target led color
         * @see CColor
         * @see CCI_HandBotBeaconActuator
         *
         **/
        virtual inline CColor GetActuatedBeaconSingleLedColor(UInt8 un_index)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "GetSingleActuatedBeaconLedColor");
            return m_tActuatedBeaconLedColors[un_index];
        }

        /**
         *
         * @brief Returns the current target color for all the LEDs
         * notice that the actual colors could be different
         *
         * @return target led color
         * @see CColor
         * @see CCI_HandBotBeaconActuator
         *
         **/
        virtual inline CCI_HandBotBeaconLedsActuator::TLedSettings& GetActuatedBeaconAllLedColors()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(BEACON_ACTUATOR_XML_NAME, m_bIsUsingBeacon, "GetAllActuatedBeaconLedColors");
            return m_tActuatedBeaconLedColors;
        }

        /**
         *
         * @brief Returns the current target color for the specified LED
         * notice that the actual color could be different
         *
         * @param un_index index of the target LED
         * @return target led color
         * @see CColor
         * @see CCI_HandBotLedsActuator
         *
         **/
        virtual inline CColor GetActuatedSingleLedColor(UInt8 un_index)
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
         * @see CCI_HandBotLedsActuator
         *
         **/
        virtual inline CCI_HandBotLedsActuator::TLedSettings& GetActuatedAllLedColors()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "GetAllActuatedLedColors");
            return m_tActuatedLedColors;
        }

        /**
         *
         * @brief Returns the current target head rotation
         * notice that the actual head rotation could be different
         *
         * @return target head rotation
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see SetHeadRotation
         *
         **/
        virtual inline CRadians GetActuatedHeadRotation()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "GetActuatedHeadRotation");
            return m_cActuatedHeadRotation;
        }

        /**
         *
         * @brief Returns the current target left arm aperture
         * notice that the actual aperture could be different
         *
         * @return target left arm aperture
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see SetLeftArmAperture
         *
         **/
        virtual inline CRadians GetActuatedLeftArmAperture()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "GetActuatedLeftArmAperture");
            return m_cActuatedLeftArmAperture;
        }

        /**
         *
         * @brief Returns the current target right arm aperture
         * notice that the actual aperture could be different
         *
         * @return target right arm aperture
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see SetRightArmAperture
         *
         **/
        virtual inline CRadians GetActuatedRightArmAperture()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "GetActuatedRightArmAperture");
            return m_cActuatedRightArmAperture;
        }

        /**
         *
         * @brief Returns the current target left gripper rotation
         * notice that the actual rotation could be different
         *
         * @return target left gripper rotation
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see SetLeftGripperRotation
         *
         **/
        virtual inline CRadians GetActuatedLeftGripperRotation()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "GetActuatedLeftGripperRotation");
            return m_cActuatedLeftGripperRotation;
        }

        /**
         *
         * @brief Returns the current target right gripper rotation
         * notice that the actual rotation could be different
         *
         * @return target right gripper rotation
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see SetRightGripperRotation
         *
         **/
        virtual inline CRadians GetActuatedRightGripperRotation()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "GetActuatedRightGripperRotation");
            return m_cActuatedRightGripperRotation;
        }

        /**
         *
         * @brief Returns the current target left gripper aperture
         * notice that the actual aperture could be different
         *
         * @return target left gripper apperture
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see SetLeftGripperAperture
         *
         **/
        virtual inline CRadians GetActuatedLeftGripperAperture()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "GetActuatedLeftGripperAperture");
            return m_cActuatedLeftGripperAperture;
        }

        /**
         *
         * @brief Returns the current target right gripper aperture
         * notice that the actual aperture could be different
         *
         * @return target right gripper aperture
         * @see CCI_HandBotArmEncodersSensor
         * @see CCI_HandBotArmsActuator
         * @see SetRightGripperAperture
         *
         **/
        virtual inline CRadians GetActuatedRightGripperAperture()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(ARMS_ACTUATOR_XML_NAME, m_bIsUsingArms, "GetActuatedRightGripperAperture");
            return m_cActuatedRightGripperAperture;
        }

        /**
         *
         * @brief Returns the current status of the retrieve book routine
         *
         * @return status of the routine
         * @see CCI_HandBotRetrieveBookActuator
         *
         **/
        virtual inline UInt32 GetRetrieveBookStatus()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(RETRIEVE_BOOK_ACTUATOR_XML_NAME, m_bIsUsingRetrieveBookActuator, "GetRetrieveBookStatus");
            return m_pcRetrieveBookActuator -> GetRetrieveBookStatus();
        }

        /** Number of LEDs */
        static const UInt8 NUM_BEACON_LEDS;
        static const UInt8 NUM_LEDS;

    protected:

        /////////////
        //    SENSORS
        /////////////

        /** References to the sensors */
        CCI_HandBotArmEncodersSensor* m_pcArmEncodersSensor;
        CCI_HandBotProximitySensor*   m_pcProximitySensor;
        CCI_HandBotGripperCameras*    m_pcGripperCameras;
        CCI_HandBotHeadCameraSensor*  m_pcHeadCamera;

        /** Sensors booleans */
        bool m_bIsUsingArmEncodersSensor;
        bool m_bIsUsingProximitySensor;
        bool m_bIsUsingGripperCameras;
        bool m_bIsUsingHeadCamera;

        /** Sensors variables */
        UInt32 m_unLeftGripperCameraLineToFetch;
        UInt32 m_unRightGripperCameraLineToFetch;

        /* XML sensor names */
        static const std::string ARM_ENCODERS_SENSOR_XML_NAME;
        static const std::string PROXIMITY_SENSORS_XML_NAME;
        static const std::string GRIPPER_CAMERAS_XML_NAME;
        static const std::string HEAD_CAMERA_XML_NAME;

        ///////////////
        //    ACTUATORS
        ///////////////

        /** References to the actuators */
        CCI_HandBotBeaconLedsActuator*   m_pcBeaconActuator;
        CCI_HandBotLedsActuator*         m_pcLedsActuator;
        CCI_HandBotArmsActuator*         m_pcArmsActuator;
        CCI_HandBotRetrieveBookActuator* m_pcRetrieveBookActuator;

        /** Actuators booleans */
        bool m_bIsUsingBeacon;
        bool m_bIsUsingLeds;
        bool m_bIsUsingArms;
        bool m_bIsUsingRetrieveBookActuator;

        /** Actuator refresh booleans */
        bool m_bRefreshBeacon;
        bool m_bRefreshLeds;
        bool m_bRefreshArms;

        /** Actuators commands variables */
        CCI_HandBotBeaconLedsActuator::TLedSettings m_tActuatedBeaconLedColors;
        CCI_HandBotLedsActuator::TLedSettings       m_tActuatedLedColors;
        CRadians                                    m_cActuatedHeadRotation;
        CRadians                                    m_cActuatedLeftArmAperture;
        CRadians                                    m_cActuatedRightArmAperture;
        CRadians                                    m_cActuatedLeftGripperRotation;
        CRadians                                    m_cActuatedRightGripperRotation;
        CRadians                                    m_cActuatedLeftGripperAperture;
        CRadians                                    m_cActuatedRightGripperAperture;

        /* XML actuator names */
        static const std::string BEACON_ACTUATOR_XML_NAME;
        static const std::string LEDS_ACTUATOR_XML_NAME;
        static const std::string ARMS_ACTUATOR_XML_NAME;
        static const std::string RETRIEVE_BOOK_ACTUATOR_XML_NAME;

    };

}

#endif

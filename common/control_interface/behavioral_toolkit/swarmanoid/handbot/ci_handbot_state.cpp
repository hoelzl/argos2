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
 * @file <common/control_interface/behavioral_toolkit/swarmanoid/handbot/ci_handbot_state.cpp>
 *
 * @brief This file provides the control interface behavioral toolkit implementation for a hand-bot state.
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#include "ci_handbot_state.h"

namespace argos {

    /****************************************/
    /****************************************/

    /** XML sensors names */
    const std::string CCI_HandBotState::ARM_ENCODERS_SENSOR_XML_NAME = "handbot_arms_encoders";
    const std::string CCI_HandBotState::PROXIMITY_SENSORS_XML_NAME   = "handbot_proximity";
    const std::string CCI_HandBotState::GRIPPER_CAMERAS_XML_NAME     = "handbot_gripper_cameras";
    const std::string CCI_HandBotState::HEAD_CAMERA_XML_NAME         = "handbot_head_camera";

    /** XML actuators names */
    const std::string CCI_HandBotState::BEACON_ACTUATOR_XML_NAME         = "handbot_beacon_leds";
    const std::string CCI_HandBotState::LEDS_ACTUATOR_XML_NAME           = "handbot_leds";
    const std::string CCI_HandBotState::ARMS_ACTUATOR_XML_NAME           = "handbot_arms";
    const std::string CCI_HandBotState::RETRIEVE_BOOK_ACTUATOR_XML_NAME  = "handbot_retrieve_book";

    /** Sensor numbers */
    const UInt32 CCI_HandBotState::NUM_PROXIMITY_SENSOR_READINGS_PER_HAND = 12;

    /** Actuator numbers */
    const UInt8 CCI_HandBotState::NUM_BEACON_LEDS = 6;
    const UInt8 CCI_HandBotState::NUM_LEDS   = 12;

    /****************************************/
    /****************************************/

    void CCI_HandBotState::Init() {

        CCI_SwarmanoidRobotState::Init();

        /////////////////////////////////////////////////////////////////
        //   INITIALIZE ALL THE SENSORS DECLARED IN THE XML CONFIGURATION
        /////////////////////////////////////////////////////////////////

        TSensorMap mapSensors = m_pcRobot->GetAllSensors();
        TSensorMap::const_iterator itSensors;

        SENSOR_INIT_HELPER(ARM_ENCODERS_SENSOR_XML_NAME, CCI_HandBotArmEncodersSensor, m_pcArmEncodersSensor, m_bIsUsingArmEncodersSensor);
        SENSOR_INIT_HELPER(PROXIMITY_SENSORS_XML_NAME, CCI_HandBotProximitySensor, m_pcProximitySensor, m_bIsUsingProximitySensor);
        SENSOR_INIT_HELPER(GRIPPER_CAMERAS_XML_NAME, CCI_HandBotGripperCameras, m_pcGripperCameras, m_bIsUsingGripperCameras);
        SENSOR_INIT_HELPER(HEAD_CAMERA_XML_NAME, CCI_HandBotHeadCameraSensor, m_pcHeadCamera, m_bIsUsingHeadCamera);

        ///////////////////////////////////////////////////////////////////
        //   INITIALIZE ALL THE ACTUATORS DECLARED IN THE XML CONFIGURATION
        ///////////////////////////////////////////////////////////////////

        TActuatorMap mapActuators = m_pcRobot->GetAllActuators();
        TActuatorMap::const_iterator itActuators;

        ACTUATOR_INIT_HELPER(BEACON_ACTUATOR_XML_NAME, CCI_HandBotBeaconLedsActuator, m_pcBeaconActuator, m_bIsUsingBeacon);
        ACTUATOR_INIT_HELPER(LEDS_ACTUATOR_XML_NAME, CCI_HandBotLedsActuator, m_pcLedsActuator, m_bIsUsingLeds);
        ACTUATOR_INIT_HELPER(ARMS_ACTUATOR_XML_NAME, CCI_HandBotArmsActuator, m_pcArmsActuator, m_bIsUsingArms);
        ACTUATOR_INIT_HELPER(RETRIEVE_BOOK_ACTUATOR_XML_NAME, CCI_HandBotRetrieveBookActuator, m_pcRetrieveBookActuator, m_bIsUsingRetrieveBookActuator);

    }

    /****************************************/
    /****************************************/

    void CCI_HandBotState::ApplyState() {

        CCI_SwarmanoidRobotState::ApplyState();

        if (m_bRefreshBeacon && m_bIsUsingBeacon) {
            m_bRefreshBeacon = false;
            m_pcBeaconActuator->SetAllColors(m_tActuatedBeaconLedColors);
        }

        if (m_bRefreshLeds && m_bIsUsingLeds) {
            m_bRefreshLeds = false;
            m_pcLedsActuator->SetAllColors(m_tActuatedLedColors);
        }

        if (m_bRefreshArms && m_bIsUsingArms) {
            m_bRefreshArms = false;
            m_pcArmsActuator->SetHeadRotation(m_cActuatedHeadRotation);
            m_pcArmsActuator->SetLeftArmAperture(m_cActuatedLeftArmAperture);
            m_pcArmsActuator->SetRightArmAperture(m_cActuatedRightArmAperture);
            m_pcArmsActuator->SetLeftGripperRotation(m_cActuatedLeftGripperRotation);
            m_pcArmsActuator->SetRightGripperRotation(m_cActuatedRightGripperRotation);
            m_pcArmsActuator->SetLeftGripperAperture(m_cActuatedLeftGripperAperture);
            m_pcArmsActuator->SetRightGripperAperture(m_cActuatedRightGripperAperture);
        }

    }

    /****************************************/
    /****************************************/

}

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
 * @file <common/control_interface/behavioral_toolkit/swarmanoid/footbot/ci_footbot_state.cpp>
 *
 * @brief This file provides the control interface behavioral toolkit implementation for a foot-bot state.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#include "ci_footbot_state.h"

namespace argos {

    /****************************************/
    /****************************************/

    //XML sensors names
    const std::string CCI_FootBotState::BASE_GROUND_SENSOR_XML_NAME            = "footbot_base_ground";
    const std::string CCI_FootBotState::PROXIMITY_SENSORS_XML_NAME             = "footbot_proximity";
    const std::string CCI_FootBotState::DISTANCE_SCANNER_SENSOR_XML_NAME       = "footbot_distance_scanner";
    const std::string CCI_FootBotState::ENCODER_SENSOR_XML_NAME                = "footbot_encoder";
    const std::string CCI_FootBotState::LIGHT_SENSOR_XML_NAME                  = "footbot_light";
    const std::string CCI_FootBotState::MOTOR_GROUND_SENSOR_XML_NAME           = "footbot_motor_ground";
    const std::string CCI_FootBotState::WHEEL_SPEED_SENSOR_XML_NAME            = "footbot_wheel_speed";
    const std::string CCI_FootBotState::TURRET_TORQUE_SENSOR_XML_NAME          = "footbot_turret_torque";
    const std::string CCI_FootBotState::TURRET_ENCODER_SENSOR_XML_NAME         = "footbot_turret_encoder";
    const std::string CCI_FootBotState::GRIPPER_SENSOR_XML_NAME                = "footbot_gripper";
    const std::string CCI_FootBotState::CEILING_CAMERA_SENSOR_XML_NAME         = "footbot_ceiling_camera";
    const std::string CCI_FootBotState::OMNIDIRECTIONAL_CAMERA_SENSOR_XML_NAME = "footbot_omnidirectional_camera";

    //XML actuators names
    const std::string CCI_FootBotState::BEACON_ACTUATOR_XML_NAME           = "footbot_beacon";
    const std::string CCI_FootBotState::WHEELS_ACTUATOR_XML_NAME           = "footbot_wheels";
    const std::string CCI_FootBotState::GRIPPER_ACTUATOR_XML_NAME          = "footbot_gripper";
    const std::string CCI_FootBotState::LEDS_ACTUATOR_XML_NAME             = "footbot_leds";
    const std::string CCI_FootBotState::TURRET_ACTUATOR_XML_NAME           = "footbot_turret";
    const std::string CCI_FootBotState::DISTANCE_SCANNER_ACTUATOR_XML_NAME = "footbot_distance_scanner";

    //Sensor numbers
    const UInt32 CCI_FootBotState::NUM_BASE_GROUND_SENSOR_READINGS  = 8;
    const UInt32 CCI_FootBotState::NUM_PROXIMITY_SENSOR_READINGS    = 24;
    const UInt32 CCI_FootBotState::NUM_LIGHT_SENSOR_READINGS        = 24;
    const UInt32 CCI_FootBotState::NUM_MOTOR_GROUND_SENSOR_READINGS = 4;

    //Actuator numbers
    const UInt8  CCI_FootBotState::NUM_LEDS = 12;


    /****************************************/
    /****************************************/

    void CCI_FootBotState::Init()
    {

        CCI_SwarmanoidRobotState::Init();

        ///////////////////////////////////////////////////////////////////
        //   INITIALIZE ALL THE SENSORS DECLARED IN THE XML CONFIGURATION
        ///////////////////////////////////////////////////////////////////

        TSensorMap mapSensors = m_pcRobot->GetAllSensors();
        TSensorMap::const_iterator itSensors;

        SENSOR_INIT_HELPER(BASE_GROUND_SENSOR_XML_NAME,             CCI_FootBotBaseGroundSensor,            m_pcBaseGroundSensor,               m_bIsUsingBaseGroundSensor);
        SENSOR_INIT_HELPER(PROXIMITY_SENSORS_XML_NAME,              CCI_FootBotProximitySensor,             m_pcProximitySensor,                m_bIsUsingProximitySensor);
        SENSOR_INIT_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME,        CCI_FootBotDistanceScannerSensor,       m_pcDistanceScannerSensor,          m_bIsUsingDistanceScannerSensor);
        SENSOR_INIT_HELPER(ENCODER_SENSOR_XML_NAME,                 CCI_FootBotEncoderSensor,               m_pcEncoderSensor,                  m_bIsUsingEncoderSensor);
        SENSOR_INIT_HELPER(LIGHT_SENSOR_XML_NAME,                   CCI_FootBotLightSensor,                 m_pcLightSensor,                    m_bIsUsingLightSensor);
        SENSOR_INIT_HELPER(MOTOR_GROUND_SENSOR_XML_NAME,            CCI_FootBotMotorGroundSensor,           m_pcMotorGroundSensor,              m_bIsUsingMotorGroundSensor);
        SENSOR_INIT_HELPER(WHEEL_SPEED_SENSOR_XML_NAME,             CCI_FootBotWheelSpeedSensor,            m_pcWheelSpeedSensor,               m_bIsUsingWheelSpeedSensor);
        SENSOR_INIT_HELPER(TURRET_TORQUE_SENSOR_XML_NAME,           CCI_FootBotTurretTorqueSensor,          m_pcTurretTorqueSensor,             m_bIsUsingTurretTorqueSensor);
        SENSOR_INIT_HELPER(TURRET_ENCODER_SENSOR_XML_NAME,           CCI_FootBotTurretEncoderSensor,          m_pcTurretEncoderSensor,             m_bIsUsingTurretEncoderSensor);
        SENSOR_INIT_HELPER(GRIPPER_SENSOR_XML_NAME,                 CCI_FootBotGripperSensor,               m_pcGripperSensor,                  m_bIsUsingGripperSensor);
        SENSOR_INIT_HELPER(CEILING_CAMERA_SENSOR_XML_NAME,          CCI_FootBotCeilingCameraSensor,         m_pcCeilingCameraSensor,            m_bIsUsingCeilingCameraSensor);
        SENSOR_INIT_HELPER(OMNIDIRECTIONAL_CAMERA_SENSOR_XML_NAME,  CCI_FootBotOmnidirectionalCameraSensor, m_pcOmnidirectionalCameraSensor,    m_bIsUsingOmnidirectionalCameraSensor);

        ///////////////////////////////////////////////////////////////////
        //   INITIALIZE SENSOR RELATED VARIABLES
        ///////////////////////////////////////////////////////////////////

        //Sensor angles
        if (m_bIsUsingLightSensor)
            m_tLightSensorReadings = &m_pcLightSensor->GetReadings();

        if (m_bIsUsingCeilingCameraSensor)
            m_pcCeilingCameraSensor->Enable();

        if (m_bIsUsingOmnidirectionalCameraSensor)
            m_pcOmnidirectionalCameraSensor->Enable();

        ///////////////////////////////////////////////////////////////////
        //   INITIALIZE ALL THE ACTUATORS DECLARED IN THE XML CONFIGURATION
        ///////////////////////////////////////////////////////////////////

        TActuatorMap mapActuators = m_pcRobot->GetAllActuators();
        TActuatorMap::const_iterator itActuators;

        ACTUATOR_INIT_HELPER(BEACON_ACTUATOR_XML_NAME,              CCI_FootBotBeaconActuator,          m_pcBeaconActuator,             m_bIsUsingBeacon);
        ACTUATOR_INIT_HELPER(WHEELS_ACTUATOR_XML_NAME,              CCI_FootBotWheelsActuator,          m_pcWheelsActuator,             m_bIsUsingWheelsActuator);
        ACTUATOR_INIT_HELPER(GRIPPER_ACTUATOR_XML_NAME,             CCI_FootBotGripperActuator,         m_pcGripperActuator,            m_bIsUsingGripperActuator);
        ACTUATOR_INIT_HELPER(LEDS_ACTUATOR_XML_NAME,                CCI_FootBotLedsActuator,            m_pcLedsActuator,               m_bIsUsingLeds);
        ACTUATOR_INIT_HELPER(TURRET_ACTUATOR_XML_NAME,              CCI_FootBotTurretActuator,          m_pcTurretActuator,             m_bIsUsingTurretActuator);
        ACTUATOR_INIT_HELPER(DISTANCE_SCANNER_ACTUATOR_XML_NAME,    CCI_FootBotDistanceScannerActuator, m_pcDistanceScannerActuator,    m_bIsUsingDistanceScannerActuator);
    }

    /****************************************/
    /****************************************/

    void CCI_FootBotState::ApplyState()
    {
        CCI_SwarmanoidRobotState::ApplyState();

        if (m_bResetEncoderSensor && m_bIsUsingEncoderSensor) {
            m_bResetEncoderSensor = false;
        }

        if (m_bRefreshBeacon && m_bIsUsingBeacon) {
            m_bRefreshBeacon = false;
            m_pcBeaconActuator->SetColor(m_cActuatedBeaconColor);
        }

        if (m_bRefreshWheelsActuator && m_bIsUsingWheelsActuator) {
            m_bRefreshWheelsActuator = false;
            m_pcWheelsActuator->SetLinearVelocity(m_fActuatedLeftWheelSpeed,
                    m_fActuatedRightWheelSpeed);
        }

        if (m_bRefreshGripperActuator && m_bIsUsingGripperActuator) {
            m_bRefreshGripperActuator = false;
            m_pcGripperActuator->SetAperture(m_cActuatedGripperAperture);
        }

        if (m_bRefreshLeds && m_bIsUsingLeds) {
            m_bRefreshLeds = false;
            m_pcLedsActuator->SetAllColors( m_tActuatedLedColors );
        }

        if (m_bRefreshTurretActuator && m_bIsUsingTurretActuator) {
            m_bRefreshTurretActuator = false;
            if (m_eActuatedTurretMode == CCI_FootBotTurretActuator::MODE_POSITION_CONTROL) {
                m_pcTurretActuator->SetRotation(m_cActuatedTurretRotation);
            }
            else if (m_eActuatedTurretMode == CCI_FootBotTurretActuator::MODE_SPEED_CONTROL) {
                m_pcTurretActuator->SetRotationSpeed(m_nActuatedTurretRotationSpeed);
            }
        }
        if(m_bIsUsingDistanceScannerActuator){
            if (m_bRefreshDistanceScannerEnabled)
            {
                m_bRefreshDistanceScannerEnabled = false;
                if (m_bActuatedDistanceScannerEnabled)
                {
                    m_pcDistanceScannerActuator->Enable();
                }
                else
                {
                    m_pcDistanceScannerActuator->Disable();
                }
            }
            if (m_bRefreshDistanceScannerActuatorAngle)
            {
                m_bRefreshDistanceScannerActuatorAngle = false;
                m_pcDistanceScannerActuator->SetAngle(m_fActuatedDistanceScannerAngle);
            }
            if (m_bRefreshDistanceScannerActuatorRPM)
            {
                m_bRefreshDistanceScannerActuatorRPM = false;
                m_pcDistanceScannerActuator->SetRPM(m_fActuatedDistanceScannerRPM);
            }
        }

        if (m_bRefreshProximityCalibration && m_bIsUsingProximitySensor) {
	    // m_pcProximitySensor->Calibrate();
            m_bRefreshProximityCalibration = false;
        }

        if (m_bRefreshBaseGroundSensorCalibration && m_bIsUsingBaseGroundSensor) {
	    // m_pcBaseGroundSensor -> Calibrate();
            m_bRefreshBaseGroundSensorCalibration = false;
        }

    }

    /****************************************/
    /****************************************/

}

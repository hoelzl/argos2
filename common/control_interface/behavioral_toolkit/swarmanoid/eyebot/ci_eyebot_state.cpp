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
 * @file <common/control_interface/behavioral_toolkit/eyebot/ci_eyebot_state.cpp>
 *
 * @brief This file provides the control interface for an eyebot state. Check
 * file ci_robot_state.h for the full explanation.
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 *
 */

#include "ci_eyebot_state.h"

namespace argos{

    // XML sensors names
    const std::string CCI_EyeBotState::DISTANCE_SCANNER_SENSOR_XML_NAME = "eyebot_distance_scanner";
    const std::string CCI_EyeBotState::PAN_AND_TILT_CAMERA_SENSOR_XML_NAME = "eyebot_pan_and_tilt_camera";
    const std::string CCI_EyeBotState::ALTITUDE_SENSOR_XML_NAME = "eyebot_altitude";

    // XML actuators names
    const std::string CCI_EyeBotState::LEDS_ACTUATOR_XML_NAME = "eyebot_leds";
    const std::string CCI_EyeBotState::PAN_AND_TILT_ACTUATOR_XML_NAME = "eyebot_pan_and_tilt";
    const std::string CCI_EyeBotState::PROPELLERS_ACTUATOR_XML_NAME = "eyebot_propellers";

    // Sensor numbers
    const UInt32 CCI_EyeBotState::NUM_DISTANCE_SCANNER = 32;

    // Actuator numbers
    const UInt32 CCI_EyeBotState::NUM_LEDS = 16;

    void CCI_EyeBotState::Init()
    {
        CCI_SwarmanoidRobotState::Init();

        ///////////////////////////////////////////////////////////////////
        //   INITIALIZE ALL THE SENSORS DECLARED IN THE XML CONFIGURATION
        ///////////////////////////////////////////////////////////////////

        TSensorMap mapSensors = m_pcRobot->GetAllSensors();
        TSensorMap::const_iterator itSensors;
        SENSOR_INIT_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME,    CCI_EyeBotDistanceScannerSensor,    m_pcDistanceScannerSensor,  m_bIsUsingDistanceScannerSensor);
        SENSOR_INIT_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, CCI_EyeBotPanAndTiltCameraSensor,   m_pcPanAndTiltCameraSensor, m_bIsUsingPanAndTiltCameraSensor);
        SENSOR_INIT_HELPER(ALTITUDE_SENSOR_XML_NAME,            CCI_EyeBotAltitudeSensor,           m_pcAltitudeSensor,         m_bIsUsingAltitudeSensor);

        ///////////////////////////////////////////////////////////////////
        //   INITIALIZE ALL THE ACTUATORS DECLARED IN THE XML CONFIGURATION
        ///////////////////////////////////////////////////////////////////

        TActuatorMap mapActuators = m_pcRobot->GetAllActuators();
        TActuatorMap::const_iterator itActuators;
        ACTUATOR_INIT_HELPER(LEDS_ACTUATOR_XML_NAME,         CCI_EyeBotLedsActuator,       m_pcLedsActuator,       m_bIsUsingLeds);
        ACTUATOR_INIT_HELPER(PAN_AND_TILT_ACTUATOR_XML_NAME, CCI_EyeBotPanAndTiltActuator, m_pcPanAndTiltActuator, m_bIsUsingPanAndTiltActuator);
        ACTUATOR_INIT_HELPER(PROPELLERS_ACTUATOR_XML_NAME,   CCI_EyeBotPropellersActuator, m_pcPropellersActuator, m_bIsUsingPropellersActuator);
    }

    /****************************************/
    /****************************************/

    void CCI_EyeBotState::ApplyState()
    {
        CCI_SwarmanoidRobotState::ApplyState();

        if (m_bIsUsingLeds) {
            m_pcLedsActuator->SetAllColors( m_tActuatedLedColors );
        }
    }

}


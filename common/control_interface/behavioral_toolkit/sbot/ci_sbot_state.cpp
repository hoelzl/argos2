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
 * @file <common/control_interface/behavioral_toolkit/sbot/ci_footbot_state.h>
 *
 * @brief This file provides the control interface for an sbot state. Check
 * file ci_robot_state.h for the full explanation.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 */

#include "ci_sbot_state.h"

const string CCI_SBotState::SENSOR_CAMERA = "pie_camera";
const string CCI_SBotState::ACTUATOR_LEDS = "sbot_leds";
const string CCI_SBotState::SENSOR_ACTUATOR_WHEELS = "sbot_wheels";

using namespace argos;
/****************************************/
/****************************************/

int CCI_SBotState::Init() {

	TSensorsMap mapSensors = m_pcRobot->GetAllSensors();
	TSensorsMap::const_iterator itSensors = mapSensors.find(SENSOR_CAMERA);

	itSensors = mapSensors.find(SENSOR_CAMERA);
	if (itSensors != mapSensors.end()) {
		m_pcPieCameraSensor = (CCI_PieCameraSensor*) (m_pcRobot->GetSensor(SENSOR_CAMERA));
		m_bIsUsingCameraSensor = true;
	}

	TActuatorsMap mapActuators = m_pcRobot->GetAllActuators();
	TActuatorsMap::const_iterator itActuators = mapActuators.find(ACTUATOR_LEDS);

	itActuators = mapActuators.find(ACTUATOR_LEDS);
	if (itActuators != mapActuators.end()) {
		m_pcLedsActuator = (CCI_SBotLedsActuator*) (m_pcRobot->GetActuator(ACTUATOR_LEDS));
		m_bIsUsingLedsActuator = true;
	}

	itActuators = mapActuators.find(SENSOR_ACTUATOR_WHEELS);
	if (itActuators != mapActuators.end()) {
		m_pcWheelsActuator = (CCI_SBotWheelsActuator*) (m_pcRobot->GetActuator(SENSOR_ACTUATOR_WHEELS));
		m_bIsUsingWheelsActuator = true;
	}

	return 0;
}
/****************************************/
/****************************************/

void CCI_SBotState::ReadState() {

	if (m_bIsUsingCameraSensor)
		m_pcCameraVector = m_pcPieCameraSensor->GetAllPieCameraSensorObjectReadings();

}
/****************************************/
/****************************************/

void CCI_SBotState::ApplyState() {

	if (m_bIsUsingWheelsActuator) {
		m_pcWheelsActuator->SetSBotWheelsAngularVelocity(m_fLeftWheelSpeed, m_fRightWheelSpeed);
	}

	if (m_bIsUsingLedsActuator) {
		for (unsigned int i = 0; i < NUM_LEDS; i++) {
			if (m_pcLedsActuator != NULL) {
				m_pcLedsActuator->SetSBotLedColor(i, m_unLEDColors[i]);
			}
		}
	}
}

/****************************************/
/****************************************/

void CCI_SBotState::SetSBotWheelsAngularVelocity(Real fLeftSpeed, Real fRightSpeed) {
	if (m_bIsUsingWheelsActuator) {
		m_fLeftWheelSpeed = fLeftSpeed;
		m_fRightWheelSpeed = fRightSpeed;
	}
}

/****************************************/
/****************************************/

void CCI_SBotState::SetSBotLedsColor(unsigned int unColor) {
	if (m_bIsUsingLedsActuator)
		for (unsigned int i = 0; i < NUM_LEDS; i++) {
			m_unLEDColors[i] = unColor;
		}
}
/****************************************/
/****************************************/

void CCI_SBotState::SetSBotLedColor(const unsigned int unLedNumber, const unsigned int unColor) {
	if (m_bIsUsingLedsActuator)
		m_unLEDColors[unLedNumber] = unColor;
}
/****************************************/
/****************************************/


CameraObjectVector* CCI_SBotState::GetAllPieCameraSensorObjectReadings() {
	if (m_bIsUsingCameraSensor) {
		return m_pcCameraVector;
	}
	else
		return NULL;
}

void CCI_SBotState::GetSBotWheelsAngularVelocity(Real* fLeftSpeed, Real* fRightSpeed) {
	*fLeftSpeed = m_fLeftWheelSpeed;
	*fRightSpeed = m_fRightWheelSpeed;
}

void CCI_SBotState::GetSBotLedsColor(unsigned int* unColor) {
	for (unsigned int i = 0; i < NUM_LEDS; i++) {
		unColor[i] = m_unLEDColors[i];
	}
}


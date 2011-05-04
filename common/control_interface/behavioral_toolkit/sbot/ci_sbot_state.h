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
 * @file <common/control_interface/behavioral_toolkit/sbot/ci_sbot_state.h>
 *
 * @brief This file provides the control interface for an footbot state. Check
 * file ci_robot_state.h for the full explanation.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 */

#ifndef CI_SBOTSTATE_H_
#define CI_SBOTSTATE_H_

namespace argos {

	class CCI_SBotState;

}
;

#include "ci_robot_state.h"

// Sensors includes
#include "ci_pie_camera_sensor.h"


// Actuators includes
#include "sbot/ci_sbot_wheels_actuator.h"
#include "sbot/ci_sbot_leds_actuator.h"


#include <vector>

using namespace argos;
using namespace std;



namespace argos {

	class CCI_SBotState: public CCI_RobotState {

		// Constants

		public:

			static const string SENSOR_CAMERA;

			static const string ACTUATOR_LEDS;

			static const string SENSOR_ACTUATOR_WHEELS;

			static const unsigned int NUM_LEDS = 8;




			// Default constructor
			CCI_SBotState(CCI_Robot* pc_robot):
				CCI_RobotState(pc_robot),
				m_bIsUsingCameraSensor(false),
				m_pcPieCameraSensor(NULL),
				m_pcCameraVector(NULL),

				m_bIsUsingWheelsActuator(false),
				m_bIsUsingLedsActuator(false),
				m_pcWheelsActuator(NULL),
				m_pcLedsActuator(NULL),

				m_fLeftWheelSpeed(0.0),
				m_fRightWheelSpeed(0.0),
				m_unLEDColors(NULL)
				{
					m_unLEDColors = new unsigned int[NUM_LEDS];
					for (unsigned i = 0; i < NUM_LEDS; i++) {
						m_unLEDColors[i] = COLOR_BLACK;
					}
				}

			// Copy constructor. Copy all the primitive attributes and also the references
			// (whose objects can be shared) except the LEDs actuator variable whose content
			// needs to be replicated
			CCI_SBotState(const CCI_SBotState& c_sbot_state) :
				CCI_RobotState(c_sbot_state.m_pcRobot),
				m_bIsUsingCameraSensor(c_sbot_state.m_bIsUsingCameraSensor),
				m_pcPieCameraSensor(c_sbot_state.m_pcPieCameraSensor),
				m_pcCameraVector(c_sbot_state.m_pcCameraVector),

				m_bIsUsingWheelsActuator(c_sbot_state.m_bIsUsingWheelsActuator),
				m_bIsUsingLedsActuator(c_sbot_state.m_bIsUsingLedsActuator),
				m_pcWheelsActuator(c_sbot_state.m_pcWheelsActuator),
				m_pcLedsActuator(c_sbot_state.m_pcLedsActuator),

				m_fLeftWheelSpeed(c_sbot_state.m_fLeftWheelSpeed),
				m_fRightWheelSpeed(c_sbot_state.m_fRightWheelSpeed),
				m_unLEDColors(NULL){
					m_unLEDColors = new unsigned int[NUM_LEDS];
					memcpy(m_unLEDColors,c_sbot_state.m_unLEDColors,NUM_LEDS * sizeof(unsigned int));
				}


			// = operator overriding. Used with the same semantic of the copy constructor
			CCI_SBotState& operator=(const CCI_SBotState& c_sbot_state)  {
				if(this != &c_sbot_state) {
					m_pcRobot = c_sbot_state.m_pcRobot;
					m_bIsUsingCameraSensor = c_sbot_state.m_bIsUsingCameraSensor;
					m_pcPieCameraSensor = c_sbot_state.m_pcPieCameraSensor;
					m_pcCameraVector = c_sbot_state.m_pcCameraVector;

					m_bIsUsingWheelsActuator = c_sbot_state.m_bIsUsingWheelsActuator;
					m_bIsUsingLedsActuator = c_sbot_state.m_bIsUsingLedsActuator;
					m_pcWheelsActuator = c_sbot_state.m_pcWheelsActuator;
					m_pcLedsActuator = c_sbot_state.m_pcLedsActuator;

					m_fLeftWheelSpeed = c_sbot_state.m_fLeftWheelSpeed;
					m_fRightWheelSpeed = c_sbot_state.m_fRightWheelSpeed;

					m_unLEDColors = new unsigned int[NUM_LEDS];
					memcpy(m_unLEDColors,c_sbot_state.m_unLEDColors,NUM_LEDS * sizeof(unsigned int));
				}
				return *this;
			}

			virtual ~CCI_SBotState() {
				delete[] m_unLEDColors;
			}

			virtual int Init();

			virtual void ReadState();

			virtual void ApplyState();


			// Sensors methods
			virtual CameraObjectVector* GetAllPieCameraSensorObjectReadings();

			// Actuators methods - setters
			virtual void SetSBotWheelsAngularVelocity(Real fLeftSpeed, Real fRightSpeed);
			virtual void SetSBotLedsColor ( const unsigned int unColor );
			virtual void SetSBotLedColor(const unsigned int unLedNumber, const unsigned int unColor);

			// Actuators methods - getters
			virtual void GetSBotWheelsAngularVelocity(Real* fLeftSpeed, Real* fRightSpeed);
			virtual void GetSBotLedsColor ( unsigned int* unColor );

			// Associations and attributes

		protected:

			// Sensors booleans
			bool m_bIsUsingCameraSensor;

			// Sensors
			CCI_PieCameraSensor* m_pcPieCameraSensor;

			// Sensors variables
			CameraObjectVector* m_pcCameraVector;

			// Actuators booleans
			bool m_bIsUsingWheelsActuator;
			bool m_bIsUsingLedsActuator;

			// Actuators
			CCI_SBotWheelsActuator* m_pcWheelsActuator;
			CCI_SBotLedsActuator* m_pcLedsActuator;

			// Actuator variables
			Real m_fLeftWheelSpeed;
			Real m_fRightWheelSpeed;
			unsigned int* m_unLEDColors;


		};

}
;

#endif /* CI_SBOTSTATE_H_ */

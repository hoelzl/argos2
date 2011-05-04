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
 * @file <common/control_interface/behavioral_toolkit/eyebot/ci_eyebot_state.h>
 *
 * @brief This file provides the control interface for an eyebot state. Check
 * file ci_robot_state.h for the full explanation.
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#ifndef CI_EYEBOT_STATE_H_
#define CI_EYEBOT_STATE_H_

namespace argos {

    class CCI_EyeBotState;

}
;

#include <argos2/common/control_interface/behavioral_toolkit/swarmanoid/ci_swarmanoid_robot_state.h>

// Sensors includes
#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_distance_scanner_sensor.h>
#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_pan_and_tilt_camera_sensor.h>
#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_altitude_sensor.h>

// Actuators includes
#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_leds_actuator.h>
#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_propellers_actuator.h>
#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_pan_and_tilt_camera_actuator.h>

namespace argos {

    class CCI_EyeBotState: public CCI_SwarmanoidRobotState {

    public:

        static const UInt32 NUM_LEDS;
        static const UInt32 NUM_DISTANCE_SCANNER;

        // Default constructor
        CCI_EyeBotState(CCI_Robot& pc_robot) :
            CCI_SwarmanoidRobotState(pc_robot),

            /** Initialize all sensors booleans */
            m_bIsUsingDistanceScannerSensor  (false),
            m_bIsUsingPanAndTiltCameraSensor (false),
            m_bIsUsingAltitudeSensor         (false),

            /** Initialize all the sensors */
            m_pcDistanceScannerSensor  (NULL),
            m_pcPanAndTiltCameraSensor (NULL),
            m_pcAltitudeSensor         (NULL),

            /** Initialize all actuators booleans */
            m_bIsUsingLeds               (false),
            m_bIsUsingPanAndTiltActuator (false),
            m_bIsUsingPropellersActuator (false),

            /** Initialize all the actuators */
            m_pcLedsActuator        (NULL),
            m_pcPanAndTiltActuator  (NULL),
            m_pcPropellersActuator  (NULL),

            m_tActuatedLedColors            (NULL)
        {
            m_tActuatedLedColors = CCI_EyeBotLedsActuator::TLedSettings(CCI_EyeBotState::NUM_LEDS);
            for (unsigned i = 0; i < CCI_EyeBotState::NUM_LEDS; i++) {
                m_tActuatedLedColors[i] = CColor::BLACK;
            }
        }

        /**
         *
         * Copy Constructor.
         *
         */
        CCI_EyeBotState(const CCI_EyeBotState& c_eyebot_state) : CCI_SwarmanoidRobotState(c_eyebot_state)
        {
            *this = c_eyebot_state;
        }

        // = operator overriding. Used with the same semantic of the copy constructor
        CCI_EyeBotState& operator=(const CCI_EyeBotState& c_eyebot_state)
        {

            if (this != &c_eyebot_state) {

                CCI_SwarmanoidRobotState::operator=(c_eyebot_state);

                /** Copy the sensors booleans */
                m_bIsUsingDistanceScannerSensor = c_eyebot_state.m_bIsUsingDistanceScannerSensor;
                m_bIsUsingPanAndTiltCameraSensor = c_eyebot_state.m_bIsUsingPanAndTiltCameraSensor;
                m_bIsUsingAltitudeSensor = c_eyebot_state.m_bIsUsingAltitudeSensor;

                /** Copy the references to the sensors */
                m_pcDistanceScannerSensor = c_eyebot_state.m_pcDistanceScannerSensor;
                m_pcPanAndTiltCameraSensor = c_eyebot_state.m_pcPanAndTiltCameraSensor;
                m_pcAltitudeSensor = c_eyebot_state.m_pcAltitudeSensor;

                /** Copy the actuators booleans */
                m_bIsUsingLeds = c_eyebot_state.m_bIsUsingLeds;
                m_bIsUsingPropellersActuator = c_eyebot_state.m_bIsUsingPropellersActuator;
                m_bIsUsingPanAndTiltActuator = c_eyebot_state.m_bIsUsingPanAndTiltActuator;

                /** Copy the references to the actuators */
                m_pcLedsActuator = c_eyebot_state.m_pcLedsActuator;
                m_pcPanAndTiltActuator = c_eyebot_state.m_pcPanAndTiltActuator;
                m_pcPropellersActuator = c_eyebot_state.m_pcPropellersActuator;

                /** Copy the actuated commands */
                m_tActuatedLedColors = c_eyebot_state.m_tActuatedLedColors;

            }
            return *this;
        }

        virtual ~CCI_EyeBotState()
        {
        }

        virtual void Init();

        virtual inline void ReadState() {};

        virtual void ApplyState();

        // Sensor methods - getters
        virtual inline const CCI_EyeBotDistanceScannerSensor::TReadings& GetAllDistanceScannerReadings()
        {
            CHECK_IS_SENSOR_USED_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME, m_bIsUsingDistanceScannerSensor, "GetAllDistanceScannerReadings");
            return m_pcDistanceScannerSensor->GetReadings();
        }

        virtual inline Real GetDistanceScannerReading(CRadians c_angle)
        {
            CHECK_IS_SENSOR_USED_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME, m_bIsUsingDistanceScannerSensor, "GetDistanceScannerReading");
            return m_pcDistanceScannerSensor->GetReading(c_angle);
        }

        /* Temporarily comment this out: this function is not supported by the CI
        virtual inline const CCI_EyeBotDistanceScannerSensor::TAngles& GetAllDistanceScannerAngles()
        {
            CHECK_IS_SENSOR_USED_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME, m_bIsUsingDistanceScannerSensor, "GetAllDistanceScannerAngles");
            return m_pcDistanceScannerSensor->GetAngles();
        }
        */

        /* Temporarily comment this out: this function is not supported by the CI

        virtual inline CRadians GetDistanceScannerAngle(UInt32 un_index)
        {
            CHECK_IS_SENSOR_USED_HELPER(DISTANCE_SCANNER_SENSOR_XML_NAME, m_bIsUsingDistanceScannerSensor, "GetDistanceScannerAngle");
            return m_pcDistanceScannerSensor->GetAngle(un_index);
        }
        */

        /* Temporarily comment this out: this function is not supported by the CI
        virtual inline const CCI_CameraSensor::TBlobList& GetBlobs()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "GetBlobs");
            return m_pcPanAndTiltCameraSensor->GetBlobs();
        }

        virtual inline const CCI_CameraSensor::TBlobList& GetBlobs(UInt64& un_sensor_updating_counter)
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "GetBlobs");
            return m_pcPanAndTiltCameraSensor->GetBlobs(un_sensor_updating_counter);
        }
        */

        virtual inline const Real GetAltitude()
        {
            CHECK_IS_SENSOR_USED_HELPER(ALTITUDE_SENSOR_XML_NAME, m_bIsUsingAltitudeSensor, "GetAltitude");
            return m_pcAltitudeSensor->GetAltitude();
        }

        /* Temporarily comment this out: this function is not supported by the CI
        virtual inline void EnableBlobDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "EnableBlobDetection");
            m_pcPanAndTiltCameraSensor->EnableBlobDetection();
        }

        virtual inline void DisableBlobDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "DisableBlobDetection");
            m_pcPanAndTiltCameraSensor->DisableBlobDetection();
        }

        virtual inline bool IsBlobDetectionEnabled()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "IsBlobDetectionEnabled");
            return m_pcPanAndTiltCameraSensor->IsBlobDetectionEnabled();
        }
         */
        virtual inline void EnableBookshelfDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "EnableBookshelfDetection");
            m_pcPanAndTiltCameraSensor->Enable();
            m_pcPanAndTiltCameraSensor->EnableBookshelfDetection();
        }

        virtual inline void DisableBookshelfDetection()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "DisableBookshelfDetection");
            m_pcPanAndTiltCameraSensor->DisableBookshelfDetection();
            m_pcPanAndTiltCameraSensor->Disable();
        }

        virtual inline bool IsBookshelfDetectionEnabled()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "IsBookshelfDetectionEnabled");
            return m_pcPanAndTiltCameraSensor->IsBookshelfDetectionEnabled();
        }

        virtual inline bool IsBookshelfInView()
        {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "IsBookshelfInView");
            return m_pcPanAndTiltCameraSensor->IsBookshelfInView();
        }


        virtual inline void EnableFootbotCounter() {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "EnableFootbotCounter");
            m_pcPanAndTiltCameraSensor->Enable();
            m_pcPanAndTiltCameraSensor->EnableFootbotCounter();
        }

        virtual inline void DisableFootbotCounter() {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "DisableFootbotCounter");
            m_pcPanAndTiltCameraSensor->DisableFootbotCounter();
            m_pcPanAndTiltCameraSensor->Disable();
        }

        virtual inline bool IsFootbotCounterEnabled() const {
            CHECK_IS_SENSOR_USED_HELPER(PAN_AND_TILT_CAMERA_SENSOR_XML_NAME, m_bIsUsingPanAndTiltCameraSensor, "IsFootbotCounterEnabled");
            return m_pcPanAndTiltCameraSensor->IsFootbotCounterEnabled();
        }

        virtual inline std::vector<CCI_EyeBotPanAndTiltCameraSensor::SFootbot> GetFootbotsDetected(){
            return m_pcPanAndTiltCameraSensor->GetFootbotsDetected();
        }

        // Actuator methods - setters
        /**
         *
         * @brief Sets the color for the specified LED
         *
         * @param un_index index of the LED to be set
         * @param c_color color to be set
         * @see CColor
         *
         **/
        virtual inline void SetSingleLedColor(UInt8 un_index, CColor c_color)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetSingleLedColor");
            m_tActuatedLedColors[un_index] = CColor(c_color.GetRed(), c_color.GetGreen(), c_color.GetBlue(), c_color.GetAlpha());
        }

        /**
         *
         * @brief Sets the color for all the LEDs
         *
         * @param c_color color to be set
         * @see CColor
         *
         **/
        virtual inline void SetAllLedsColor(CColor c_color)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetAllLedsColor");
            for (UInt8 i = 0; i < NUM_LEDS; i++) {
                m_tActuatedLedColors[i] = CColor(c_color.GetRed(), c_color.GetGreen(), c_color.GetBlue(), c_color.GetAlpha());
            }
        }

        /**
         *
         * @brief Sets the intensity for the specified LED
         *
         * @param un_index index of the LED to be set
         * @param un_intensity intensity of the color (0-255)
         * @see CColor
         *
         **/
        virtual inline void SetSingleLedIntensity(UInt8 un_index, UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetSingleLedIntensity");
            m_tActuatedLedColors[un_index].SetAlpha(un_intensity);
        }

        /**
         *
         * @brief Sets the intensity for all the LEDs
         *
         * @param un_intensity intensity of the color (0-255)
         * @see CColor
         *
         **/
        virtual inline void SetAllLedsIntensity(UInt8 un_intensity)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "SetAllLedsIntensity");
            for (UInt32 i=0; i < NUM_LEDS; i++) {
                m_tActuatedLedColors[i].SetAlpha(un_intensity);
            }
            m_pcLedsActuator->SetAllColors(m_tActuatedLedColors);
        }


        virtual inline void EnableLedRings(const CCI_EyeBotLedsActuator::ERingModes& e_mode)
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "EnableSideLedRingOnly");
            m_pcLedsActuator->EnableRings(e_mode);
        }

        virtual inline void SetPan( const CRadians& c_pan )
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PAN_AND_TILT_ACTUATOR_XML_NAME, m_bIsUsingPanAndTiltActuator, "SetPan");
            m_pcPanAndTiltActuator->SetPan( c_pan );
        }

        virtual inline void SetTilt( const CRadians& c_tilt )
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PAN_AND_TILT_ACTUATOR_XML_NAME, m_bIsUsingPanAndTiltActuator, "SetTilt");
            m_pcPanAndTiltActuator->SetTilt( c_tilt );
        }

       virtual inline void SetVelocity( Real f_linear_velocity, Real f_angular_velocity )
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "SetLinearVelocity");
            m_pcPropellersActuator->SetVelocity( f_linear_velocity, f_angular_velocity );
        }

        virtual inline void SetForce( Real f_pitch_force, Real f_roll_force, Real f_thrust_force )
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "SetForce");
            m_pcPropellersActuator->SetForce( f_pitch_force, f_roll_force, f_thrust_force );
        }

        virtual inline void SetYawRotation( Real f_yaw_rotation )
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "SetYawRotation");
            m_pcPropellersActuator->SetYawRotation( f_yaw_rotation );
        }

        /* Temporarily comment this out: this function is not supported by the CI
        virtual inline void RotateClockwise()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "RotateClockwise");
            m_pcPropellersActuator->RotateClockwise();
        }

        virtual inline void RotateAntiClockwise()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "RotateAntiClockwise");
            m_pcPropellersActuator->RotateAntiClockwise();
        }
         */

        virtual inline void AttachToCeiling()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "AttachToCeiling");
            m_pcPropellersActuator->AttachToCeiling();
        }

        virtual inline void DetachFromCeiling()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "DetachFromCeiling");
            m_pcPropellersActuator->DetachFromCeiling();
        }

        virtual inline void SetDesiredAltitude( Real f_desired_altitude )
        {
            CHECK_IS_ACTUATOR_USED_HELPER(PROPELLERS_ACTUATOR_XML_NAME, m_bIsUsingPropellersActuator, "SetDesiredAltitude");
            m_pcPropellersActuator->SetDesiredAltitude( f_desired_altitude );
        }

        ///////////////////////////////////////////////////////////////////////////////////////////
        //   ACTUATORS GETTERS METHOD
        //   WARNING: many of these methods return the actuated commands that are going to be send.
        //            Therefore the values are not measures of the real state of the robot.
        ///////////////////////////////////////////////////////////////////////////////////////////

        /**
         *
         * @brief Returns the current target color for the specified LED
         * notice that the actual color could be different
         *
         * @param un_index index of the target LED
         * @return target led color
         * @see CColor
         * @see CCI_EyeBotLedsActuator
         *
         **/
        virtual inline CColor GetActuatedSingleLedColor(UInt32 un_index)
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
         * @see CCI_EyeBotLedsActuator
         *
         **/
        virtual inline CCI_EyeBotLedsActuator::TLedSettings& GetActuatedAllLedColors()
        {
            CHECK_IS_ACTUATOR_USED_HELPER(LEDS_ACTUATOR_XML_NAME, m_bIsUsingLeds, "GetAllActuatedLedColors");
            return m_tActuatedLedColors;
        }


    protected:

        // Sensors booleans
        bool m_bIsUsingDistanceScannerSensor;
        bool m_bIsUsingPanAndTiltCameraSensor;
        bool m_bIsUsingAltitudeSensor;

        // Sensors
        CCI_EyeBotDistanceScannerSensor*  m_pcDistanceScannerSensor;
        CCI_EyeBotPanAndTiltCameraSensor* m_pcPanAndTiltCameraSensor;
        CCI_EyeBotAltitudeSensor*         m_pcAltitudeSensor;

        // Actuators booleans
        bool m_bIsUsingLeds;
        bool m_bIsUsingPanAndTiltActuator;
        bool m_bIsUsingPropellersActuator;

        // Actuators
        CCI_EyeBotLedsActuator*            m_pcLedsActuator;
        CCI_EyeBotPanAndTiltActuator*      m_pcPanAndTiltActuator;
        CCI_EyeBotPropellersActuator*	   m_pcPropellersActuator;

        // Sensor variables

        // Actuator variables
        CCI_EyeBotLedsActuator::TLedSettings m_tActuatedLedColors;

        /* XML sensor names */
        static const std::string DISTANCE_SCANNER_SENSOR_XML_NAME;
        static const std::string PAN_AND_TILT_CAMERA_SENSOR_XML_NAME;
        static const std::string ALTITUDE_SENSOR_XML_NAME;

        /* XML actuator names */
        static const std::string LEDS_ACTUATOR_XML_NAME;
        static const std::string PROPELLERS_ACTUATOR_XML_NAME;
        static const std::string PAN_AND_TILT_ACTUATOR_XML_NAME;

    };

}
;

#endif /* CI_EYEBOTSTATE_H_ */

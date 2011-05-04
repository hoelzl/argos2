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
 * @file <common/control_interface/swarmanoid/ci_camera_sensor.h>
 *
 * @brief This file provides the definition of the e-puck camera sensor and of the data structure
 * representing its readings.
 * The camera sensor enables the user to extract information from the image acquired by the
 * simulated or by the physical camera (under development).
 *
 * This interface defines also the basic type of information that at the moment
 * it is possible to extract from image processing on the real robot, that is the position
 * of the LED of neighboring robots.
 *
 * @author Laurent Compere <laurent.compere@ulb.ac.be>
 */

#ifndef CI_CAMERA_SENSOR_H
#define CI_CAMERA_SENSOR_H

namespace argos {
	class CCI_CameraSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>
#include <argos2/common/utility/datatypes/color.h>
#include <vector>

namespace argos {

	class CCI_EPuckCameraSensor: virtual public CCI_Sensor {

		public:

			/**
			 * Constructor
			 */
			CCI_EPuckCameraSensor() {
			}

			/**
			 * Destructor
			 */
			virtual ~CCI_EPuckCameraSensor() {
			}

			/**
			 * Returns a reference to the current camera readings.
			 */
			inline virtual UInt8 ** GetCameraReadings() {
				return m_punCameraReadings;
			}

			/**
			 * Enables image acquisition and processing.
			 */
			virtual void Enable() = 0;

			/**
			 * Disables image acquisition and processing.
			 */
			virtual void Disable() = 0;

                        /**
                          * Sets the resolution of the camera (size limited).
                          */

                        virtual void ChangeResolution(UInt16 un_width, UInt16 un_height) = 0;

                        /**
                          * Return the width of the image
                          */
                        virtual UInt16 GetWidth() = 0;

                        /**
                          * Return the height of the image
                          */
                        virtual UInt16 GetHeight() = 0;

		protected:
			/* camera readings */
			UInt8 ** m_punCameraReadings;
	};

}/* namespace argos */

#endif

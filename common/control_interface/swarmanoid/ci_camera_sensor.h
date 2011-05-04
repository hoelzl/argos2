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
 * @brief This file provides the definition of the base camera sensor and of the data structure
 * representing its readings.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Alessandro Stranieri - <alessandro.stranieri@ulb.ac.be>
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

	/**
	 * @brief This class provides the most general interface to a camera.
	 *
	 * The camera sensor enables the user to extract information from the images
	 * acquired by the simulated or by the physical camera.
	 *
	 * This interface defines also the basic type of information that at the moment
	 * it is possible to extract from image processing on the real robot, that is the position
	 * of the colored LED of neighboring robots.
	 *
	 * The camera can be enabled and disabled, in order to save computation time.
	 *
	 */
	class CCI_CameraSensor: virtual public CCI_Sensor {

		public:

			/**
			 * An SBlob represents a generic colored 2D segment in the image.
			 *
			 * A blob has a color as defined by the CColor class. The position of the blob is given in
			 * polar coordinates. The angle is counted counter-clockwise watching the FootBot from top, as to respect the
			 * general frame convention. As for the distances, both the distance in cms from the robot center and in pixels from the
			 * optical center in the image are given. The last attribute is the area of the blob in pixels.
			 *
			 * @see CColor
			 */
			struct SBlob {
					/* color */
					CColor Color;
					/* angle */
					CRadians Angle;
					/* distance in cms */
					Real Distance;
					/* distance in pixels */
					Real RawDistance;
					/* area in pixels */
					Real Area;
					/**
					 * Constructor
					 */
					SBlob() :
						Color(CColor::BLACK), Distance(0.0) {
					}
					/**
					 * Constructor with paramters
					 *
					 * @param c_color Blob color
					 * @param c_angle Blob center
					 * @param f_distance Blob distance in cm
					 * @param f_raw_distance Blob distance in pixels
					 * @param f_area Blob Area in pixel
					 */
					SBlob(const CColor& c_color, const CRadians& c_angle, Real f_distance, Real f_raw_distance, Real f_area) :
						Color(c_color), Angle(c_angle), Distance(f_distance), RawDistance(f_raw_distance), Area(f_area) {
					}

					friend std::ostream& operator<<(std::ostream& c_os, const SBlob& s_blob) {
						c_os << "(Color = " << s_blob.Color << "," << "Angle = " << ToDegrees(s_blob.Angle) << ","
								<< "Distance = " << s_blob.Distance << "," << "Raw Distance = " << s_blob.RawDistance
								<< "," << "Area = " << s_blob.Area << ")";
						return c_os;
					}
			};

			/**
			 * Vector of pointers to colored blobs.
			 */
			typedef std::vector<SBlob*> TBlobList;

			/**
			 * An SCameraReadings represents the readings collected thorugh the camera at a specific time step.
			 * It consists of two members, the vector of colored blobs detected and a counter which stores the time step
			 * at which the blobs became available.
			 */
			struct SCameraReadings {
					TBlobList BlobList;
					UInt64 Counter;

					SCameraReadings() :
						Counter(0) {
					}

					friend std::ostream& operator<<(std::ostream& c_os, const SCameraReadings& s_reading) {
						c_os << "Counter: " <<  s_reading.Counter << std::endl;
						for (size_t i = 0; i < s_reading.BlobList.size(); i++) {
							c_os << "Blob[" << i << "]: " << s_reading.BlobList[i] << std::endl;
						}
						return c_os;
					}
			};

		public:

			/**
			 * Constructor
			 */
			CCI_CameraSensor() {
			}

			/**
			 * Destructor
			 */
			virtual ~CCI_CameraSensor() {
			}

			/**
			 * Returns a reference to the current camera readings.
			 */
			inline virtual const SCameraReadings& GetCameraReadings() {
				return m_sCameraReadings;
			}

			/**
			 * Enables image acquisition and processing.
			 */
			virtual void Enable() = 0;

			/**
			 * Disable image acquisition and processing.
			 */
			virtual void Disable() = 0;

		protected:
			/* camera readings */
			SCameraReadings m_sCameraReadings;
	};

}/* namespace argos */

#endif

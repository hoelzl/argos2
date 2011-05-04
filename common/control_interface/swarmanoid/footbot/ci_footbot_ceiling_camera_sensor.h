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
 * @file <common/control_interface/footbot/ci_footbot_camera_sensor.h>
 *
 * @brief This file provides the definition of the FootBot ceiling camera sensor.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CI_FOOTBOT_CEILING_CAMERA_SENSOR_H
#define CI_FOOTBOT_CEILING_CAMERA_SENSOR_H

namespace argos {
	class CCI_FootBotCeilingCameraSensor;
}

#include <argos2/common/control_interface/swarmanoid/ci_camera_sensor.h>

namespace argos {

	/**
	 * This class provides the main interface to the ceiling camera on the FootBot.
	 *
	 * @see CCI_CameraSensor
	 */
	class CCI_FootBotCeilingCameraSensor: virtual public CCI_CameraSensor {

		public:
			/**
			 * Constructor
			 */
			CCI_FootBotCeilingCameraSensor() :
				CCI_CameraSensor() {
			}
			/**
			 * Destructor
			 */
			virtual ~CCI_FootBotCeilingCameraSensor() {
			}
	};

}/* namespace argos */

#endif

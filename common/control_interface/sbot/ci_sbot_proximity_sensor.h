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
 * @file <common/control_interface/sbot/ci_sbot_proximity_sensor.h>
 *
 * @brief This file provides the definition of the sbot proximity sensor.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_SBOTPROXIMITYSENSOR_H
#define CCI_SBOTPROXIMITYSENSOR_H

/* To avoid dependency problems when including */
namespace argos {

   class CCI_SBotProximitySensor;

};

#include <argos2/common/control_interface/ci_sensor.h>
#include "ci_proximity_sensor.h"



namespace argos {

   class CCI_SBotProximitySensor: public CCI_ProximitySensor {
	 // Associations
	 // Attributes
	 // Operations

      public:

      /**
       * @brief Read the value of a proximity sensor.
       * @param n_sensor_index Number of sensor. Sensors are numbered CCW when seen from above, from 0 to 14 starting from the rigid gripper. [0;14]
       * @return Distance to object. 20 is 15 cm, 50 is 5 cm, 1000 is 1 cm, 3700 is 0.5 cm. [0;8191]
      */
      virtual Real GetProximitySensorReading( const unsigned int n_sensor_index ) = 0;
      virtual const Real *GetAllProximitySensorReadings( void ) = 0;
      virtual unsigned GetProximitySensorAtAngle(int angle) = 0;
      virtual void SetProximityMode(unsigned mode) = 0;
      // virtual void LogSensorValues( ) = 0;

   };

};

#endif

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
 * @file <common/control_interface/sbot/ci_sbot_light_sensor.h>
 *
 * @brief This file provides the definition of the sbot light sensor
 *
 * @author Alvaro Gutierrez - <aguti@etsit.upm.es>
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_SBOTLIGHTSENSOR_H
#define CCI_SBOTLIGHTSENSOR_H

/* To avoid dependency problems when including */
namespace argos {

   class CCI_SBotLightSensor;

};

#include "ci_light_sensor.h"

/**
 * The light sensors are mounted around the turret ring.
 * The number of sensors is 8. They are located at fixed angles: (360/NUMBER_OF_LIGHT_SENSORS)*i for i in [0:NUMBER_OF_LIGHT_SENSORS -1] counterclockwise.
 *
 * The light readings are taken from a sample file, and only the closest light is considered.
 *
 * The values go approx. from 1024 for 0cm to 0 for more than 250 cm, samples taken from real sbots.
 *
 * The sensor is registered as :
 *      REGISTER_SENSOR( CGenericSBotLightSensor, "sbot_light", "generic_sbot_light");
 *
 **/

namespace argos
{

  class CCI_SBotLightSensor: public CCI_LightSensor
  {

      // Associations

      // Attributes

    public:

      static const unsigned int NUMBER_OF_LIGHT_SENSORS;
  };

};

#endif

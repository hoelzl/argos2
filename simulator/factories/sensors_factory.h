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
 * @file <simulator/factories/sensors_factory.h>
 *
 * @brief This file contains the definition of
 *
 * This file contains the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef SENSORS_FACTORY_H
#define SENSORS_FACTORY_H

namespace argos {
   class CSensorsFactory;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <string>
#include <map>

namespace argos {

   class CSensorsFactory {

   public:

      static CCI_Sensor* NewSensor(const std::string& str_actuator_type, const std::string& str_actuator_implementation);

   };

}

#endif

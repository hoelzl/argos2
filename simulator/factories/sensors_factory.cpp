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
 * @file <simulator/factories/sensors_factory.cpp>
 *
 * @brief This file contains the implementation of
 *
 * This file contains the implementation of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "sensors_factory.h"
#include <sensors/simulated_sensor.h>

namespace argos {

   /****************************************/
   /****************************************/

   SSensorPlugin* GetSensorPlugin(void) {
      static std::auto_ptr<SSensorPlugin> psSensorPlugin(new SSensorPlugin());
      return psSensorPlugin.get();
   }

   /****************************************/
   /****************************************/

   CCI_Sensor* CSensorsFactory::NewSensor(const std::string& str_sensor_type,
                                          const std::string& str_sensor_implementation) {
      std::string strKey = str_sensor_type + " (" + str_sensor_implementation + ")";
      if(GetSensorPlugin()->FactoryMap.find(strKey) == GetSensorPlugin()->FactoryMap.end()) {
         THROW_ARGOSEXCEPTION("Sensor type \"" << str_sensor_type << "\", implementation \"" << str_sensor_implementation << "\" not found");
      }
      return GetSensorPlugin()->FactoryMap[strKey]();
   }

   /****************************************/
   /****************************************/

}

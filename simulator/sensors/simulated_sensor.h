/* -*- Mode: C++ -*-
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
 * @file <argos2/simulator/generic_sensors/simulated_sensor.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef SIMULATED_SENSOR_H
#define SIMULATED_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CSimulatedSensor;
   class CEntity;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <string>
#include <map>

namespace argos {

   class CSimulatedSensor {

   public:

      virtual ~CSimulatedSensor() {}

      virtual CEntity& GetEntity() = 0;
      virtual void SetEntity(CEntity& c_entity) = 0;

      virtual void Update() = 0;
      virtual void Reset() = 0;

      virtual void Destroy() {}

   };

}

/* Sensor factory */

namespace argos {

   // typedef to make it easier to set up the sensor factory
   typedef CCI_Sensor *CSensor_Maker();

   struct SSensorPlugin {
      std::map < std::string, CSensor_Maker *, std::less<std::string> > FactoryMap;
      std::map < std::string,     std::string, std::less<std::string> > ShortDescriptionMap;
      std::map < std::string,     std::string, std::less<std::string> > AuthorMap;
      std::map < std::string,     std::string, std::less<std::string> > LongDescriptionMap;
      std::map < std::string,     std::string, std::less<std::string> > StatusMap;
   };

   SSensorPlugin* GetSensorPlugin();

// to add the controller to the factory
#define REGISTER_SENSOR(class_name, sensor_type, sensor_implementation, short_description, author, long_description, status) \
   extern "C" {                                                         \
      CCI_Sensor* class_name ## _maker(){                               \
         return new class_name;                                         \
      }                                                                 \
                                                                        \
      class class_name ## _proxy {                                      \
      public:                                                           \
      class_name ## _proxy(){                                           \
         argos::GetSensorPlugin()->FactoryMap[ sensor_type " (" sensor_implementation ")" ] = class_name ## _maker; \
         argos::GetSensorPlugin()->ShortDescriptionMap[ sensor_type " (" sensor_implementation ")" ] = short_description; \
         argos::GetSensorPlugin()->AuthorMap[ sensor_type " (" sensor_implementation ")" ] = author; \
         argos::GetSensorPlugin()->LongDescriptionMap[ sensor_type " (" sensor_implementation ")" ] = long_description; \
         argos::GetSensorPlugin()->StatusMap[ sensor_type " (" sensor_implementation ")" ] = status; \
      }                                                                 \
      };                                                                \
      class_name ## _proxy class_name ## _p;                            \
   }

}

#endif

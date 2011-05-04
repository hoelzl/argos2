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
 * @file <simulator/physics_engines/simulated_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef SIMULATED_ACTUATOR_H
#define SIMULATED_ACTUATOR_H

namespace argos {
   class CSimulatedActuator;
   class CEntity;
}

#include <argos2/common/control_interface/ci_actuator.h>

#include <string>
#include <map>

namespace argos {

   class CSimulatedActuator : virtual public CCI_Actuator {

   public:

      virtual ~CSimulatedActuator() {}

      virtual CEntity& GetEntity() = 0;
      virtual void SetEntity(CEntity& c_entity) = 0;

      virtual void Update() = 0;
      virtual void Reset() = 0;

   };

}

/* Actuator factory */

namespace argos {

   // typedef to make it easier to set up the actuator factory
   typedef CCI_Actuator *CActuator_Maker();

   struct SActuatorPlugin {
      std::map < std::string, CActuator_Maker *, std::less<std::string> > FactoryMap;
      std::map < std::string,       std::string, std::less<std::string> > ShortDescriptionMap;
      std::map < std::string,       std::string, std::less<std::string> > AuthorMap;
      std::map < std::string,       std::string, std::less<std::string> > LongDescriptionMap;
      std::map < std::string,       std::string, std::less<std::string> > StatusMap;
   };

   SActuatorPlugin* GetActuatorPlugin();

// to add the controller to the factory
#define REGISTER_ACTUATOR(class_name, actuator_type, actuator_implementation, short_description, author, long_description, status) \
   extern "C" {                                                         \
      CCI_Actuator* class_name ## _maker(){                             \
         return new class_name;                                         \
      }                                                                 \
                                                                        \
      class class_name ## _proxy {                                      \
      public:                                                           \
      class_name ## _proxy(){                                           \
         argos::GetActuatorPlugin()->FactoryMap[ actuator_type " (" actuator_implementation ")" ] = class_name ## _maker; \
         argos::GetActuatorPlugin()->ShortDescriptionMap[ actuator_type " (" actuator_implementation ")" ] = short_description; \
         argos::GetActuatorPlugin()->AuthorMap[ actuator_type " (" actuator_implementation ")" ] = author; \
         argos::GetActuatorPlugin()->LongDescriptionMap[ actuator_type " (" actuator_implementation ")" ] = long_description; \
         argos::GetActuatorPlugin()->StatusMap[ actuator_type " (" actuator_implementation ")" ] = status; \
      }                                                                 \
      };                                                                \
      class_name ## _proxy class_name ## _p;                            \
   }

}

#endif

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
 * @file <simulator/factories/actuators_factory.cpp>
 *
 * @brief This file contains the implementation of
 *
 * This file contains the implementation of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "actuators_factory.h"
#include <argos2/common/utility/logging/argos_log.h>
#include <actuators/simulated_actuator.h>

namespace argos {

   /****************************************/
   /****************************************/

   SActuatorPlugin* GetActuatorPlugin() {
      static std::auto_ptr<SActuatorPlugin> psActuatorPlugin(new SActuatorPlugin());
      return psActuatorPlugin.get();
   }

   /****************************************/
   /****************************************/

   CCI_Actuator* CActuatorsFactory::NewActuator(const std::string& str_actuator_type,
                                                const std::string& str_actuator_implementation) {
      std::string strKey = str_actuator_type + " (" + str_actuator_implementation + ")";
      if(GetActuatorPlugin()->FactoryMap.find(strKey) == GetActuatorPlugin()->FactoryMap.end()) {
         THROW_ARGOSEXCEPTION("Actuator type \"" << str_actuator_type << "\", implementation \"" << str_actuator_implementation << "\" not found");
      }
      return GetActuatorPlugin()->FactoryMap[strKey]();
   }

   /****************************************/
   /****************************************/

}

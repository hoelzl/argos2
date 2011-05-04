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
 * @file <simulator/factories/physicsengines_factory.cpp>
 *
 * @brief This file contains the implementation of
 *
 * This file contains the implementation of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "physicsengines_factory.h"

namespace argos {

   /****************************************/
   /****************************************/

   SPhysicsEnginePlugin* GetPhysicsEnginePlugin() {
      static std::auto_ptr<SPhysicsEnginePlugin> psPhysicsEngineMap(new SPhysicsEnginePlugin());
      return psPhysicsEngineMap.get();
   }

   /****************************************/
   /****************************************/

   CPhysicsEngine* CPhysicsEnginesFactory::NewPhysicsEngine(const std::string& str_engine_type) {
      if(GetPhysicsEnginePlugin()->FactoryMap.find(str_engine_type) == GetPhysicsEnginePlugin()->FactoryMap.end()) {
         THROW_ARGOSEXCEPTION("Physics engine \"" << str_engine_type << "\" not found");
      }
      return GetPhysicsEnginePlugin()->FactoryMap[str_engine_type]();
   }

   /****************************************/
   /****************************************/

}

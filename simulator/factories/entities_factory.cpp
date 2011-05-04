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
 * @file <simulator/factories/renderers_factory.cpp>
 *
 * @brief This file contains the implementation of
 *
 * This file contains the implementation of
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#include "entities_factory.h"

namespace argos {

   /****************************************/
   /****************************************/

   SEntityPlugin* GetEntityPlugin() {
      static std::auto_ptr<SEntityPlugin> psEntityMap(new SEntityPlugin());
      return psEntityMap.get();
   }

   /****************************************/
   /****************************************/

   CEntity* CEntitiesFactory::NewEntity(const std::string& str_entity_type) {
      if(GetEntityPlugin()->FactoryMap.find(str_entity_type) == GetEntityPlugin()->FactoryMap.end()) {
         THROW_ARGOSEXCEPTION("Entity type \"" << str_entity_type << "\" not found");
      }
      return GetEntityPlugin()->FactoryMap[str_entity_type]();
   }

   /****************************************/
   /****************************************/

}

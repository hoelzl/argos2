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
 * @file <simulator/factories/renderers_factory.h>
 *
 * @brief This file contains the definition of
 *
 * This file contains the definition of
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef ENTITIES_FACTORY_H
#define ENTITIES_FACTORY_H

#include <string>
#include <map>

namespace argos {
   class CEntitiesFactory;
}

#include <space/entities/entity.h>

namespace argos {

   class CEntitiesFactory {

   public:

      static CEntity* NewEntity(const std::string& str_entity_type);

   };

}

#endif

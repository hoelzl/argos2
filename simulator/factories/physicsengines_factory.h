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
 * @file <simulator/factories/physicsengines_factory.h>
 *
 * @brief This file contains the definition of
 *
 * This file contains the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef PHYSICS_ENGINES_FACTORY_H
#define PHYSICS_ENGINES_FACTORY_H

namespace argos {
   class CPhysicsEnginesFactory;
}

#include <string>
#include <map>
#include <physics_engines/physics_engine.h>

namespace argos {

   class CPhysicsEnginesFactory {

   public:

      static CPhysicsEngine* NewPhysicsEngine(const std::string& str_engine_type);

   };

}

#endif

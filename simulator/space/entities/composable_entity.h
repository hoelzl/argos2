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
 * @file <simulator/space/entities/composable_entity.h>
 *
 * @brief This file contains the definition of an entity.
 *
 * This file contains the class definition of an
 * entity, that is, the basic class that provides the interface for the
 * simulation of all the objects in the environment.
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef COMPOSABLE_ENTITY_H
#define COMPOSABLE_ENTITY_H

namespace argos {
   class CComposableEntity;
}

#include <argos2/simulator/space/entities/entity.h>

namespace argos {
   class CComposableEntity : public CEntity {

   public:

      CComposableEntity(CEntity* pc_parent) :
         CEntity(pc_parent) {}
      virtual ~CComposableEntity() {}

      virtual CEntity& GetComponent(const std::string& str_component) = 0;
      template <class E> E& GetComponent(const std::string& str_component) {
         return *(dynamic_cast<E*>(&GetComponent(str_component)));
      }
      virtual bool HasComponent(const std::string& str_component) = 0;

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "composable_entity";
      }

   };
}

#endif

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
 * @file <argos2/simulator/space/entities/medium_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef MEDIUM_ENTITY_H
#define MEDIUM_ENTITY_H

namespace argos {
   class CMediumEntity;
}

#include <argos2/simulator/space/entities/entity.h>

namespace argos {
   class CMediumEntity : public CEntity {

   public:

      CMediumEntity(CEntity* pc_parent) :
         CEntity(pc_parent) {}
      virtual ~CMediumEntity() {}

      virtual void Update() = 0;

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "medium_entity";
      }

   };

   typedef std::vector<CMediumEntity*> TMediumEntityVector;
}

#endif

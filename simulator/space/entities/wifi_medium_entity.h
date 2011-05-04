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
 * @file <argos2/simulator/space/entities/wifi_medium_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef WIFI_MEDIUM_ENTITY_H
#define WIFI_MEDIUM_ENTITY_H

namespace argos {
   class CWiFiMediumEntity;
}

#include <argos2/simulator/space/entities/medium_entity.h>

namespace argos {
   class CWiFiMediumEntity : public CMediumEntity {

   public:

      CWiFiMediumEntity(CEntity* pc_parent) :
         CMediumEntity(pc_parent) {}
      virtual ~CWiFiMediumEntity() {}

      virtual void Update() {}

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "wifi_medium_entity";
      }

   };
}

#endif

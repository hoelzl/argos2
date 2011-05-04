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
 * @file <argos2/simulator/space/entities/entity.h>
 *
 * @brief This file contains the definition of an entity.
 *
 * This file contains the class definition of an
 * entity, that is, the basic class that provides the interface for the
 * simulation of all the objects in the environment.
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef ENTITY_H
#define ENTITY_H

namespace argos {
   class CEntity;
   class CPhysicsEngine;
   class CSpace;
}

#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/common/utility/configuration/argos_configuration.h>
#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/simulator/visitors/entity_visitor.h>

#include <vector>
#include <map>
#include <string>

namespace argos {

   class CEntity : public CBaseConfigurableResource {

   public:

      CEntity(CEntity* pc_parent) :
         m_pcParent(pc_parent) {}
      virtual ~CEntity() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset() {}
      virtual void Destroy() {}

      inline virtual const std::string& GetId() const {
         return m_strId;
      }

      inline virtual void SetId(const std::string& str_id) {
         m_strId = str_id;
      }

      inline CEntity& GetParent() {
         return *m_pcParent;
      }

      inline void SetParent(CEntity& c_parent) {
         m_pcParent = &c_parent;
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }
      virtual std::string GetTypeDescription() const = 0;

   private:

      std::string m_strId;
      CEntity* m_pcParent;

   };

   typedef std::vector<CEntity*> TEntityVector;
   typedef std::map<std::string, CEntity*> TEntityMap;

}

/* Entity factory */

namespace argos {

   // typedef to make it easier to set up the render factory
   typedef CEntity *CEntity_Maker();

   struct SEntityPlugin {
      std::map < std::string, CEntity_Maker *, std::less<std::string> > FactoryMap;
      std::map < std::string,     std::string, std::less<std::string> > ShortDescriptionMap;
      std::map < std::string,     std::string, std::less<std::string> > AuthorMap;
      std::map < std::string,     std::string, std::less<std::string> > LongDescriptionMap;
      std::map < std::string,     std::string, std::less<std::string> > StatusMap;
   };

   SEntityPlugin* GetEntityPlugin();

// to add the controller to the factory
#define REGISTER_ENTITY(class_name, label, short_description, author, long_description, status) \
   extern "C" {                                                         \
      CEntity* class_name ## _maker(){                                  \
         return new class_name;                                         \
      }                                                                 \
                                                                        \
      class class_name ## _proxy {                                      \
      public:                                                           \
      class_name ## _proxy(){                                           \
         argos::GetEntityPlugin()->FactoryMap[label] = class_name ## _maker; \
         argos::GetEntityPlugin()->ShortDescriptionMap[label] = short_description; \
         argos::GetEntityPlugin()->AuthorMap[label] = author; \
         argos::GetEntityPlugin()->LongDescriptionMap[label] = long_description; \
         argos::GetEntityPlugin()->StatusMap[label] = status; \
      }                                                                 \
      };                                                                \
      class_name ## _proxy class_name ## _p;                            \
   }

}

#endif

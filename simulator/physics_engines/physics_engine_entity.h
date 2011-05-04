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
 * @file <simulator/physics_engines/physics_engine_entity.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef PHYSICS_ENGINE_ENTITY_H
#define PHYSICS_ENGINE_ENTITY_H

namespace argos {
   class CPhysicsEngineEntity;
   class CEmbodiedEntity;
   class CRay;
   class CVector3;
   class CQuaternion;
}

#include <argos2/common/utility/datatypes/datatypes.h>
#include <map>
#include <vector>
#include <string>

namespace argos {

   class CPhysicsEngineEntity {
   protected:

      CEmbodiedEntity* m_pcEmbodiedEntity;

   public:

      CPhysicsEngineEntity(CEmbodiedEntity& c_entity) :
         m_pcEmbodiedEntity(&c_entity) {}
      virtual ~CPhysicsEngineEntity() {}

      inline CEmbodiedEntity& GetEmbodiedEntity() const {
         return *m_pcEmbodiedEntity;
      }

      virtual bool CheckIntersectionWithRay(Real& f_t_on_ray,
                                            const CRay& c_ray) const = 0;

      virtual bool MoveTo(const CVector3& c_position,
                          const CQuaternion& c_orientation,
                          bool b_check_only = false) = 0;

   };

   typedef std::map<std::string, CPhysicsEngineEntity*> TPhysicsEngineEntityMap;
   typedef std::vector<CPhysicsEngineEntity*> TPhysicsEngineEntityVector;

}

#endif

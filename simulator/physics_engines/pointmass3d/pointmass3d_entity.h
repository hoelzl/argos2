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
 * @file <argos2/simulator/physics_engines/pointmass3d_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef POINTMASS3D_ENTITY_H
#define POINTMASS3D_ENTITY_H

namespace argos {
   class CPointMass3DEngine;
   class CPointMass3DEngine;
}

#include <argos2/simulator/physics_engines/physics_engine_entity.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/common/utility/math/quaternion.h>

namespace argos {

   class CPointMass3DEntity : public CPhysicsEngineEntity {

   public:

      CPointMass3DEntity(CPointMass3DEngine& c_engine,
                         CEmbodiedEntity& c_entity) :
         CPhysicsEngineEntity(c_entity),
         m_cEngine(c_engine) {}
      virtual ~CPointMass3DEntity() {}
      
      virtual bool CheckIntersectionWithRay(Real& f_distance,
                                            const CRay& c_ray) const = 0;

      virtual bool MoveTo(const CVector3& c_position,
                          const CQuaternion& c_orientation,
                          bool b_check_only = false) {
         return false;
      }

      virtual void Reset() = 0;

      virtual void UpdateEntityStatus() = 0;
      virtual void UpdateFromEntityStatus() = 0;

   protected:

      CPointMass3DEngine& m_cEngine;
      CVector3 m_cVelocity;
      CVector3 m_cTotalForce;

   };

   typedef std::map<std::string, CPointMass3DEntity*> TPointMass3DEntityMap;

}

#endif

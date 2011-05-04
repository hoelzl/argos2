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
 * @file <argos2/simulator/physics_engines/dynamics3d_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS3D_ENTITY_H
#define DYNAMICS3D_ENTITY_H

namespace argos {
   class CDynamics3DEngine;
   class CDynamics3DEngine;
}

#include <argos2/simulator/physics_engines/physics_engine_entity.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/common/utility/math/quaternion.h>
#include <ode/ode.h>

namespace argos {

   class CDynamics3DEntity : public CPhysicsEngineEntity {

   public:

      CDynamics3DEntity(CDynamics3DEngine& c_engine,
                        CEmbodiedEntity& c_entity);
      virtual ~CDynamics3DEntity() {}
      
      virtual bool CheckIntersectionWithRay(Real& f_t_on_ray,
                                            const CRay& c_ray) const;

      virtual bool MoveTo(const CVector3& c_position,
                          const CQuaternion& c_orientation,
                          bool b_check_only = false);

      virtual void Reset();

      virtual void UpdateEntityStatus();
      virtual void UpdateFromEntityStatus() {}

   protected:

      CDynamics3DEngine& m_cEngine;
      dWorldID           m_tEngineWorld;
      dSpaceID           m_tEngineSpace;
      dBodyID            m_tBody;
      dSpaceID           m_tEntitySpace;
      dMass              m_tMass;

   };

   typedef std::map<std::string, CDynamics3DEntity*> TDynamics3DEntityMap;

}

#endif

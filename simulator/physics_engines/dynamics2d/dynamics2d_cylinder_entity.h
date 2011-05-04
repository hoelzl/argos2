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
 * @file <argos2/simulator/physics_engines/dynamics2d_cylinder_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS2D_CYLINDER_ENTITY_H
#define DYNAMICS2D_CYLINDER_ENTITY_H

#include <argos2/simulator/physics_engines/dynamics2d/dynamics2d_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>

namespace argos {

   class CDynamics2DCylinderEntity : public CDynamics2DEntity {

   public:

      CDynamics2DCylinderEntity(CDynamics2DEngine& c_engine,
                                CCylinderEntity& c_entity);
      virtual ~CDynamics2DCylinderEntity();
      
      virtual bool CheckIntersectionWithRay(Real& f_t_on_ray,
                                            const CRay& c_ray) const;

      virtual void Reset();

      virtual void UpdateEntityStatus();
      virtual void UpdateFromEntityStatus() {}

   private:

      CCylinderEntity& m_cCylinderEntity;
      Real     m_fHalfHeight;
      cpFloat  m_fMass;
      cpShape* m_ptShape;
      cpBody*  m_ptBody;
      cpConstraint* m_ptLinearFriction;
      cpConstraint* m_ptAngularFriction;
      
   };

}

#endif

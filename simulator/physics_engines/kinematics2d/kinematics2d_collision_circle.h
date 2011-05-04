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
 * @file <argos2/simulator/physics_engines/kinematics2d/kinematics2d_collision_circle.h>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef KINEMATICS2D_COLLISIONCIRCLE_H
#define KINEMATICS2D_COLLISIONCIRCLE_H

namespace argos {
  class CKinematics2DEngine;
  class CKinematics2DCollisionCircle;
}

#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_entity.h>

namespace argos {

  class CKinematics2DCollisionCircle : public CKinematics2DEntity {

  public:
      
    CKinematics2DCollisionCircle(CKinematics2DEngine& c_engine, CEmbodiedEntity& c_entity, Real f_radius);
    virtual ~CKinematics2DCollisionCircle() {}
    
    virtual bool CheckIntersectionWithRay(Real& f_distance, const CRay& c_ray) const;

    virtual Real GetRadius() const {return m_fRadius;}
    virtual void SetRadius( const Real& f_radius ) {m_fRadius = f_radius;}

    virtual bool MoveTo(const CVector3& c_position, const CQuaternion& c_orientation, bool b_check_only = false);

  private:
    
    Real m_fRadius;
  };

}

#endif

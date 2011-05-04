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
 * @file <argos2/simulator/physics_engines/kinematics2d/kinematics2d_collision_rectangle.h>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef KINEMATICS2D_COLLISIONRECTANGLE_H
#define KINEMATICS2D_COLLISIONRECTANGLE_H

namespace argos {
  class CKinematics2DEngine;
  class CKinematics2DCollisionRectangle;
}

#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_entity.h>

namespace argos {

  class CKinematics2DCollisionRectangle : public CKinematics2DEntity {

  public:
      
    CKinematics2DCollisionRectangle(CKinematics2DEngine& c_engine, CEmbodiedEntity& c_entity, const CVector3& c_half_size);
    virtual ~CKinematics2DCollisionRectangle() {}
      
    virtual bool CheckIntersectionWithRay(Real& f_distance, const CRay& c_ray) const;

    virtual bool MoveTo(const CVector3& c_position, const CQuaternion& c_orientation, bool b_check_only = false);
    virtual void Reset();

    inline virtual const CVector2& GetVertex( UInt32 i ) const {return m_pcVertices[i];}
    inline virtual void SetVertex( UInt32 i, const CVector2& c_vertex ) {m_pcVertices[i] = c_vertex;}

    inline virtual const CVector2& GetHalfSize() const {return m_cHalfSize;}
    inline virtual void SetHalfSize( const CVector2& c_size ) {m_cHalfSize = c_size;}

  private:
    
    CVector2 m_pcVertices[4];    
    CVector2 m_cHalfSize;
  };

}

#endif

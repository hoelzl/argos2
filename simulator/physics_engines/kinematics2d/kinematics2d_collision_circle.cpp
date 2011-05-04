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
 * @file <argos2/simulator/physics_engines/kinematics2d/kinematics2d_collision_circle.cpp>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "kinematics2d_collision_circle.h"
#include "kinematics2d_collision_rectangle.h"
#include "kinematics2d_engine.h"
#include <argos2/common/utility/math/segment.h>
#include <argos2/common/utility/math/ray.h>

namespace argos {

  /****************************************/
  /****************************************/

  CKinematics2DCollisionCircle::CKinematics2DCollisionCircle(CKinematics2DEngine& c_engine, CEmbodiedEntity& c_entity, Real f_radius) :
    CKinematics2DEntity(c_engine, c_entity),
    m_fRadius(f_radius) {
    m_bEnabled = true;
    m_tCollisionType = KINEMATICS2D_COLLISION_CIRCLE;
  }

  /****************************************/
  /****************************************/

  bool CKinematics2DCollisionCircle::CheckIntersectionWithRay(Real& f_distance, const CRay& c_ray) const {
    CSegment c_segment = c_ray.ProjectOntoXY();
    CVector2 c_closest_point, c_closest_segment_point;
    c_segment.GetMinimumDistancePoints( m_cPosition, c_closest_point, c_closest_segment_point );
    
    Real f_min_segment_distance = Distance(m_cPosition,c_closest_segment_point);
    if( f_min_segment_distance > m_fRadius ) {
      return false;
    }

    // see http://local.wasp.uwa.edu.au/~pbourke/geometry/sphereline/
    CVector2 dp = c_segment.GetEnd() - c_segment.GetStart();
    Real     a  = dp.SquareLength();
    Real     b  = 2 * dp.DotProduct(c_segment.GetStart() - m_cPosition);
    Real     c  = (m_cPosition.SquareLength() +
		   c_segment.GetStart().SquareLength() -
		   2 * m_cPosition.DotProduct(c_segment.GetStart()) -
		   m_fRadius*m_fRadius);
    Real bb4ac  = b*b - 4*a*c;
    Real mu1    = (-b + sqrt(bb4ac)) / (2 * a);
    Real mu2    = (-b - sqrt(bb4ac)) / (2 * a);
    
    Real mu = Min(mu1,mu2);
    if( mu < 0 || mu > 1 ) mu = Max(mu1,mu2);

    f_distance = mu * c_ray.GetLength();    
    return true;
  }
  

  /****************************************/
  /****************************************/

  bool CKinematics2DCollisionCircle::MoveTo(const CVector3& c_position, const CQuaternion& c_orientation, bool b_check_only) {
    CKinematics2DEntity::MoveTo(c_position, c_orientation, b_check_only);
    return !m_cEngine.CollisionsDetection(this);
  }

  /****************************************/
  /****************************************/

}

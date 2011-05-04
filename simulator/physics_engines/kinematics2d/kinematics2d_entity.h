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
 * @file <argos2/simulator/physics_engines/kinematics2d_entity.h>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef KINEMATICS2D_ENTITY_H
#define KINEMATICS2D_ENTITY_H

namespace argos {
  class CKinematics2DEngine;
  class CKinematics2DEngine;
}

#include <argos2/simulator/physics_engines/physics_engine_entity.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/common/utility/math/quaternion.h>

namespace argos {

  enum TKinematics2DCollisionType {
    KINEMATICS2D_COLLISION_NONE,
    KINEMATICS2D_COLLISION_CIRCLE,
    KINEMATICS2D_COLLISION_RECTANGLE,
    KINEMATICS2D_COLLISION_COMPOUND };


  class CKinematics2DEntity : public CPhysicsEngineEntity {

  public:

    /* Constructor and Destructor */
    CKinematics2DEntity(CKinematics2DEngine& c_engine, CEmbodiedEntity& c_entity);
    virtual ~CKinematics2DEntity() {}
      
    /* Function to check intersections with ray (interface) */
    virtual bool CheckIntersectionWithRay(Real& f_distance, const CRay& c_ray) const = 0;

    /* Function to move the entity to a given position */
    virtual bool MoveTo(const CVector3& c_position, const CQuaternion& c_orientation, bool b_check_only = false);
    
    /* Reset the basic elements of the entity (position and orientation) */
    virtual void Reset();
    virtual void UpdateEntityStatus();
    virtual void UpdateFromEntityStatus();

    /* get/set entity 2D position */
    inline const CVector2& GetPosition() const {return m_cPosition;}
    inline void SetPosition( const CVector2& c_position ) {m_cPosition = c_position;}
    
    /* get/set entity orientation */
    inline const CRadians& GetOrientation() const {return m_cOrientation;}
    inline void SetOrientation( const CRadians& c_orientation) {m_cOrientation = c_orientation;}

    /* get/set entity collision flag */
    bool IsEnabled( void ) const {return m_bEnabled;}
    void SetEnabled( const bool b_enabled ) {m_bEnabled = b_enabled;}

    /* get/set entity collision type */
    inline const TKinematics2DCollisionType GetCollisionType() const {return m_tCollisionType;}
    inline void SetCollisionType( const TKinematics2DCollisionType& t_type) {m_tCollisionType = t_type;}

    /* function to revert the entity position and orientation to the
       previous ones after a collision */
    void RevertPositionAndOrientation();

  protected:

    CKinematics2DEngine&       m_cEngine;
    CVector2                   m_cPosition;
    CRadians                   m_cOrientation;

    CVector2                   m_cPreviousPosition;
    CRadians                   m_cPreviousOrientation;

    CVector3                   m_cSpacePosition;
    CQuaternion                m_cSpaceOrientation;
    bool                       m_bEnabled;
    TKinematics2DCollisionType m_tCollisionType;
  };

  typedef std::map<std::string, CKinematics2DEntity*> TKinematics2DEntityMap;

}

#endif

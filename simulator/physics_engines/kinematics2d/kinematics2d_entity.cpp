/*
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
 * @file <argos2/simulator/physics_engines/kinematics2d_engine.cpp>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "kinematics2d_entity.h"
#include "kinematics2d_engine.h"
#include <argos2/simulator/space/entities/embodied_entity.h>

namespace argos {

  /****************************************/
  /****************************************/

  CKinematics2DEntity::CKinematics2DEntity(CKinematics2DEngine& c_engine, CEmbodiedEntity& c_entity) :
    CPhysicsEngineEntity(c_entity),
    m_cEngine(c_engine),
    m_cPosition(),
    m_cOrientation(),
    m_cSpacePosition(),
    m_cSpaceOrientation(),
    m_bEnabled(false),
    m_tCollisionType(KINEMATICS2D_COLLISION_NONE) {

    /* Set the initial body position */
    m_cPosition = GetEmbodiedEntity().GetPosition().ProjectOntoXY();
    
    /* set the initial body orientation */
    CRadians cXAngle, cYAngle;
    GetEmbodiedEntity().GetOrientation().ToEulerAngles(m_cOrientation, cYAngle, cXAngle);
  }

  /****************************************/
  /****************************************/

  bool CKinematics2DEntity::MoveTo(const CVector3& c_position, const CQuaternion& c_orientation, bool b_check_only) {
    m_cPosition = c_position.ProjectOntoXY();
    CRadians cXAngle, cYAngle;
    c_orientation.ToEulerAngles(m_cOrientation, cYAngle, cXAngle);      
    return true;
  }


  /****************************************/
  /****************************************/

  void CKinematics2DEntity::Reset() {
    /* Reset body position */
    m_cPosition = GetEmbodiedEntity().GetInitPosition().ProjectOntoXY();
    
    /* Reset body orientation */
    CRadians cXAngle, cYAngle;
    GetEmbodiedEntity().GetInitOrientation().ToEulerAngles(m_cOrientation, cYAngle, cXAngle);
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEntity::UpdateEntityStatus() {
    /* Update entity position */
    m_cEngine.PositionPhysicsToSpace(m_cSpacePosition, GetEmbodiedEntity().GetPosition(), m_cPosition);
    GetEmbodiedEntity().SetPosition(m_cSpacePosition);
    
    /* Update entity orientation */
    m_cEngine.OrientationPhysicsToSpace(m_cSpaceOrientation, m_cOrientation);
    GetEmbodiedEntity().SetOrientation(m_cSpaceOrientation);
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEntity::UpdateFromEntityStatus() {
    if( m_bEnabled ) {
      m_cPreviousPosition = m_cPosition;
      m_cPreviousOrientation = m_cOrientation;

      GetEmbodiedEntity().ResetCollisionDetected();
    }
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEntity::RevertPositionAndOrientation() {
    if( m_bEnabled ) {
      m_cPosition = m_cPreviousPosition;
      m_cOrientation = m_cPreviousOrientation;
    }
  }

  /****************************************/
  /****************************************/
}

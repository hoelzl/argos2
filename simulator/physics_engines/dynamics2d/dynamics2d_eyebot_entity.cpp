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
 * @file <argos2/simulator/physics_engines/dynamics2d_eyebot_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/space/entities/gripper_equipped_entity.h>
#include "dynamics2d_eyebot_entity.h"
#include "dynamics2d_engine.h"

namespace argos {

   /****************************************/
   /****************************************/

   static const Real EYEBOT_RADIUS         = 0.25f;
   static const Real EYEBOT_BODY_HEIGHT    = 0.015f;
   static const Real EYEBOT_BODY_ELEVATION = 0.151f;
   static const Real EYEBOT_BODY_BOTTOM    = EYEBOT_BODY_ELEVATION;
   static const Real EYEBOT_BODY_TOP       = EYEBOT_BODY_ELEVATION + EYEBOT_BODY_HEIGHT;

   static const Real EYEBOT_MAX_FORCE      = 1.5f;
   static const Real EYEBOT_MAX_TORQUE     = 1.5f;

   /****************************************/
   /****************************************/

   CDynamics2DEyeBotEntity::CDynamics2DEyeBotEntity(CDynamics2DEngine& c_engine,
                                                    CEyeBotEntity& c_entity) :
      CDynamics2DEntity(c_engine, c_entity.GetEmbodiedEntity()),
      m_cEyeBotEntity(c_entity),
      m_fMass(1.6f) {
      /* Create the actual body with initial position and orientation */
      m_ptActualBody =
         cpSpaceAddBody(m_cEngine.GetPhysicsSpace(),
                        cpBodyNew(m_fMass,
                                  cpMomentForCircle(m_fMass,
                                                    0.0f,
                                                    EYEBOT_RADIUS + EYEBOT_RADIUS,
                                                    cpvzero)));
      const CVector3& cPosition = GetEmbodiedEntity().GetPosition();
      m_ptActualBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOrientation().ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(m_ptActualBody, cZAngle.GetValue());
      /* Create the control body with initial position and orientation */
      m_ptControlBody = cpBodyNew(INFINITY, INFINITY);
      /* Create the actual body geometry */
      m_ptShape =
         cpSpaceAddShape(m_cEngine.GetPhysicsSpace(),
                         cpCircleShapeNew(m_ptActualBody,
                                          EYEBOT_RADIUS,
                                          cpvzero));
      /* No elasticity */
      m_ptShape->e = 0.0;
      /* Lots of friction */
      m_ptShape->u = 0.7;
      /* Constrain the actual  body to follow the control  body */
      m_ptControlLinearMotion =
         cpSpaceAddConstraint(m_cEngine.GetPhysicsSpace(),
                              cpPivotJointNew2(m_ptActualBody,
                                               m_ptControlBody,
                                               cpvzero,
                                               cpvzero));
      m_ptControlLinearMotion->biasCoef = 0.0f; /* disable joint correction */
      m_ptControlLinearMotion->maxForce = EYEBOT_MAX_FORCE; /* limit the dragging force */
      m_ptControlAngularMotion = cpSpaceAddConstraint(m_cEngine.GetPhysicsSpace(),
                                               cpGearJointNew(m_ptActualBody,
                                                              m_ptControlBody,
                                                              0.0f,
                                                              1.0f));
      m_ptControlAngularMotion->biasCoef = 0.0f; /* disable joint correction */
      m_ptControlAngularMotion->maxForce = EYEBOT_MAX_TORQUE; /* limit the dragging torque */
   }

   /****************************************/
   /****************************************/

   CDynamics2DEyeBotEntity::~CDynamics2DEyeBotEntity() {
      cpSpaceRemoveConstraint(m_cEngine.GetPhysicsSpace(), m_ptControlLinearMotion);
      cpSpaceRemoveConstraint(m_cEngine.GetPhysicsSpace(), m_ptControlAngularMotion);
      cpSpaceRemoveBody(m_cEngine.GetPhysicsSpace(), m_ptActualBody);
      cpSpaceRemoveShape(m_cEngine.GetPhysicsSpace(), m_ptShape);
      cpConstraintFree(m_ptControlLinearMotion);
      cpConstraintFree(m_ptControlAngularMotion);
      cpBodyFree(m_ptActualBody);
      cpBodyFree(m_ptControlBody);
      cpShapeFree(m_ptShape);
   }

   /****************************************/
   /****************************************/

   bool CDynamics2DEyeBotEntity::CheckIntersectionWithRay(Real& f_t_on_ray,
                                                           const CRay& c_ray) const {
      cpSegmentQueryInfo tInfo;
      if(cpShapeSegmentQuery(m_ptShape,
                             cpv(c_ray.GetStart().GetX(), c_ray.GetStart().GetY()),
                             cpv(c_ray.GetEnd().GetX()  , c_ray.GetEnd().GetY()  ),
                             &tInfo)) {
      	 CVector3 cIntersectionPoint;
      	 c_ray.GetPoint(cIntersectionPoint, tInfo.t);
      	 if((cIntersectionPoint.GetZ() >= GetEmbodiedEntity().GetPosition().GetZ() + EYEBOT_BODY_BOTTOM) &&
      			(cIntersectionPoint.GetZ() <= GetEmbodiedEntity().GetPosition().GetZ() + EYEBOT_BODY_TOP) ) {
            f_t_on_ray = tInfo.t;
            return true;
      	 }
      	 else {
            return false;
      	 }
      }
      else {
         return false;
      }
   }

   /****************************************/
   /****************************************/

   bool CDynamics2DEyeBotEntity::MoveTo(const CVector3& c_position,
                                        const CQuaternion& c_orientation,
                                        bool b_check_only) {
      /* Save body position and orientation */
      cpVect tOldPos = m_ptActualBody->p;
      cpFloat fOldA = m_ptActualBody->a;
      /* Move the body to the desired position */
      m_ptActualBody->p = cpv(c_position.GetX(), c_position.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      c_orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(m_ptActualBody, cZAngle.GetValue());
      /* Create a shape sensor to test the movement */
      cpShape* ptSensorShape = cpCircleShapeNew(m_ptActualBody,
                                                EYEBOT_RADIUS,
                                                cpvzero);
      ptSensorShape->sensor = 1;
      /* Check if there is a collision */
      int nCollision = checkCollision(m_cEngine.GetPhysicsSpace(), ptSensorShape);
      /* Restore old body state if there was a collision or
         it was only a check for movement */
      if(b_check_only || nCollision) {
         m_ptActualBody->p = tOldPos;
         cpBodySetAngle(m_ptActualBody, fOldA);
      }
      /* Dispose of the sensor shape */
      cpShapeFree(ptSensorShape);
      /* The movement is allowed if there is no collision */
      return !nCollision;
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEyeBotEntity::Reset() {
      /* Reset body position */
      const CVector3& cPosition = GetEmbodiedEntity().GetInitPosition();
      m_ptActualBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      /* Reset body orientation */
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetInitOrientation().ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(m_ptActualBody, cZAngle.GetValue());
      /* Zero speed and applied forces of actual body */
      m_ptActualBody->v = cpvzero;
      m_ptActualBody->w = 0.0f;
      cpBodyResetForces(m_ptActualBody);
      /* Zero speed and applied forces of control body */
      m_ptControlBody->v = cpvzero;
      m_ptControlBody->w = 0.0f;
      cpBodyResetForces(m_ptControlBody);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEyeBotEntity::UpdateEntityStatus() {
      /* Update eye-bot body position */
      m_cEngine.PositionPhysicsToSpace(m_cSpacePosition, GetEmbodiedEntity().GetPosition(), m_ptActualBody);
      if(m_cEyeBotEntity.IsAttachedToCeiling()) {
         m_cSpacePosition.SetZ(m_fArenaHeight);
      }
      GetEmbodiedEntity().SetPosition(m_cSpacePosition);
      /* Update eye-bot body orientation */
      m_cEngine.OrientationPhysicsToSpace(m_cSpaceOrientation, m_ptActualBody);
      GetEmbodiedEntity().SetOrientation(m_cSpaceOrientation);
      /* Update eye-bot components */
      m_cEyeBotEntity.UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEyeBotEntity::UpdateFromEntityStatus() {
      /* Zero applied forces and speeds */
      cpBodyResetForces(m_ptControlBody);
      /* Update physics state */
      if(m_cEyeBotEntity.IsDetachedFromCeiling()) {
         /* Update layer information */
         m_ptShape->layers = CDynamics2DEngine::LAYER_NORMAL;
         /* Get speeds or forces from entity */
         if(m_cEyeBotEntity.GetMotionData().Source == CEyeBotEntity::SMotionData::MOTION_FROM_FORCES) {
            /* Apply wanted forces */
            // TODO
         }
         else {
            /* Apply wanted speeds */
            m_ptControlBody->v = cpvrotate(m_ptActualBody->rot,
                                           cpv(m_cEyeBotEntity.GetMotionData().LinearSpeed,
                                               0.0f));
            m_ptControlBody->w = m_cEyeBotEntity.GetMotionData().AngularSpeed;
         }
      }
      else {
         /* Update layer information */
         m_ptShape->layers = CDynamics2DEngine::LAYER_FROZEN;
      }
   }

   /****************************************/
   /****************************************/

}


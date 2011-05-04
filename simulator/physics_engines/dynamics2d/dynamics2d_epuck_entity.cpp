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
 * @file <argos2/simulator/physics_engines/dynamics2d_epuck_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include <argos2/simulator/space/entities/embodied_entity.h>
#include "dynamics2d_epuck_entity.h"
#include "dynamics2d_engine.h"

namespace argos {

   /****************************************/
   /****************************************/

   static const Real EPUCK_RADIUS              = 0.035f;
   static const Real EPUCK_INTERWHEEL_DISTANCE = 0.053f;
   static const Real EPUCK_HEIGHT              = 0.086f; // to be checked!

   static const Real EPUCK_MAX_FORCE           = 1.5f;
   static const Real EPUCK_MAX_TORQUE          = 1.5f;

   enum EPUCK_WHEELS {
      EPUCK_LEFT_WHEEL = 0,
      EPUCK_RIGHT_WHEEL = 1
   };

   /****************************************/
   /****************************************/

   CDynamics2DEPuckEntity::CDynamics2DEPuckEntity(CDynamics2DEngine& c_engine,
                                                  CEPuckEntity& c_entity) :
      CDynamics2DEntity(c_engine, c_entity.GetEmbodiedEntity()),
      m_cEPuckEntity(c_entity),
      m_cWheeledEntity(m_cEPuckEntity.GetWheeledEntity()),
      m_fMass(0.4f) {
      /* Create the actual body with initial position and orientation */
      m_ptActualBaseBody =
         cpSpaceAddBody(m_cEngine.GetPhysicsSpace(),
                        cpBodyNew(m_fMass,
                                  cpMomentForCircle(m_fMass,
                                                    0.0f,
                                                    EPUCK_RADIUS + EPUCK_RADIUS,
                                                    cpvzero)));
      const CVector3& cPosition = GetEmbodiedEntity().GetPosition();
      m_ptActualBaseBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOrientation().ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(m_ptActualBaseBody, cZAngle.GetValue());
      /* Create the control body with initial position and orientation */
      m_ptControlBaseBody = cpBodyNew(INFINITY, INFINITY);
      /* Create the actual body geometry */
      m_ptBaseShape =
         cpSpaceAddShape(m_cEngine.GetPhysicsSpace(),
                         cpCircleShapeNew(m_ptActualBaseBody,
                                          EPUCK_RADIUS,
                                          cpvzero));
      /* No elasticity */
      m_ptBaseShape->e = 0.0;
      /* Lots of friction */
      m_ptBaseShape->u = 0.7;
      /* Constrain the actual base body to follow the control base body */
      m_ptBaseControlLinearMotion =
         cpSpaceAddConstraint(m_cEngine.GetPhysicsSpace(),
                              cpPivotJointNew2(m_ptActualBaseBody,
                                               m_ptControlBaseBody,
                                               cpvzero,
                                               cpvzero));
      m_ptBaseControlLinearMotion->biasCoef = 0.0f; /* disable joint correction */
      m_ptBaseControlLinearMotion->maxForce = EPUCK_MAX_FORCE; /* limit the dragging force */
      m_ptBaseControlAngularMotion = cpSpaceAddConstraint(m_cEngine.GetPhysicsSpace(),
                                                          cpGearJointNew(m_ptActualBaseBody,
                                                                         m_ptControlBaseBody,
                                                                         0.0f,
                                                                         1.0f));
      m_ptBaseControlAngularMotion->biasCoef = 0.0f; /* disable joint correction */
      m_ptBaseControlAngularMotion->maxForce = EPUCK_MAX_TORQUE; /* limit the dragging torque */
      /* Zero the wheel velocity */
      m_fCurrentWheelVelocityFromSensor[EPUCK_LEFT_WHEEL] = 0.0f;
      m_fCurrentWheelVelocityFromSensor[EPUCK_RIGHT_WHEEL] = 0.0f;
   }

   /****************************************/
   /****************************************/

   CDynamics2DEPuckEntity::~CDynamics2DEPuckEntity() {
      cpSpaceRemoveConstraint(m_cEngine.GetPhysicsSpace(), m_ptBaseControlLinearMotion);
      cpSpaceRemoveConstraint(m_cEngine.GetPhysicsSpace(), m_ptBaseControlAngularMotion);
      cpSpaceRemoveBody(m_cEngine.GetPhysicsSpace(), m_ptActualBaseBody);
      cpSpaceRemoveShape(m_cEngine.GetPhysicsSpace(), m_ptBaseShape);
      cpConstraintFree(m_ptBaseControlLinearMotion);
      cpConstraintFree(m_ptBaseControlAngularMotion);
      cpBodyFree(m_ptActualBaseBody);
      cpBodyFree(m_ptControlBaseBody);
      cpShapeFree(m_ptBaseShape);
   }

   /****************************************/
   /****************************************/

   bool CDynamics2DEPuckEntity::CheckIntersectionWithRay(Real& f_t_on_ray,
                                                         const CRay& c_ray) const {
      cpSegmentQueryInfo tInfo;
      if(cpShapeSegmentQuery(m_ptBaseShape,
                             cpv(c_ray.GetStart().GetX(), c_ray.GetStart().GetY()),
                             cpv(c_ray.GetEnd().GetX()  , c_ray.GetEnd().GetY()  ),
                             &tInfo)) {
      	 CVector3 cIntersectionPoint;
      	 c_ray.GetPoint(cIntersectionPoint, tInfo.t);
      	 if((cIntersectionPoint.GetZ() >= GetEmbodiedEntity().GetPosition().GetZ()                 ) &&
      			(cIntersectionPoint.GetZ() <= GetEmbodiedEntity().GetPosition().GetZ() + EPUCK_HEIGHT) ) {
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

   bool CDynamics2DEPuckEntity::MoveTo(const CVector3& c_position,
                                       const CQuaternion& c_orientation,
                                       bool b_check_only) {
      /* Save body position and orientation */
      cpVect tOldPos = m_ptActualBaseBody->p;
      cpFloat fOldA = m_ptActualBaseBody->a;
      /* Move the body to the desired position */
      m_ptActualBaseBody->p = cpv(c_position.GetX(), c_position.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      c_orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(m_ptActualBaseBody, cZAngle.GetValue());
      /* Create a shape sensor to test the movement */
      cpShape* ptSensorShape = cpCircleShapeNew(m_ptActualBaseBody,
                                                EPUCK_RADIUS,
                                                cpvzero);
      ptSensorShape->sensor = 1;
      /* Check if there is a collision */
      int nCollision = checkCollision(m_cEngine.GetPhysicsSpace(), ptSensorShape);
      /* Restore old body state if there was a collision or
         it was only a check for movement */
      if(b_check_only || nCollision) {
         m_ptActualBaseBody->p = tOldPos;
         cpBodySetAngle(m_ptActualBaseBody, fOldA);
      }
      /* Dispose of the sensor shape */
      cpShapeFree(ptSensorShape);
      /* The movement is allowed if there is no collision */
      return !nCollision;
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEPuckEntity::Reset() {
      /* Reset body position */
      const CVector3& cPosition = GetEmbodiedEntity().GetInitPosition();
      m_ptActualBaseBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      /* Reset body orientation */
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetInitOrientation().ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(m_ptActualBaseBody, cZAngle.GetValue());
      /* Zero speed and applied forces of actual body */
      m_ptActualBaseBody->v = cpvzero;
      m_ptActualBaseBody->w = 0.0f;
      cpBodyResetForces(m_ptActualBaseBody);
      /* Zero speed and applied forces of control body */
      m_ptControlBaseBody->v = cpvzero;
      m_ptControlBaseBody->w = 0.0f;
      cpBodyResetForces(m_ptControlBaseBody);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEPuckEntity::UpdateEntityStatus() {
      /* Update e-puck body position */
      m_cEngine.PositionPhysicsToSpace(m_cSpacePosition, GetEmbodiedEntity().GetPosition(), m_ptActualBaseBody);
      GetEmbodiedEntity().SetPosition(m_cSpacePosition);
      /* Update e-puck body orientation */
      m_cEngine.OrientationPhysicsToSpace(m_cSpaceOrientation, m_ptActualBaseBody);
      GetEmbodiedEntity().SetOrientation(m_cSpaceOrientation);
      /* Update e-puck components */
      m_cEPuckEntity.UpdateComponents();
      /* Check whether a transfer is necessary */
      if(m_cEngine.IsEntityTransferActive()) {
         std::string strEngineId;
         if(m_cEngine.CalculateTransfer(GetEmbodiedEntity().GetPosition().GetX(),
                                        GetEmbodiedEntity().GetPosition().GetY(),
                                        strEngineId)) {
            m_cEngine.ScheduleEntityForTransfer(m_cEPuckEntity, strEngineId);
         }
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEPuckEntity::UpdateFromEntityStatus() {
      /* Get wheel speeds from entity */
      m_cWheeledEntity.GetSpeed(m_fCurrentWheelVelocityFromSensor);
      /* Do we want to move? */
      if((m_fCurrentWheelVelocityFromSensor[EPUCK_LEFT_WHEEL] != 0.0f) ||
         (m_fCurrentWheelVelocityFromSensor[EPUCK_RIGHT_WHEEL] != 0.0f)) {
         /* Yeah, we do */
         /*
          * THE DIFFERENTIAL STEERING SYSTEM
          *
          * check http://rossum.sourceforge.net/papers/DiffSteer/
          * for details
          *
          * Equations:
          *
          * w = (Vr - Vl) / b
          * v = [ ((Vr + Vl) / 2) cos(a),
          *       ((Vr + Vl) / 2) sin(a) ]
          *
          * where:
          *        a  = body orientation
          *        w  = body angular velocity
          *        v  = body center linear velocity
          *        Vr = right wheel velocity
          *        Vl = left wheel velocity
          *        b  = length of wheel axis
          */
         m_ptControlBaseBody->w =
            (m_fCurrentWheelVelocityFromSensor[EPUCK_RIGHT_WHEEL] -
             m_fCurrentWheelVelocityFromSensor[EPUCK_LEFT_WHEEL]) / 
            EPUCK_INTERWHEEL_DISTANCE;
         m_ptControlBaseBody->v =
            cpvrotate(m_ptActualBaseBody->rot,
                      cpv((m_fCurrentWheelVelocityFromSensor[EPUCK_LEFT_WHEEL] +
                           m_fCurrentWheelVelocityFromSensor[EPUCK_RIGHT_WHEEL]) *
                          0.5f,
                          0.0f));
      }
      else {
         /* No, we don't want to move - zero all speeds */
         m_ptControlBaseBody->w = 0.0f;
         m_ptControlBaseBody->v = cpvzero;
      }
   }

   /****************************************/
   /****************************************/

}


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
 * @file <argos2/simulator/physics_engines/dynamics2d_cylinder_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include <argos2/simulator/space/entities/embodied_entity.h>
#include "dynamics2d_cylinder_entity.h"
#include "dynamics2d_engine.h"

namespace argos {

   /****************************************/
   /****************************************/

   CDynamics2DCylinderEntity::CDynamics2DCylinderEntity(CDynamics2DEngine& c_engine,
                                                        CCylinderEntity& c_entity) :
      CDynamics2DEntity(c_engine, c_entity.GetEmbodiedEntity()),
      m_cCylinderEntity(c_entity),
      m_fMass(c_entity.GetMass()),
      m_ptShape(NULL),
      m_ptBody(NULL) {
      /* Get the radius of the entity */
      Real fRadius = c_entity.GetRadius();
      m_fHalfHeight = c_entity.GetHeight() * 0.5f;
      /* Create a circle object in the physics space */
      const CVector3& cPosition = GetEmbodiedEntity().GetPosition();
      if(c_entity.IsMovable()) {
         /* The cylinder is movable */
         /* Create the body */
         m_ptBody = cpSpaceAddBody(m_cEngine.GetPhysicsSpace(),
                                   cpBodyNew(m_fMass,
                                             cpMomentForCircle(m_fMass,
                                                               0,
                                                               fRadius + fRadius,
                                                               cpvzero)));
         m_ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
         CRadians cXAngle, cYAngle, cZAngle;
         GetEmbodiedEntity().GetOrientation().ToEulerAngles(cZAngle, cYAngle, cXAngle);
         cpBodySetAngle(m_ptBody, cZAngle.GetValue());
         /* Create the geometry */
         m_ptShape = cpSpaceAddShape(m_cEngine.GetPhysicsSpace(),
                                     cpCircleShapeNew(m_ptBody, fRadius, cpvzero));
         /* This object is grippable */
         m_ptShape->collision_type = CDynamics2DEngine::SHAPE_GRIPPABLE;
         m_ptShape->data = reinterpret_cast<void*>(&c_entity);
         /* No elasticity */
         m_ptShape->e = 0.0;
         /* Lots surface contact friction to help pushing */
         m_ptShape->u = 0.7;
         /* Friction with ground */
         m_ptLinearFriction =
            cpSpaceAddConstraint(m_cEngine.GetPhysicsSpace(),
                                 cpPivotJointNew2(m_cEngine.GetGroundBody(),
                                                  m_ptBody,
                                                  cpvzero,
                                                  cpvzero));
         m_ptLinearFriction->biasCoef = 0.0f; // disable joint correction
         m_ptLinearFriction->maxForce = 1.0f; // emulate linear friction
         m_ptAngularFriction =
            cpSpaceAddConstraint(m_cEngine.GetPhysicsSpace(),
                                 cpGearJointNew(m_cEngine.GetGroundBody(),
                                                m_ptBody,
                                                0.0f,
                                                1.0f));
         m_ptAngularFriction->biasCoef = 0.0f; // disable joint correction
         m_ptAngularFriction->maxForce = 5.0f; // emulate angular friction
      }
      else {
         /* The cylinder is not movable */
         /* Create the geometry */
         m_ptShape = cpSpaceAddStaticShape(m_cEngine.GetPhysicsSpace(),
                                           cpCircleShapeNew(m_cEngine.GetGroundBody(),
                                                            fRadius,
                                                            cpv(cPosition.GetX(), cPosition.GetY())));
         /* This object is normal */
         m_ptShape->collision_type = CDynamics2DEngine::SHAPE_NORMAL;
         m_ptShape->data = reinterpret_cast<void*>(&c_entity);
         /* No elasticity */
         m_ptShape->e = 0.0;
         /* Little contact friction to help sliding away */
         m_ptShape->u = 0.1;
      }
   }

   /****************************************/
   /****************************************/

   CDynamics2DCylinderEntity::~CDynamics2DCylinderEntity() {
      if(m_ptBody != NULL) {
         cpSpaceRemoveConstraint(m_cEngine.GetPhysicsSpace(), m_ptLinearFriction);
         cpSpaceRemoveConstraint(m_cEngine.GetPhysicsSpace(), m_ptAngularFriction);
         cpConstraintFree(m_ptLinearFriction);
         cpConstraintFree(m_ptAngularFriction);
         cpSpaceRemoveBody(m_cEngine.GetPhysicsSpace(), m_ptBody);
         cpBodyFree(m_ptBody);
         cpSpaceRemoveShape(m_cEngine.GetPhysicsSpace(), m_ptShape);
      }
      else {
         cpSpaceRemoveStaticShape(m_cEngine.GetPhysicsSpace(), m_ptShape);
         cpSpaceRehashStatic(m_cEngine.GetPhysicsSpace());
      }
      cpShapeFree(m_ptShape);
   }

   /****************************************/
   /****************************************/

   bool CDynamics2DCylinderEntity::CheckIntersectionWithRay(Real& f_t_on_ray,
                                                            const CRay& c_ray) const {
      cpSegmentQueryInfo tInfo;
      if(cpShapeSegmentQuery(m_ptShape,
                             cpv(c_ray.GetStart().GetX(), c_ray.GetStart().GetY()),
                             cpv(c_ray.GetEnd().GetX()  , c_ray.GetEnd().GetY()  ),
                             &tInfo)) {
      	 CVector3 cIntersectionPoint;
      	 c_ray.GetPoint(cIntersectionPoint, tInfo.t);
      	 if((cIntersectionPoint.GetZ() >= GetEmbodiedEntity().GetPosition().GetZ() - m_fHalfHeight) &&
      			(cIntersectionPoint.GetZ() <= GetEmbodiedEntity().GetPosition().GetZ() + m_fHalfHeight) ) {
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

   void CDynamics2DCylinderEntity::Reset() {
      if(m_ptBody != NULL) {
         /* Reset body position */
         const CVector3& cPosition = GetEmbodiedEntity().GetInitPosition();
         m_ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
         /* Reset body orientation */
         CRadians cXAngle, cYAngle, cZAngle;
         GetEmbodiedEntity().GetInitOrientation().ToEulerAngles(cZAngle, cYAngle, cXAngle);
         cpBodySetAngle(m_ptBody, cZAngle.GetValue());
         /* Zero speed and applied forces */
         m_ptBody->v = cpvzero;
         m_ptBody->w = 0.0f;
         cpBodyResetForces(m_ptBody);
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics2DCylinderEntity::UpdateEntityStatus() {
      if(m_ptBody != NULL) {
         m_cEngine.PositionPhysicsToSpace(m_cSpacePosition, GetEmbodiedEntity().GetPosition(), m_ptBody);
         GetEmbodiedEntity().SetPosition(m_cSpacePosition);
         m_cEngine.OrientationPhysicsToSpace(m_cSpaceOrientation, m_ptBody);
         GetEmbodiedEntity().SetOrientation(m_cSpaceOrientation);
      }

      /* Update components */
      m_cCylinderEntity.UpdateComponents();

   }

   /****************************************/
   /****************************************/

}

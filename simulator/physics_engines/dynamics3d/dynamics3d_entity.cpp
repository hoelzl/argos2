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
 * @file <argos2/simulator/physics_engines/dynamics3d_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics3d_entity.h"
#include "dynamics3d_engine.h"
#include <argos2/simulator/space/entities/embodied_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CDynamics3DEntity::CDynamics3DEntity(CDynamics3DEngine& c_engine,
                                        CEmbodiedEntity& c_entity) :
      CPhysicsEngineEntity(c_entity),
      m_cEngine(c_engine),
      m_tEngineWorld(c_engine.GetWorldID()),
      m_tEngineSpace(c_engine.GetSpaceID()),
      m_tBody(dBodyCreate(m_tEngineWorld)),
      m_tEntitySpace(dSimpleSpaceCreate(m_tEngineSpace)) {
      /* Zero the body mass */
      dMassSetZero(&m_tMass);
      /*
       * Set the level of the body space
       * Necessary for dSpaceCollide2 to work properly
       */
      dSpaceSetSublevel(m_tEngineSpace, 1);
   }

   /****************************************/
   /****************************************/

   bool CDynamics3DEntity::MoveTo(const CVector3& c_position,
                                  const CQuaternion& c_orientation,
                                  bool b_check_only) {
      /* Move the body to the new position */
      dBodySetPosition(m_tBody, c_position.GetX(), c_position.GetY(), c_position.GetZ());
      /* Rotate the body to the new orientation */
      dQuaternion tQuat = { c_orientation.GetW(),
                            c_orientation.GetX(),
                            c_orientation.GetY(),
                            c_orientation.GetZ() };
      dBodySetQuaternion(m_tBody, tQuat);
      /* Check for collisions */
      bool bCollisions = m_cEngine.IsEntityColliding(m_tEntitySpace);
      if(bCollisions || b_check_only) {
         /*
          * Undo the changes if there is a collision or
          * if the move was just a check
          */
         const CVector3& cPosition = GetEmbodiedEntity().GetPosition();
         dBodySetPosition(m_tBody, cPosition.GetX(), cPosition.GetY(), cPosition.GetZ());
         const CQuaternion& cOrientation = GetEmbodiedEntity().GetOrientation();
         dQuaternion tQuat2 = { cOrientation.GetW(),
                                cOrientation.GetX(),
                                cOrientation.GetY(),
                                cOrientation.GetZ() };
         dBodySetQuaternion(m_tBody, tQuat2);
         return !bCollisions;
      }
      else {
         /* Set the new position and orientation */
         GetEmbodiedEntity().SetPosition(c_position);
         GetEmbodiedEntity().SetOrientation(c_orientation);
         return true;
      }
   }

   /****************************************/
   /****************************************/
   
   bool CDynamics3DEntity::CheckIntersectionWithRay(Real& f_t_on_ray,
                                                    const CRay& c_ray) const {
      /* Create an ODE ray from ARGoS ray */
      Real fRayLength = c_ray.GetLength();
      dGeomID tRay = dCreateRay(m_cEngine.GetSpaceID(), fRayLength);
      CVector3 cDirection;
      c_ray.GetDirection(cDirection);
      dGeomRaySet(tRay,
                  c_ray.GetStart().GetX(),
                  c_ray.GetStart().GetY(),
                  c_ray.GetStart().GetZ(),
                  cDirection.GetX(),
                  cDirection.GetY(),
                  cDirection.GetZ());
      /* Create the structure to contain info about the possible
         ray/geom intersection */
      dContactGeom tIntersection;
      /* Check for intersection between the ray and the object local space */
      if(dCollide(tRay, reinterpret_cast<dGeomID>(m_tEntitySpace), 1, &tIntersection, sizeof(dContactGeom)) > 0) {
         /* There is an intersecton */
         f_t_on_ray = tIntersection.depth / fRayLength;
         return true;
      }
      else {
         /* No intersection detected */
         return false;
      }
   }
   
   /****************************************/
   /****************************************/

   void CDynamics3DEntity::Reset() {
      /* Clear force and torque on the body */
      dBodySetForce(m_tBody, 0.0f, 0.0f, 0.0f);
      dBodySetTorque(m_tBody, 0.0f, 0.0f, 0.0f);
      /* Clear speeds */
      dBodySetLinearVel(m_tBody, 0.0f, 0.0f, 0.0f);
      dBodySetAngularVel(m_tBody, 0.0f, 0.0f, 0.0f);
      /* Reset position */
      const CVector3& cPosition = GetEmbodiedEntity().GetInitPosition();
      dBodySetPosition(m_tBody,
                       cPosition.GetX(),
                       cPosition.GetY(),
                       cPosition.GetZ());
      /* Reset orientation */
      const CQuaternion& cQuaternion = GetEmbodiedEntity().GetInitOrientation();
      dQuaternion tQuat = {
         cQuaternion.GetW(),
         cQuaternion.GetX(),
         cQuaternion.GetY(),
         cQuaternion.GetZ()
      };
      dBodySetQuaternion(m_tBody, tQuat);
   }

   /****************************************/
   /****************************************/
   
   void CDynamics3DEntity::UpdateEntityStatus() {
      /* Update entity position and orientation */
      const dReal* ptPosition = dBodyGetPosition(m_tBody);
      GetEmbodiedEntity().SetPosition(
         CVector3(ptPosition[0],
                  ptPosition[1],
                  ptPosition[2]));
      const dReal* ptOrientation = dBodyGetQuaternion(m_tBody);
      GetEmbodiedEntity().SetOrientation(
         CQuaternion(ptOrientation[0],
                     ptOrientation[1],
                     ptOrientation[2],
                     ptOrientation[3]));
   }

   /****************************************/
   /****************************************/

}

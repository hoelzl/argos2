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
 * @file <argos2/simulator/physics_engines/dynamics3d_box.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics3d_box.h"
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/physics_engines/dynamics3d/dynamics3d_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   CDynamics3DBox::CDynamics3DBox(CDynamics3DEngine& c_engine,
                                  CBoxEntity& c_box) :
      CDynamics3DEntity(c_engine, c_box.GetEmbodiedEntity()),
      m_cBoxEntity(c_box) {
      /* Check whether the box is movable or not */
      if(c_box.IsMovable()) {
         /* Movable box */
         /* Set the body to its initial position and orientation */
         const CQuaternion& cOrient = GetEmbodiedEntity().GetOrientation();
         dQuaternion tQuat = { cOrient.GetW(), cOrient.GetX(), cOrient.GetY(), cOrient.GetZ() };
         dBodySetQuaternion(m_tBody, tQuat);
         const CVector3& cPos = GetEmbodiedEntity().GetPosition();
         dBodySetPosition(m_tBody, cPos.GetX(), cPos.GetY(), cPos.GetZ());
         /* Create the geometry and the mass */
         const CVector3& cBoxSize = c_box.GetSize();
         m_tGeom = dCreateBox(m_tEntitySpace, cBoxSize.GetX(), cBoxSize.GetY(), cBoxSize.GetZ());
         /* Create its mass */
         dMassSetBoxTotal(&m_tMass, c_box.GetMass(), cBoxSize.GetX(), cBoxSize.GetY(), cBoxSize.GetZ());
         /* Associate the body to the geom */
         dGeomSetBody(m_tGeom, m_tBody);
         /* Set the parent body total mass */
         dBodySetMass(m_tBody, &m_tMass);
      }
      else {
         /* Unmovable box, get rid of the body and add only the geometry */
         dBodyDestroy(m_tBody);
         /* Create the geometry */
         const CVector3& cBoxSize = c_box.GetSize();
         m_tGeom = dCreateBox(m_tEntitySpace, cBoxSize.GetX(), cBoxSize.GetY(), cBoxSize.GetZ());
         /* Set the geom to its position and orientation */
         const CQuaternion& cOrient = GetEmbodiedEntity().GetOrientation();
         dQuaternion tQuat = { cOrient.GetW(), cOrient.GetX(), cOrient.GetY(), cOrient.GetZ() };
         dGeomSetQuaternion(m_tGeom, tQuat);
         const CVector3& cPos = GetEmbodiedEntity().GetPosition();
         dGeomSetPosition(m_tGeom, cPos.GetX(), cPos.GetY(), cPos.GetZ());
         /* Associate the geom to null body (this makes it static) */
         dGeomSetBody(m_tGeom, 0);
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics3DBox::Reset() {
      if(m_cBoxEntity.IsMovable()) {      
         /* Reset box position and orientation */
         CDynamics3DEntity::Reset();
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics3DBox::UpdateEntityStatus() {
      if(m_cBoxEntity.IsMovable()) {      
         /* Update box position and orientation */
         CDynamics3DEntity::UpdateEntityStatus();
         /* Update components */
         m_cBoxEntity.UpdateComponents();
      }
   }

   /****************************************/
   /****************************************/

}

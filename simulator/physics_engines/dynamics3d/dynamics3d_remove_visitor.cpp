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
 * @file <argos2/simulator/physics_engines/dynamics3d/dynamics3d_remove_visitor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics3d_remove_visitor.h"
#include "dynamics3d_box.h"
#include "dynamics3d_cylinder.h"
#include "dynamics3d_eyebot.h"
#include "dynamics3d_engine.h"

namespace argos {

   /****************************************/
   /****************************************/

   void CDynamics3DRemoveVisitor::Visit(CBoxEntity& c_entity) {
      m_cEngine.RemovePhysicsEntity(c_entity.GetId());
   }

   /****************************************/
   /****************************************/

   void CDynamics3DRemoveVisitor::Visit(CCylinderEntity& c_entity) {
      m_cEngine.RemovePhysicsEntity(c_entity.GetId());
   }

   /****************************************/
   /****************************************/

   void CDynamics3DRemoveVisitor::Visit(CEyeBotEntity& c_entity) {
      m_cEngine.RemovePhysicsEntity(c_entity.GetId());
      m_cEngine.RemoveControllableEntity(c_entity.GetId());
   }

   /****************************************/
   /****************************************/

}

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
 * @file <argos2/simulator/physics_engines/dynamics3d/dynamics3d_add_visitor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics3d_add_visitor.h"
#include "dynamics3d_box.h"
#include "dynamics3d_cylinder.h"
#include "dynamics3d_eyebot.h"
#include "dynamics3d_engine.h"
#include <argos2/simulator/space/entities/embodied_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   void CDynamics3DAddVisitor::Visit(CBoxEntity& c_entity) {
      CDynamics3DBox* pcEntity = new CDynamics3DBox(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

   void CDynamics3DAddVisitor::Visit(CCylinderEntity& c_entity) {
      CDynamics3DCylinder* pcEntity = new CDynamics3DCylinder(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

   void CDynamics3DAddVisitor::Visit(CEyeBotEntity& c_entity) {
      CDynamics3DEyeBot* pcEntity = new CDynamics3DEyeBot(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      m_cEngine.AddControllableEntity(c_entity.GetControllableEntity());
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

}

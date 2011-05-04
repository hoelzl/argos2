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
 * @file <argos2/simulator/physics_engines/dynamics2d/dynamics2d_add_visitor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics2d_add_visitor.h"
#include "dynamics2d_box_entity.h"
#include "dynamics2d_cylinder_entity.h"
#include "dynamics2d_footbot_entity.h"
#include "dynamics2d_eyebot_entity.h"
#include "dynamics2d_epuck_entity.h"
#include "dynamics2d_engine.h"

namespace argos {

   /****************************************/
   /****************************************/

   static bool BBIntersectsPlane(const CDynamics2DEngine& c_engine,
                                 const CEmbodiedEntity::SBoundingBox& c_bb) {
      return
         c_bb.MinCorner.GetZ() <= c_engine.GetElevation() &&
         c_engine.GetElevation() <= c_bb.MaxCorner.GetZ();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DAddVisitor::Visit(CBoxEntity& c_entity) {
      if(! BBIntersectsPlane(m_cEngine, c_entity.GetEmbodiedEntity().GetBoundingBox())) {
         THROW_ARGOSEXCEPTION("Entity \"" << c_entity.GetId() << "\" does not intersect the plane of physics engine \"" << m_cEngine.GetId() << "\"");
      }
      CDynamics2DBoxEntity* pcEntity = new CDynamics2DBoxEntity(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DAddVisitor::Visit(CCylinderEntity& c_entity) {
      if(! BBIntersectsPlane(m_cEngine, c_entity.GetEmbodiedEntity().GetBoundingBox())) {
         THROW_ARGOSEXCEPTION("Entity \"" << c_entity.GetId() << "\" does not intersect the plane of physics engine \"" << m_cEngine.GetId() << "\"");
      }
      CDynamics2DCylinderEntity* pcEntity = new CDynamics2DCylinderEntity(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DAddVisitor::Visit(CFootBotEntity& c_entity) {
      if(! BBIntersectsPlane(m_cEngine, c_entity.GetEmbodiedEntity().GetBoundingBox())) {
         THROW_ARGOSEXCEPTION("Entity \"" << c_entity.GetId() << "\" does not intersect the plane of physics engine \"" << m_cEngine.GetId() << "\"");
      }
      CDynamics2DFootBotEntity* pcEntity = new CDynamics2DFootBotEntity(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      m_cEngine.AddControllableEntity(c_entity.GetControllableEntity());
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DAddVisitor::Visit(CEyeBotEntity& c_entity) {
      if(! BBIntersectsPlane(m_cEngine, c_entity.GetEmbodiedEntity().GetBoundingBox())) {
         THROW_ARGOSEXCEPTION("Entity \"" << c_entity.GetId() << "\" does not intersect the plane of physics engine \"" << m_cEngine.GetId() << "\"");
      }
      CDynamics2DEyeBotEntity* pcEntity = new CDynamics2DEyeBotEntity(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      m_cEngine.AddControllableEntity(c_entity.GetControllableEntity());
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DAddVisitor::Visit(CEPuckEntity& c_entity) {
      if(! BBIntersectsPlane(m_cEngine, c_entity.GetEmbodiedEntity().GetBoundingBox())) {
         THROW_ARGOSEXCEPTION("Entity \"" << c_entity.GetId() << "\" does not intersect the plane of physics engine \"" << m_cEngine.GetId() << "\"");
      }
      CDynamics2DEPuckEntity* pcEntity = new CDynamics2DEPuckEntity(m_cEngine, c_entity);
      m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
      m_cEngine.AddControllableEntity(c_entity.GetControllableEntity());
      c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
      c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
   }

   /****************************************/
   /****************************************/

}

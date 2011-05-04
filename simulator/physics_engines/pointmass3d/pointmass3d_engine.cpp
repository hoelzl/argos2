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
 * @file <argos2/simulator/physics_engines/pointmass3d_engine.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "pointmass3d_engine.h"

namespace argos {

   /****************************************/
   /****************************************/

   CPointMass3DEngine::CPointMass3DEngine() :
      m_cAddVisitor(*this),
      m_cRemoveVisitor(*this) {
   }

   /****************************************/
   /****************************************/

   CPointMass3DEngine::~CPointMass3DEngine() {
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::Init(TConfigurationNode& t_tree) {
      /* Init parent */
      CPhysicsEngine::Init(t_tree);
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::Reset() {
      for(TPointMass3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->Reset();
      }
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::Destroy() {
      /* Empty the physics entity map */
      for(TPointMass3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         delete it->second;
      }
      m_tPhysicsEntities.clear();
   }
      
   /****************************************/
   /****************************************/

   void CPointMass3DEngine::Update() {
      /* Update the physics state from the entities */
      for(TPointMass3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->UpdateFromEntityStatus();
      }
      /* Perform the step */
      /* Update the simulated space */
      for(TPointMass3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->UpdateEntityStatus();
      }
   }
   
   /****************************************/
   /****************************************/

   UInt32 CPointMass3DEngine::GetNumPhysicsEngineEntities() {
      return m_tPhysicsEntities.size();
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::AddEntity(CEntity& c_entity) {
      c_entity.Accept(m_cAddVisitor);
   }
   
   /****************************************/
   /****************************************/

   void CPointMass3DEngine::RemoveEntity(CEntity& c_entity) {
      c_entity.Accept(m_cRemoveVisitor);
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::AddPhysicsEntity(const std::string& str_id,
                                             CPointMass3DEntity& c_entity) {
      m_tPhysicsEntities[str_id] = &c_entity;
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::AddControllableEntity(CControllableEntity& c_entity) {
      m_tControllableEntities[c_entity.GetId()] = &c_entity;
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::RemovePhysicsEntity(const std::string& str_id) {
      TPointMass3DEntityMap::iterator it = m_tPhysicsEntities.find(str_id);
      if(it != m_tPhysicsEntities.end()) {
         delete it->second;
         m_tPhysicsEntities.erase(it);
      }
      else {
         THROW_ARGOSEXCEPTION("PointMass3D entity id \"" << str_id << "\" not found in dynamics 2D engine \"" << GetId() << "\"");
      }
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEngine::RemoveControllableEntity(const std::string& str_id) {
      TControllableEntityMap::iterator it = m_tControllableEntities.find(str_id);
      if(it != m_tControllableEntities.end()) {
         m_tControllableEntities.erase(it);
      }
      else {
         THROW_ARGOSEXCEPTION("Controllable entity id \"" << str_id << "\" not found in dynamics 2D engine \"" << GetId() << "\"");
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_PHYSICS_ENGINE(CPointMass3DEngine,
                           "pointmass3d",
                           "A 3D physics engine in which entities are point masses",
                           "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                           "TODO",
                           "Under development"
      );
}

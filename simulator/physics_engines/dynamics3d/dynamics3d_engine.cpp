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
 * @file <argos2/simulator/physics_engines/dynamics3d_engine.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics3d_engine.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <cstring>

namespace argos {

   /****************************************/
   /****************************************/

   void ManageCloseGeomsAddingContactJointsCallback(void* pt_data, dGeomID t_geom1, dGeomID t_geom2) {
      CDynamics3DEngine::SGeomCheckData* psGeomCheckData = reinterpret_cast<CDynamics3DEngine::SGeomCheckData*>(pt_data);
      psGeomCheckData->Engine.ManageCloseGeomsAddingContactJoints(psGeomCheckData, t_geom1, t_geom2);
   }

   void ManageCloseGeomsCheckContactsOnlyCallback(void* pt_data, dGeomID t_geom1, dGeomID t_geom2) {
      CDynamics3DEngine::SGeomCheckData* psGeomCheckData = reinterpret_cast<CDynamics3DEngine::SGeomCheckData*>(pt_data);
      if(! psGeomCheckData->AreContactsPresent) {
         psGeomCheckData->Engine.ManageCloseGeomsCheckContactsOnly(psGeomCheckData, t_geom1, t_geom2);
      }
   }

   /****************************************/
   /****************************************/

   CDynamics3DEngine::CDynamics3DEngine() :
      m_pcRNG(NULL),
      m_cAddVisitor(*this),
      m_cRemoveVisitor(*this),
      m_fArenaHeight(CSimulator::GetInstance().GetSpace().GetArenaSize().GetZ()) {
   }

   /****************************************/
   /****************************************/

   CDynamics3DEngine::~CDynamics3DEngine() {
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::Init(TConfigurationNode& t_tree) {
      /* Init parent */
      CPhysicsEngine::Init(t_tree);
      /* Parse the XML */
      GetNodeAttributeOrDefault(t_tree, "gravity", m_cGravity, CVector3(0.0f, 0.0f, -9.81f));
      GetNodeAttributeOrDefault<Real>(t_tree, "erp", m_fERP, 0.8);
      GetNodeAttributeOrDefault<Real>(t_tree, "cfm", m_fCFM, 0.01);
      GetNodeAttributeOrDefault<UInt32>(t_tree, "iterations", m_unIterations, 20);
      GetNodeAttributeOrDefault<size_t>(t_tree, "max_contacts", m_unMaxContacts, 32);
      /* Init ODE stuff */
      m_tWorldID = dWorldCreate();
      m_tSpaceID = dHashSpaceCreate(0);
      dSpaceSetSublevel(m_tSpaceID, 0);
      m_tContactJointGroupID = dJointGroupCreate(0);
      dWorldSetGravity(m_tWorldID, 0.0f, 0.0f, -9.81f);
      dWorldSetERP(m_tWorldID, m_fERP);
      dWorldSetCFM(m_tWorldID, m_fCFM);
      dWorldSetQuickStepNumIterations(m_tWorldID, m_unIterations);
      dInitODE();
      /* Initialize contact information */
      m_ptContacts = new dContact[m_unMaxContacts];
      for(UInt32 i  = 0; i < m_unMaxContacts; ++i) {
         ::memset(&(m_ptContacts[i].surface), 0, sizeof(dSurfaceParameters));
         m_ptContacts[i].surface.mode = dContactMu2;
         m_ptContacts[i].surface.mu = dInfinity;
         m_ptContacts[i].surface.mu2 = dInfinity;
      }
      /* Add a planar floor */
      m_tFloor = dCreatePlane(m_tSpaceID, 0, 0, 1.0f, 0.0f);
      /* Set the random seed from a random number taken from ARGoS RNG */
      m_pcRNG = CARGoSRandom::CreateRNG("argos");
      dRandSetSeed(m_pcRNG->Uniform(CRange<UInt32>(1,65535)));
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::Reset() {
      /*
       * Reset the random seed
       * Since m_pcRNG has already been reset by CSimulator::Reset(), here it is safe to just ask
       * the ARGoS RNG to give the first number. It's the same as the one chosen in
       * CDynamics3DEngine::Init(), if the user set the global random seed in the XML; otherwise,
       * it's a different one.
       */
      dRandSetSeed(m_pcRNG->Uniform(CRange<UInt32>(1,65535)));
      /* Reset the physics entities */
      for(TDynamics3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->Reset();
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::Destroy() {
      /* Empty the physics entity map */
      for(TDynamics3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         delete it->second;
      }
      m_tPhysicsEntities.clear();
      /* Cleanup ODE stuff */
      delete[] m_ptContacts;
      dJointGroupDestroy(m_tContactJointGroupID);
      dWorldDestroy(m_tWorldID);
      dCloseODE();
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::Update() {
      /* Update the physics state from the entities */
      for(TDynamics3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->UpdateFromEntityStatus();
      }
      /* Remove contact joints to be ready to calculate new ones */
      dJointGroupEmpty(m_tContactJointGroupID);
      /* Check collisions inside the space */
      SGeomCheckData sGeomCheckData(*this);
      dSpaceCollide(m_tSpaceID, &sGeomCheckData, &ManageCloseGeomsAddingContactJointsCallback);
      /* Perform the physics step */
      dWorldStep(m_tWorldID, m_fSimulationClockTick);
      /* Update the simulated space */
      for(TDynamics3DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->UpdateEntityStatus();
      }
   }

   /****************************************/
   /****************************************/

   UInt32 CDynamics3DEngine::GetNumPhysicsEngineEntities() {
      return m_tPhysicsEntities.size();
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::AddEntity(CEntity& c_entity) {
      c_entity.Accept(m_cAddVisitor);
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::RemoveEntity(CEntity& c_entity) {
      c_entity.Accept(m_cRemoveVisitor);
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::AddPhysicsEntity(const std::string& str_id,
                                             CDynamics3DEntity& c_entity) {
      m_tPhysicsEntities[str_id] = &c_entity;
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::AddControllableEntity(CControllableEntity& c_entity) {
      m_tControllableEntities[c_entity.GetId()] = &c_entity;
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::RemovePhysicsEntity(const std::string& str_id) {
      TDynamics3DEntityMap::iterator it = m_tPhysicsEntities.find(str_id);
      if(it != m_tPhysicsEntities.end()) {
         delete it->second;
         m_tPhysicsEntities.erase(it);
      }
      else {
         THROW_ARGOSEXCEPTION("Dynamics3D entity id \"" << str_id << "\" not found in dynamics 3D engine \"" << GetId() << "\"");
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::RemoveControllableEntity(const std::string& str_id) {
      TControllableEntityMap::iterator it = m_tControllableEntities.find(str_id);
      if(it != m_tControllableEntities.end()) {
         m_tControllableEntities.erase(it);
      }
      else {
         THROW_ARGOSEXCEPTION("Controllable entity id \"" << str_id << "\" not found in dynamics 3D engine \"" << GetId() << "\"");
      }
   }

   /****************************************/
   /****************************************/

   bool CDynamics3DEngine::IsEntityColliding(dSpaceID t_entity) {
      /* Remove contact joints to be ready to calculate new ones */
      dJointGroupEmpty(m_tContactJointGroupID);
      /* Check collisions inside the space */
      SGeomCheckData sGeomCheckData(*this);
      dSpaceCollide2(reinterpret_cast<dGeomID>(m_tSpaceID),
                     reinterpret_cast<dGeomID>(t_entity),
                     &sGeomCheckData,
                     &ManageCloseGeomsCheckContactsOnlyCallback);
      return sGeomCheckData.AreContactsPresent;
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::ManageCloseGeomsAddingContactJoints(SGeomCheckData* ps_data, dGeomID t_geom1, dGeomID t_geom2) {
      /*
       * The passed geometries can be spaces or shapes.
       * Depending on the type of each passed geometry, we do something different
       */
      if(dGeomIsSpace(t_geom1) || dGeomIsSpace(t_geom2)) {
         /*
          * At least one of the two geometries is a space.
          * We need to open up the spaces to get to the basic elements.
          */
         dSpaceCollide2(t_geom1, t_geom2, ps_data, &ManageCloseGeomsAddingContactJointsCallback);
      }
      else {
         /* Both geoms are shapes. Let's check for collisions among them */
         size_t unContacts = dCollide(t_geom1, t_geom2, m_unMaxContacts, &m_ptContacts->geom, sizeof(dContact));
         /* If no collision is detected, we're done */
         if(unContacts == 0) return;
         /* Otherwise, let's add contact joints in each contact point detected */
         /* Get the body ids */
         dBodyID tBody1 = dGeomGetBody(t_geom1);
         dBodyID tBody2 = dGeomGetBody(t_geom2);
         /* Create a buffer for the contact joints */
         dJointID tContactJoint;
         /* Go through the contact points and create the joints */
         for(UInt32 i = 0; i < unContacts; ++i) {
            tContactJoint = dJointCreateContact(m_tWorldID, m_tContactJointGroupID, m_ptContacts+i);
            dJointAttach(tContactJoint, tBody1, tBody2);
         }
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEngine::ManageCloseGeomsCheckContactsOnly(SGeomCheckData* ps_data, dGeomID t_geom1, dGeomID t_geom2) {
      /*
       * The passed geometries can be spaces or shapes.
       * Depending on the type of each passed geometry, we do something different
       */
      if(dGeomIsSpace(t_geom1) || dGeomIsSpace(t_geom2)) {
         /*
          * At least one of the two geometries is a space.
          * We need to open up the spaces to get to the basic elements.
          */
         dSpaceCollide2(t_geom1, t_geom2, ps_data, &ManageCloseGeomsCheckContactsOnlyCallback);
      }
      else {
         /* Both geoms are shapes. Let's check for collisions among them */
         size_t unContacts = dCollide(t_geom1, t_geom2, m_unMaxContacts, &m_ptContacts->geom, sizeof(dContact));
         /* Update the contact presence flag */
         ps_data->AreContactsPresent = (unContacts == 0);
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_PHYSICS_ENGINE(CDynamics3DEngine,
                           "dynamics3d",
                           "A 3D physics engine based on ODE.",
                           "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                           "TODO",
                           "Under development"
      );
}

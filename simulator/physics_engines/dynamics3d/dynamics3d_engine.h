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
 * @file <argos2/simulator/physics_engines/dynamics3d_engine.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS3D_ENGINE_H
#define DYNAMICS3D_ENGINE_H

namespace argos {
   class CDynamics3DEngine;
   class CDynamics3DEntity;
}

#include <argos2/simulator/physics_engines/physics_engine.h>
#include <argos2/simulator/physics_engines/dynamics3d/dynamics3d_entity.h>
#include <argos2/simulator/physics_engines/dynamics3d/dynamics3d_add_visitor.h>
#include <argos2/simulator/physics_engines/dynamics3d/dynamics3d_remove_visitor.h>
#include <argos2/simulator/space/entities/controllable_entity.h>
#include <argos2/common/utility/argos_random.h>
#include <ode/ode.h>

namespace argos {

   class CDynamics3DEngine : public CPhysicsEngine {

   public:

      CDynamics3DEngine();
      virtual ~CDynamics3DEngine();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual void Update();

      virtual UInt32 GetNumPhysicsEngineEntities();
      virtual void AddEntity(CEntity& c_entity);
      virtual void RemoveEntity(CEntity& c_entity);

      bool IsEntityColliding(dSpaceID t_entity);

      inline dWorldID GetWorldID() const { return m_tWorldID; }
      inline dSpaceID GetSpaceID() const { return m_tSpaceID; }
      inline const CVector3& GetGravity() const { return m_cGravity; }

   private:

      void AddPhysicsEntity(const std::string& str_id,
                            CDynamics3DEntity& c_entity);
      void AddControllableEntity(CControllableEntity& c_entity);
      void RemovePhysicsEntity(const std::string& str_id);
      void RemoveControllableEntity(const std::string& str_id);

      struct SGeomCheckData {
         bool AreContactsPresent;
         CDynamics3DEngine& Engine;

         SGeomCheckData(CDynamics3DEngine& c_engine) :
            AreContactsPresent(false),
            Engine(c_engine) {}
      };

      void ManageCloseGeomsAddingContactJoints(SGeomCheckData* ps_data, dGeomID t_geom1, dGeomID t_geom2);
      void ManageCloseGeomsCheckContactsOnly(SGeomCheckData* ps_data, dGeomID t_geom1, dGeomID t_geom2);


      friend void ManageCloseGeomsAddingContactJointsCallback(void* pt_data, dGeomID t_geom1, dGeomID t_geom2);
      friend void ManageCloseGeomsCheckContactsOnlyCallback(void* pt_data, dGeomID t_geom1, dGeomID t_geom2);

   private:

      CARGoSRandom::CRNG* m_pcRNG;
      CDynamics3DAddVisitor m_cAddVisitor;
      CDynamics3DRemoveVisitor m_cRemoveVisitor;
      TControllableEntityMap m_tControllableEntities;
      TDynamics3DEntityMap m_tPhysicsEntities;
      friend class CDynamics3DAddVisitor;
      friend class CDynamics3DRemoveVisitor;

      Real m_fArenaHeight;

      dWorldID m_tWorldID;
      dSpaceID m_tSpaceID;
      dJointGroupID m_tContactJointGroupID;
      dGeomID m_tFloor;

      CVector3 m_cGravity;
      Real m_fERP;
      Real m_fCFM;
      UInt32 m_unIterations;
      size_t m_unMaxContacts;
      dContact* m_ptContacts;

   };

}

#endif

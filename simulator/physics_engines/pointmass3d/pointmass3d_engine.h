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
 * @file <argos2/simulator/physics_engines/pointmass3d_engine.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef POINTMASS3D_ENGINE_H
#define POINTMASS3D_ENGINE_H

namespace argos {
   class CPointMass3DEngine;
   class CPointMass3DEntity;
}

#include <argos2/simulator/physics_engines/physics_engine.h>
#include <argos2/simulator/physics_engines/pointmass3d/pointmass3d_entity.h>
#include <argos2/simulator/physics_engines/pointmass3d/pointmass3d_add_visitor.h>
#include <argos2/simulator/physics_engines/pointmass3d/pointmass3d_remove_visitor.h>
#include <argos2/simulator/space/entities/controllable_entity.h>

namespace argos {

   class CPointMass3DEngine : public CPhysicsEngine {

   public:

      CPointMass3DEngine();
      virtual ~CPointMass3DEngine();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual void Update();

      virtual UInt32 GetNumPhysicsEngineEntities();
      virtual void AddEntity(CEntity& c_entity);
      virtual void RemoveEntity(CEntity& c_entity);

   private:

      void AddPhysicsEntity(const std::string& str_id,
                            CPointMass3DEntity& c_entity);
      void AddControllableEntity(CControllableEntity& c_entity);
      void RemovePhysicsEntity(const std::string& str_id);
      void RemoveControllableEntity(const std::string& str_id);

   private:

      CPointMass3DAddVisitor m_cAddVisitor;
      CPointMass3DRemoveVisitor m_cRemoveVisitor;
      TControllableEntityMap m_tControllableEntities;
      TPointMass3DEntityMap m_tPhysicsEntities;
      friend class CPointMass3DAddVisitor;
      friend class CPointMass3DRemoveVisitor;

   };

}

#endif

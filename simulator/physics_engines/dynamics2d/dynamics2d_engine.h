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
 * @file <argos2/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS2D_ENGINE_H
#define DYNAMICS2D_ENGINE_H

namespace argos {
   class CDynamics2DEngine;
   class CGripperEquippedEntity;
}

#include <argos2/simulator/space/entities/controllable_entity.h>
#include <argos2/simulator/physics_engines/physics_engine.h>
#include <argos2/simulator/physics_engines/dynamics2d/dynamics2d_entity.h>
#include <argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/include/chipmunk.h>
#include <argos2/simulator/physics_engines/dynamics2d/dynamics2d_add_visitor.h>
#include <argos2/simulator/physics_engines/dynamics2d/dynamics2d_remove_visitor.h>

namespace argos {

   struct SDynamics2DEngineGripperData {
      cpSpace* Space;
      CGripperEquippedEntity& GripperEntity;
      cpVect GripperAnchor;
      cpConstraint* GripConstraint;

      SDynamics2DEngineGripperData(cpSpace* pt_space,
                                   CGripperEquippedEntity& c_entity,
                                   cpVect t_anchor);
      ~SDynamics2DEngineGripperData();
      void ClearConstraints();
   };

   class CDynamics2DEngine : public CPhysicsEngine {

   public:

      enum EShapeType {
         SHAPE_NORMAL = 0,
         SHAPE_GRIPPABLE,
         SHAPE_CLAW_GRIPPER,
         SHAPE_MAGNETIC_GRIPPER
      };

      enum ELayerType {
         LAYER_FROZEN = 0,
         LAYER_NORMAL = CP_ALL_LAYERS
      };

      struct SBoundarySegment {
         CSegment Segment;
         enum {
            SEGMENT_TYPE_WALL,
            SEGMENT_TYPE_GATE
         } Type;
         std::string EngineId;

         SBoundarySegment() : 
            Type(SEGMENT_TYPE_WALL) {}
      };

      struct SEntityTransferData {
         std::string EngineId;
         CEntity* Entity;

         SEntityTransferData() :
            Entity(NULL) {}
      };

      CDynamics2DEngine();
      virtual ~CDynamics2DEngine() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Update();
      virtual void Destroy();
      virtual UInt32 GetNumPhysicsEngineEntities();
      virtual void AddEntity(CEntity& c_entity);
      virtual void RemoveEntity(CEntity& c_entity);

      inline virtual bool IsEntityTransferNeeded() const {
         return ! m_vecTransferData.empty();
      }
      virtual void TransferEntities();

      inline virtual bool IsEntityTransferActive() const {
         return m_bEntityTransferActive;
      }
      bool CalculateTransfer(Real f_x, Real f_y,
                             std::string& str_engine_id);
      inline void ScheduleEntityForTransfer(CEntity& c_entity,
                                            const std::string& str_engine_id) {
         m_vecTransferData.push_back(SEntityTransferData());
         m_vecTransferData.back().EngineId = str_engine_id;
         m_vecTransferData.back().Entity = &c_entity;
      }

      inline cpSpace* GetPhysicsSpace() {
         return m_ptSpace;
      }

      inline cpBody* GetGroundBody() {
         return m_ptGroundBody;
      }

      inline Real GetElevation() const {
         return m_fElevation;
      }

      inline void PositionPhysicsToSpace(CVector3& c_new_pos,
                                         const CVector3& c_original_pos,
                                         const cpBody* pt_body) {
         c_new_pos.SetX(pt_body->p.x);
         c_new_pos.SetY(pt_body->p.y);
         c_new_pos.SetZ(c_original_pos.GetZ());
      }

      inline void OrientationPhysicsToSpace(CQuaternion& c_new_orient,
                                            cpBody* pt_body) {
         c_new_orient.FromAngleAxis(CRadians(pt_body->a), CVector3::Z);
      }

   private:

      void AddPhysicsEntity(const std::string& str_id,
                            CDynamics2DEntity& c_entity);
      void AddControllableEntity(CControllableEntity& c_entity);
      void RemovePhysicsEntity(const std::string& str_id);
      void RemoveControllableEntity(const std::string& str_id);

   private:

      CDynamics2DAddVisitor m_cAddVisitor;
      CDynamics2DRemoveVisitor m_cRemoveVisitor;

      SInt32 m_nIterations;
      cpFloat m_fStaticHashCellSize;
      cpFloat m_fActiveHashCellSize;
      SInt32 m_nStaticHashCells;
      SInt32 m_nActiveHashCells;
      cpSpace* m_ptSpace;
      cpBody* m_ptGroundBody;
      Real m_fElevation;

      std::vector<CVector2> m_vecVertices;
      std::vector<SBoundarySegment> m_vecSegments;
      std::vector<SEntityTransferData> m_vecTransferData;
      bool m_bEntityTransferActive;

      TControllableEntityMap m_tControllableEntities;
      TDynamics2DEntityMap m_tPhysicsEntities;

      friend class CDynamics2DAddVisitor;
      friend class CDynamics2DRemoveVisitor;

   };

}

#endif

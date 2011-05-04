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
 * @file <argos2/simulator/physics_engines/dynamics2d/dynamics2d_engine.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics2d_engine.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/space/entities/controllable_entity.h>
#include <argos2/simulator/space/entities/gripper_equipped_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   SDynamics2DEngineGripperData::SDynamics2DEngineGripperData(cpSpace* pt_space,
                                                              CGripperEquippedEntity& c_entity,
                                                              cpVect t_anchor) :
      Space(pt_space),
      GripperEntity(c_entity),
      GripperAnchor(t_anchor),
      GripConstraint(NULL) {}

   SDynamics2DEngineGripperData::~SDynamics2DEngineGripperData() {
      ClearConstraints();
   }

   void SDynamics2DEngineGripperData::ClearConstraints() {
      if(GripConstraint != NULL) {
         cpSpaceRemoveConstraint(Space, GripConstraint);
         cpConstraintFree(GripConstraint);
         GripConstraint = NULL;
         GripperEntity.ClearGrippedEntity();
      }
   }

   /****************************************/
   /****************************************/

   int MagneticGripperGrippableCollisionBegin(cpArbiter* pt_arb, cpSpace* pt_space, void* p_data) {
      /* Get the shapes involved */
      CP_ARBITER_GET_SHAPES(pt_arb, ptGripperShape, ptGrippableShape);
      /* Get a reference to the gripper data */
      SDynamics2DEngineGripperData& sGripperData = *reinterpret_cast<SDynamics2DEngineGripperData*>(ptGripperShape->data);
      /* Get a reference to the gripped entity */
      CEmbodiedEntity& cGrippedEntity = *reinterpret_cast<CEmbodiedEntity*>(ptGrippableShape->data);
      /* If the entities match, ignore the collision forever */
      return (sGripperData.GripperEntity.GetId() != cGrippedEntity.GetId());
   }

   int MagneticGripperGrippableCollisionPreSolve(cpArbiter* pt_arb, cpSpace* pt_space, void* p_data) {
      /* Get the shapes involved */
      CP_ARBITER_GET_SHAPES(pt_arb, ptGripperShape, ptGrippableShape);
      /* Get a reference to the gripper data */
      SDynamics2DEngineGripperData& sGripperData = *reinterpret_cast<SDynamics2DEngineGripperData*>(ptGripperShape->data);
      /* The gripper is locked or unlocked? */
      if(sGripperData.GripperEntity.IsUnlocked()) {
         /* The gripper is locked. If it was gripping an object,
          * release it. Then, process the collision normally */
      	 if(sGripperData.GripperEntity.IsGripping()) {
            sGripperData.ClearConstraints();
      	 }
         return 1;
      }
      else if(! sGripperData.GripperEntity.IsGripping()) {
         /* The gripper is unlocked and free, create the joints */
         /* Prevent gripper from slipping */
         pt_arb->e = 0.0f; // No elasticity
         pt_arb->u = 1.0f; // Max friction
         pt_arb->surface_vr = cpvzero; // No surface velocity
         /* Calculate the anchor point on the grippable body
            as the centroid of the contact points */
         cpVect tGrippableAnchor = cpvzero;
         for(SInt32 i = 0; i < pt_arb->numContacts; ++i) {
            tGrippableAnchor = cpvadd(tGrippableAnchor, cpArbiterGetPoint(pt_arb, i));
         }
         tGrippableAnchor = cpvmult(tGrippableAnchor, 1.0f / pt_arb->numContacts);
         /* Create a constraint */
         sGripperData.GripConstraint = cpSpaceAddConstraint(pt_space,
                                                            cpPivotJointNew(
                                                               ptGripperShape->body,
                                                               ptGrippableShape->body,
                                                               tGrippableAnchor));
         sGripperData.GripConstraint->biasCoef = 0.95f; // Correct overlap
         sGripperData.GripConstraint->maxBias  = 0.01f; // Max correction speed
         sGripperData.GripperEntity.SetGrippedEntity(*reinterpret_cast<CEmbodiedEntity*>(ptGrippableShape->data));
      }
      /* Ignore the collision, the objects are gripped already */
      return 0;
   }

   /****************************************/
   /****************************************/

   CDynamics2DEngine::CDynamics2DEngine() :
      m_cAddVisitor(*this),
      m_cRemoveVisitor(*this),
      m_nIterations(10),
      m_fStaticHashCellSize(0.1f),
      m_fActiveHashCellSize(2.0f * 0.085036758f),
      m_nStaticHashCells(1000),
      m_nActiveHashCells(1000),
      m_ptSpace(NULL),
      m_ptGroundBody(NULL),
      m_fElevation(0.0f),
      m_bEntityTransferActive(false) {
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::Init(TConfigurationNode& t_tree) {
      /* Init parent */
      CPhysicsEngine::Init(t_tree);
      /* Parse XML */
      GetNodeAttributeOrDefault(t_tree, "iterations",       m_nIterations,         m_nIterations);
      GetNodeAttributeOrDefault(t_tree, "static_cell_size", m_fStaticHashCellSize, m_fStaticHashCellSize);
      GetNodeAttributeOrDefault(t_tree, "active_cell_size", m_fActiveHashCellSize, m_fActiveHashCellSize);
      GetNodeAttributeOrDefault(t_tree, "static_cells",     m_nStaticHashCells,    m_nStaticHashCells);
      GetNodeAttributeOrDefault(t_tree, "active_cells",     m_nActiveHashCells,    m_nActiveHashCells);
      GetNodeAttributeOrDefault(t_tree, "elevation",        m_fElevation,          m_fElevation);
      if(NodeExists(t_tree, "boundaries")) {
         /* Parse the boundary definition */
         TConfigurationNode& tBoundaries = GetNode(t_tree, "boundaries");
         SBoundarySegment sBoundSegment;
         CVector2 cLastPoint, cCurPoint;
         std::string strConnectWith;
         TConfigurationNodeIterator tVertexIt("vertex");
         /* Get the first vertex */
         tVertexIt = tVertexIt.begin(&tBoundaries);
         if(tVertexIt == tVertexIt.end()) {
            THROW_ARGOSEXCEPTION("Physics engine of type \"dynamics2d\", id \"" << GetId() << "\": you didn't specify any <vertex>!");
         }
         GetNodeAttribute(*tVertexIt, "point", cLastPoint);
         m_vecVertices.push_back(cLastPoint);
         /* Go through the other vertices */
         ++tVertexIt;
         while(tVertexIt != tVertexIt.end()) {
            /* Read vertex data and fill in segment struct */
            GetNodeAttribute(*tVertexIt, "point", cCurPoint);
            m_vecVertices.push_back(cCurPoint);
            sBoundSegment.Segment.SetStart(cLastPoint);
            sBoundSegment.Segment.SetEnd(cCurPoint);
            GetNodeAttribute(*tVertexIt, "connect_with", strConnectWith);
            if(strConnectWith == "gate") {
               /* Connect to previous vertex with a gate */
               sBoundSegment.Type = SBoundarySegment::SEGMENT_TYPE_GATE;
               GetNodeAttribute(*tVertexIt, "to_engine", sBoundSegment.EngineId);
            }
            else if(strConnectWith == "wall") {
               /* Connect to previous vertex with a wall */
               sBoundSegment.Type = SBoundarySegment::SEGMENT_TYPE_WALL;
               sBoundSegment.EngineId = "";
            }
            else {
               /* Parse error */
               THROW_ARGOSEXCEPTION("Physics engine of type \"dynamics2d\", id \"" << GetId() << "\": unknown vertex connection method \"" << strConnectWith << "\". Allowed methods are \"wall\" and \"gate\".");
            }
            m_vecSegments.push_back(sBoundSegment);
            /* Next vertex */
            cLastPoint = cCurPoint;
            ++tVertexIt;
         }
         /* Check that the boundary is a closed path */
         if(m_vecVertices.front() != m_vecVertices.back()) {
            THROW_ARGOSEXCEPTION("Physics engine of type \"dynamics2d\", id \"" << GetId() << "\": the specified path is not closed. The first and last points of the boundaries MUST be the same.");
         }
      }
      /* Initialize physics */
      cpInitChipmunk();
      cpResetShapeIdCounter();
      /* Used to attach static geometries so that they won't move and to simulate friction */
      m_ptGroundBody = cpBodyNew(INFINITY, INFINITY);
      /* Create the space to contain the movable objects */
      m_ptSpace = cpSpaceNew();
      /* Subiterations to solve constraints.
         The more, the better for precision but the worse for speed
      */
      m_ptSpace->iterations = m_nIterations;
      /* Resize the space hash.
         This has dramatic effects on performance.
         TODO: - find optimal parameters automatically (average entity size)
      */
      cpSpaceResizeStaticHash(m_ptSpace, m_fStaticHashCellSize, m_nStaticHashCells);
      cpSpaceResizeActiveHash(m_ptSpace, m_fActiveHashCellSize, m_nActiveHashCells);
      /* Gripper-Gripped callback functions */
      cpSpaceAddCollisionHandler(
         m_ptSpace,
         SHAPE_MAGNETIC_GRIPPER,
         SHAPE_GRIPPABLE,
         MagneticGripperGrippableCollisionBegin,
         MagneticGripperGrippableCollisionPreSolve,
         NULL,
         NULL,
         NULL);
      /* Add boundaries, if specified */
      if(! m_vecSegments.empty()) {
         cpShape* ptSegment;
         for(size_t i = 0; i < m_vecSegments.size(); ++i) {
            if(m_vecSegments[i].Type == SBoundarySegment::SEGMENT_TYPE_WALL) {
               ptSegment =
                  cpSpaceAddShape(
                     m_ptSpace,
                     cpSegmentShapeNew(
                        m_ptGroundBody,
                        cpv(m_vecSegments[i].Segment.GetStart().GetX(),
                            m_vecSegments[i].Segment.GetStart().GetY()),
                        cpv(m_vecSegments[i].Segment.GetEnd().GetX(),
                            m_vecSegments[i].Segment.GetEnd().GetY()),
                        0.0f));
               ptSegment->e = 0.0f; // no elasticity
               ptSegment->u = 1.0f; // max friction
            }
            else {
               /* There is at least a gate, transfer is activated */
               m_bEntityTransferActive = true;
            }
         }
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::Reset() {
      for(TDynamics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->Reset();
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::Update() {
      /* Update the physics state from the entities */
      for(TDynamics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->UpdateFromEntityStatus();
      }
      /* Perform the step */
      cpSpaceStep(m_ptSpace, m_fSimulationClockTick);
      /* Update the simulated space */
      for(TDynamics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         it->second->UpdateEntityStatus();
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::Destroy() {
      /* Empty the physics entity map */
      for(TDynamics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
          it != m_tPhysicsEntities.end(); ++it) {
         delete it->second;
      }
      m_tPhysicsEntities.clear();
      /* Get rid of the physics space */
      cpSpaceFree(m_ptSpace);
      cpBodyFree(m_ptGroundBody);
   }

   /****************************************/
   /****************************************/

   UInt32 CDynamics2DEngine::GetNumPhysicsEngineEntities() {
      return m_tPhysicsEntities.size();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::AddEntity(CEntity& c_entity) {
      c_entity.Accept(m_cAddVisitor);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::RemoveEntity(CEntity& c_entity) {
      c_entity.Accept(m_cRemoveVisitor);
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::TransferEntities() {
      for(size_t i = 0; i < m_vecTransferData.size(); ++i) {
         CPhysicsEngine& cToEngine = CSimulator::GetInstance().GetPhysicsEngine(m_vecTransferData[i].EngineId);
         cToEngine.AddEntity(*m_vecTransferData[i].Entity);
         RemoveEntity(*m_vecTransferData[i].Entity);
      }
      m_vecTransferData.clear();
   }

   /****************************************/
   /****************************************/

   bool CDynamics2DEngine::CalculateTransfer(Real f_x, Real f_y,
                                             std::string& str_engine_id) {
      /*
       * TODO: this method makes the assumption that only one gate is trespassed at any time.
       * This assumption may be false in some ill-shaped polygons or when the gate isn't just a
       * segment, but is a sequence of segments.
       */
      for(size_t i = 0; i < m_vecSegments.size(); ++i) {
         if(m_vecSegments[i].Type == SBoundarySegment::SEGMENT_TYPE_GATE) {
            const CVector2& cP0 = m_vecSegments[i].Segment.GetStart();
            const CVector2& cP1 = m_vecSegments[i].Segment.GetEnd();
            Real fCriterion =
               (f_y - cP0.GetY()) * (cP1.GetX() - cP0.GetX()) -
               (f_x - cP0.GetX()) * (cP1.GetY() - cP0.GetY());
            if(fCriterion < 0.0f) {
               str_engine_id = m_vecSegments[i].EngineId;
               return true;
            }
         }
      }
      return false;
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::AddPhysicsEntity(const std::string& str_id,
                                            CDynamics2DEntity& c_entity) {
      m_tPhysicsEntities[str_id] = &c_entity;
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::AddControllableEntity(CControllableEntity& c_entity) {
      m_tControllableEntities[c_entity.GetId()] = &c_entity;
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::RemovePhysicsEntity(const std::string& str_id) {
      TDynamics2DEntityMap::iterator it = m_tPhysicsEntities.find(str_id);
      if(it != m_tPhysicsEntities.end()) {
         delete it->second;
         m_tPhysicsEntities.erase(it);
      }
      else {
         THROW_ARGOSEXCEPTION("Dynamics2D entity id \"" << str_id << "\" not found in dynamics 2D engine \"" << GetId() << "\"");
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics2DEngine::RemoveControllableEntity(const std::string& str_id) {
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

   REGISTER_PHYSICS_ENGINE(CDynamics2DEngine,
                           "dynamics2d",
                           "A 2D dynamics physics engine",
                           "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                           "This physics engine is a 2D dynamics engine based on the Chipmunk library\n"
                           "(http://code.google.com/p/chipmunk-physics).\n\n"
                           "REQUIRED XML CONFIGURATION\n\n"
                           "  <physics_engines>\n"
                           "    ...\n"
                           "    <dynamics2d id=\"dyn2d\" />\n"
                           "    ...\n"
                           "  </physics_engines>\n\n"
                           "The 'id' attribute is necessary and must be unique among the physics engines.\n"
                           "It is used in the subsequent section <arena_physics> to assign entities to\n"
                           "physics engines. If two engines share the same id, initialization aborts.\n\n"
                           "OPTIONAL XML CONFIGURATION\n\n"
                           "The plane of the physics engine can be translated on the Z axis, to simulate\n"
                           "for example hovering objects, such as flying robots. To translate the plane\n"
                           "2m up the Z axis, use the 'elevation' attribute as follows:\n\n"
                           "  <physics_engines>\n"
                           "    ...\n"
                           "    <dynamics2d id=\"dyn2d\"\n"
                           "                elevation=\"2.0\" />\n"
                           "    ...\n"
                           "  </physics_engines>\n\n"
                           "When not specified, the elevation is zero, which means that the plane\n"
                           "corresponds to the XY plane.\n",
                           "Under development"
      );

}

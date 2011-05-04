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
 * @file <argos2/simulator/physics_engines/kinematics2d_engine.cpp>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "kinematics2d_engine.h"
#include <argos2/simulator/space/entities/embodied_entity.h>

namespace argos {

  /****************************************/
  /****************************************/

  CKinematics2DEngine::CKinematics2DEngine() :
    m_cAddVisitor(*this),
    m_cRemoveVisitor(*this),
    m_bDetectCollisions(true) {
  }

  /****************************************/
  /****************************************/

  CKinematics2DEngine::~CKinematics2DEngine() {
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::Init(TConfigurationNode& t_tree) {
    /* Init parent */
    CPhysicsEngine::Init(t_tree);

    GetNodeAttributeOrDefault(t_tree, "check_collisions", m_bDetectCollisions, m_bDetectCollisions);
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::Reset() {
    for(TKinematics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
	it != m_tPhysicsEntities.end(); ++it) {
      it->second->Reset();
    }
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::Destroy() {
    /* Empty the physics entity map */
    for(TKinematics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
	it != m_tPhysicsEntities.end(); ++it) {
      delete it->second;
    }
    m_tPhysicsEntities.clear();
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::Update() {
    /* Update the physics state from the entities */
    for(TKinematics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
	it != m_tPhysicsEntities.end(); ++it) {
      it->second->UpdateFromEntityStatus();
    }

    /* Perform the step */
    CollisionsDetection();

    /* Update the simulated space */
    for(TKinematics2DEntityMap::iterator it = m_tPhysicsEntities.begin();
	it != m_tPhysicsEntities.end(); ++it) {
      it->second->UpdateEntityStatus();
    }
  }

  /****************************************/
  /****************************************/

  UInt32 CKinematics2DEngine::GetNumPhysicsEngineEntities() {
    return m_tPhysicsEntities.size();
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::AddEntity(CEntity& c_entity) {
    c_entity.Accept(m_cAddVisitor);
  }
   
  /****************************************/
  /****************************************/

  void CKinematics2DEngine::RemoveEntity(CEntity& c_entity) {
    c_entity.Accept(m_cRemoveVisitor);
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::AddPhysicsEntity(const std::string& str_id,
                                             CKinematics2DEntity& c_entity) {
    m_tPhysicsEntities[str_id] = &c_entity;
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::AddControllableEntity(CControllableEntity& c_entity) {
    m_tControllableEntities[c_entity.GetId()] = &c_entity;
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::RemovePhysicsEntity(const std::string& str_id) {
    TKinematics2DEntityMap::iterator it = m_tPhysicsEntities.find(str_id);
    if(it != m_tPhysicsEntities.end()) {
      delete it->second;
      m_tPhysicsEntities.erase(it);
    }
    else {
      THROW_ARGOSEXCEPTION("entity id \"" << str_id << "\" not found in kinematics 2D engine \"" << GetId() << "\"");
    }
  }

  /****************************************/
  /****************************************/

  void CKinematics2DEngine::RemoveControllableEntity(const std::string& str_id) {
    TControllableEntityMap::iterator it = m_tControllableEntities.find(str_id);
    if(it != m_tControllableEntities.end()) {
      m_tControllableEntities.erase(it);
    }
    else {
      THROW_ARGOSEXCEPTION("Controllable entity id \"" << str_id << "\" not found in kinematics 2D engine \"" << GetId() << "\"");
    }
  }

  /****************************************/
  /****************************************/

  bool CKinematics2DEngine::CheckCollisions( const CKinematics2DCollisionCircle* pc_circle_1, const CKinematics2DCollisionCircle* pc_circle_2 ) {
    Real min_distance = pc_circle_1->GetRadius() + pc_circle_2->GetRadius();
    return (SquareDistance(pc_circle_1->GetPosition(), pc_circle_2->GetPosition()) <= min_distance*min_distance);
  }

  /****************************************/
  /****************************************/

  bool CKinematics2DEngine::CheckCollisions( const CKinematics2DCollisionRectangle* pc_rectangle_1, const CKinematics2DCollisionRectangle* pc_rectangle_2 ) {
    return false;
  }

  /****************************************/
  /****************************************/

  bool CKinematics2DEngine::CheckCollisions( const CKinematics2DCollisionCircle* pc_circle, const CKinematics2DCollisionRectangle* pc_rectangle ) {
    /* Rototranslate the plane so that the rectangle is axis aligned and centered in O */
    CVector2 center = pc_circle->GetPosition() - pc_rectangle->GetPosition();
    center.Rotate(pc_rectangle->GetOrientation() );
    center.Absolute();
    
    /* Find the Voronoi Region that the circle is in, exploiting the symmetries */
    CVector2 c_half_size   = pc_rectangle->GetHalfSize();
    Real     f_radius      = pc_circle->GetRadius();
    if( center.GetX() <= c_half_size.GetX() ) {
      /* The circle is in the top or bottom region */
      return (center.GetY() <= c_half_size.GetY() + f_radius);
    }
    
    if( center.GetY() <= c_half_size.GetY() ) {
      /* The circle is in the left or right region */
      return (center.GetX() <= c_half_size.GetX() + f_radius);
    }

    /* The circle is in one of the four corner regions */
    return (SquareDistance( c_half_size, center ) <= f_radius*f_radius);
  }



  /****************************************/
  /****************************************/

  void CKinematics2DEngine::CollisionsDetection( void ) {
    if(!m_bDetectCollisions)
      return;

    for( TKinematics2DEntityMap::const_iterator it1 = m_tPhysicsEntities.begin(); it1 != m_tPhysicsEntities.end(); ++it1 ) {
      bool it1_enabled = it1->second->IsEnabled();
      TKinematics2DCollisionType it1_type = it1->second->GetCollisionType();

      TKinematics2DEntityMap::const_iterator it2 = it1;
      for( ++it2; it2 != m_tPhysicsEntities.end(); ++it2 ) {
	bool it2_enabled = it2->second->IsEnabled();
	TKinematics2DCollisionType it2_type = it2->second->GetCollisionType();

	// skip collision detection if both entity are disabled or if
	// one of them has no collision model
	if( (!it1_enabled && !it2_enabled) ||
	    (it1_type == KINEMATICS2D_COLLISION_NONE) || 
	    (it2_type == KINEMATICS2D_COLLISION_NONE) ) {
	  continue;
	}
	
	// check intersection between bounding boxes
	if( !it1->second->GetEmbodiedEntity().GetBoundingBox().Intersects( it2->second->GetEmbodiedEntity().GetBoundingBox() ) ) {
	  continue;
	}

	bool collision_detected = false;
	if( (it1_type == KINEMATICS2D_COLLISION_CIRCLE) &&
	    (it2_type == KINEMATICS2D_COLLISION_CIRCLE) ) {
	  collision_detected = CheckCollisions(dynamic_cast<CKinematics2DCollisionCircle*>(it1->second), 
					       dynamic_cast<CKinematics2DCollisionCircle*>(it2->second));
	}
	else if( (it1_type == KINEMATICS2D_COLLISION_RECTANGLE) &&
		 (it2_type == KINEMATICS2D_COLLISION_CIRCLE) ) {
	  collision_detected = CheckCollisions(dynamic_cast<CKinematics2DCollisionCircle*>(it2->second),
					       dynamic_cast<CKinematics2DCollisionRectangle*>(it1->second));
	}
	else if( (it1_type == KINEMATICS2D_COLLISION_CIRCLE) &&
		 (it2_type == KINEMATICS2D_COLLISION_RECTANGLE) ) {
	  collision_detected = CheckCollisions(dynamic_cast<CKinematics2DCollisionCircle*>(it1->second),
					       dynamic_cast<CKinematics2DCollisionRectangle*>(it2->second));
	}
	else if( (it1_type == KINEMATICS2D_COLLISION_RECTANGLE) &&
		 (it2_type == KINEMATICS2D_COLLISION_RECTANGLE) ) {
	  collision_detected = CheckCollisions(dynamic_cast<CKinematics2DCollisionRectangle*>(it1->second),
					       dynamic_cast<CKinematics2DCollisionRectangle*>(it2->second));
	}
	else {
	  continue;
	}
	
	/* reset to previous positions if collision is detected */
	if( collision_detected ) {
	  it1->second->RevertPositionAndOrientation();
	  it1->second->GetEmbodiedEntity().SetCollisionDetected();
	  
	  it2->second->RevertPositionAndOrientation();
	  it2->second->GetEmbodiedEntity().SetCollisionDetected();
 	}
      }
    }
  }
  
  
  /****************************************/
  /****************************************/

  bool CKinematics2DEngine::CollisionsDetection( const CKinematics2DCollisionCircle* pc_circle ) {
    if(!m_bDetectCollisions)
      return false;
    
    bool enabled = pc_circle->IsEnabled();
    
    for( TKinematics2DEntityMap::const_iterator it = m_tPhysicsEntities.begin(); it != m_tPhysicsEntities.end(); ++it ) {
      /* don't ckeck if it's the same entity */
      if( pc_circle == it->second ) continue;

      bool it_enabled = it->second->IsEnabled();
      TKinematics2DCollisionType it_type = it->second->GetCollisionType();
      
      // skip collision detection if both entity are disabled or if
      // one of them has no collision model
      if( (!it_enabled && !enabled) ||
	  (it_type == KINEMATICS2D_COLLISION_NONE) ) {
	continue;
      }
      
      // check intersection between bounding boxes
      if( !pc_circle->GetEmbodiedEntity().GetBoundingBox().Intersects( it->second->GetEmbodiedEntity().GetBoundingBox() ) ) {
	continue;
      }
      
      bool collision_detected = false;
      if( it_type == KINEMATICS2D_COLLISION_CIRCLE ) {
	collision_detected = CheckCollisions(pc_circle, dynamic_cast<CKinematics2DCollisionCircle*>(it->second));
      }
      else if( it_type == KINEMATICS2D_COLLISION_RECTANGLE ) {
	collision_detected = CheckCollisions(pc_circle, dynamic_cast<CKinematics2DCollisionRectangle*>(it->second));
      }
      else  {
	continue;
      }
      
      /* reset to previous positions if collision is detected */
      if( collision_detected ) {
	return true;
      }
    }
    
    return false;
  }


  /****************************************/
  /****************************************/

  bool CKinematics2DEngine::CollisionsDetection( const CKinematics2DCollisionRectangle* pc_rectangle ) {
    if(!m_bDetectCollisions)
      return false;
    
    bool enabled = pc_rectangle->IsEnabled();
    
    for( TKinematics2DEntityMap::const_iterator it = m_tPhysicsEntities.begin(); it != m_tPhysicsEntities.end(); ++it ) {
      /* don't ckeck if it's the same entity */
      if( pc_rectangle == it->second ) continue;

      bool it_enabled = it->second->IsEnabled();
      TKinematics2DCollisionType it_type = it->second->GetCollisionType();
      
      // skip collision detection if both entities are disabled or if
      // one of them has no collision model
      if( (!it_enabled && !enabled) ||
	  (it_type == KINEMATICS2D_COLLISION_NONE) ) {
	continue;
      }
      
      // check intersection between bounding boxes
      if( !pc_rectangle->GetEmbodiedEntity().GetBoundingBox().Intersects( it->second->GetEmbodiedEntity().GetBoundingBox() ) ) {
	continue;
      }
      
      bool collision_detected = false;
      if( it_type == KINEMATICS2D_COLLISION_CIRCLE ) {
	collision_detected = CheckCollisions(dynamic_cast<CKinematics2DCollisionCircle*>(it->second), pc_rectangle);
      }
      else if( it_type == KINEMATICS2D_COLLISION_RECTANGLE ) {
	collision_detected = CheckCollisions(pc_rectangle, dynamic_cast<CKinematics2DCollisionRectangle*>(it->second));
      }
      else  {
	continue;
      }
      
      /* reset to previous positions if collision is detected */
      if( collision_detected ) {
	return true;
      }
    }
    
    return false;
  }


  
  /****************************************/
  /****************************************/

  REGISTER_PHYSICS_ENGINE(CKinematics2DEngine,
			  "kinematics2d",
			  "A 2D physics engine in which entities simulation is limited to kinematics",
			  "Vito Trianni [vito.trianni@istc.cnr.it]",
			  "This physics engine is a 2D engine based on simple kinematics and minimal\n"
			  "collision detection. It does not handle connections between robots,\n"
			  "friction and many other details, but it is rather fast.\n"
			  "REQUIRED XML CONFIGURATION\n\n"
			  "  <physics_engines>\n"
			  "    ...\n"
			  "    <kinematics2d id=\"kin2d\" />\n"
			  "    ...\n"
			  "  </physics_engines>\n\n"
			  "The 'id' attribute is necessary and must be unique among the physics engines.\n"
			  "It is used in the subsequent section <arena_physics> to assign entities to\n"
			  "physics engines. If two engines share the same id, initialization aborts.\n\n"
			  "OPTIONAL XML CONFIGURATION\n\n"
			  "Collisions can be disabled using the 'check_collisions' attribute as follows:\n"
			  "  <physics_engines>\n"
			  "    ...\n"
			  "    <kinematics2d id=\"kin2d\"\n"
			  "                check_collisions=\"false\" />\n"
			  "    ...\n"
			  "  </physics_engines>\n\n",
			  "Under development"
			  );
}

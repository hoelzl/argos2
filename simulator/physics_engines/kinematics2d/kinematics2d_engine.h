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
 * @file <argos2/simulator/physics_engines/kinematics2d_engine.h>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef KINEMATICS2D_ENGINE_H
#define KINEMATICS2D_ENGINE_H

namespace argos {
  class CKinematics2DEngine;
  class CKinematics2DEntity;
}

#include <argos2/simulator/physics_engines/physics_engine.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_entity.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_collision_circle.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_collision_rectangle.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_add_visitor.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_remove_visitor.h>
#include <argos2/simulator/space/entities/controllable_entity.h>

namespace argos {

  class CKinematics2DEngine : public CPhysicsEngine {

  public:

    CKinematics2DEngine();
    virtual ~CKinematics2DEngine();

    virtual void Init(TConfigurationNode& t_tree);
    virtual void Reset();
    virtual void Destroy();

    virtual void Update();

    virtual UInt32 GetNumPhysicsEngineEntities();
    virtual void AddEntity(CEntity& c_entity);
    virtual void RemoveEntity(CEntity& c_entity);

    inline void PositionPhysicsToSpace(CVector3& c_new_pos,
				       const CVector3& c_original_pos,
				       const CVector2& c_engine_pos) {
      c_new_pos.Set(c_engine_pos.GetX(),
		    c_engine_pos.GetY(),
		    c_original_pos.GetZ());
    }
    
    inline void OrientationPhysicsToSpace(CQuaternion& c_new_orient,
					  const CRadians& c_angle) {
      c_new_orient.FromAngleAxis(c_angle, CVector3::Z);
    }
    

    bool CheckCollisions( const CKinematics2DCollisionCircle* pc_circle_1, const CKinematics2DCollisionCircle* pc_circle_2 );
    bool CheckCollisions( const CKinematics2DCollisionRectangle* pc_rectangle_1, const CKinematics2DCollisionRectangle* pc_rectangle_2 );
    bool CheckCollisions( const CKinematics2DCollisionCircle* pc_circle, const CKinematics2DCollisionRectangle* pc_rectangle );
    
    void CollisionsDetection( void );
    
    // collision detection for individual shapes
    bool CollisionsDetection( const CKinematics2DCollisionCircle* pc_circle_1 );
    bool CollisionsDetection( const CKinematics2DCollisionRectangle* pc_rectangle_1 );



  private:

    void AddPhysicsEntity(const std::string& str_id,
			  CKinematics2DEntity& c_entity);
    void AddControllableEntity(CControllableEntity& c_entity);
    void RemovePhysicsEntity(const std::string& str_id);
    void RemoveControllableEntity(const std::string& str_id);

  private:

    CKinematics2DAddVisitor m_cAddVisitor;
    CKinematics2DRemoveVisitor m_cRemoveVisitor;
    TControllableEntityMap m_tControllableEntities;
    TKinematics2DEntityMap m_tPhysicsEntities;
    friend class CKinematics2DAddVisitor;
    friend class CKinematics2DRemoveVisitor;

    bool m_bDetectCollisions;

  };

}

#endif

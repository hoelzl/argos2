/* -*- Mode: C++ -*-
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
 * @file <argos2/simulator/physics_engines/kinematics2d_footbot.cpp>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "kinematics2d_footbot.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_engine.h>

namespace argos {

  /****************************************/
  /****************************************/

  static const Real FOOTBOT_RADIUS                   = 0.085036758f;
  static const Real FOOTBOT_INTERWHEEL_DISTANCE      = 0.14f;
  static const Real FOOTBOT_HEIGHT                   = 0.146899733f;

  enum FOOTBOT_WHEELS {
    FOOTBOT_LEFT_WHEEL = 0,
    FOOTBOT_RIGHT_WHEEL = 1
  };

  /****************************************/
  /****************************************/

  CKinematics2DFootBot::CKinematics2DFootBot(CKinematics2DEngine& c_engine,
					     CFootBotEntity& c_footbot) :
    CKinematics2DCollisionCircle(c_engine, c_footbot.GetEmbodiedEntity(), FOOTBOT_RADIUS),
    m_cFootBotEntity(c_footbot),
    m_cWheeledEntity(c_footbot.GetWheeledEntity()),
    m_cGripperEntity(c_footbot.GetGripperEquippedEntity()) {

    m_fCurrentWheelVelocityFromSensor[FOOTBOT_LEFT_WHEEL] = 0.0f;
    m_fCurrentWheelVelocityFromSensor[FOOTBOT_RIGHT_WHEEL] = 0.0f;
  }

  /****************************************/
  /****************************************/

  void CKinematics2DFootBot::UpdateEntityStatus() {
    /* update entity position and orientation */
    CKinematics2DEntity::UpdateEntityStatus();

    /* Update foot-bot components */
    m_cFootBotEntity.UpdateComponents();
  }
  
  /****************************************/
  /****************************************/
  
  void CKinematics2DFootBot::UpdateFromEntityStatus() {
    /* Store previous position and orientation for collision avoidance */
    CKinematics2DEntity::UpdateFromEntityStatus();

    /* Get wheel speeds from entity */
    m_cWheeledEntity.GetSpeed(m_fCurrentWheelVelocityFromSensor);

    /* Do we want to move? */
    if((m_fCurrentWheelVelocityFromSensor[FOOTBOT_LEFT_WHEEL] != 0.0f) ||
       (m_fCurrentWheelVelocityFromSensor[FOOTBOT_RIGHT_WHEEL] != 0.0f)) {
      /* Yeah, we do */

      /**
       *
       * THE DIFFERENTIAL STEERING SYSTEM
       *
       * The differential drive motion can be simulated according to
       * the following equations:
       *
       * 	dx/dt = [(Vl + Vr)/2] * r * cos( a )
       * 	dy/dt = [(Vl + Vr)/2] * r * sin( a )                 (1),
       * 	da/dt = [Vr - Vl] * r / L
       *
       * where x,y are the absolute coordinates in the world reference
       * frame, Vr and Vl are the angular speed of the left and right
       * wheels, r is the radius of the wheels and L is the distance
       * between the centers of the wheels.
       *
       * Integrating (1) we obtain:
       *
       * 	x(t) = x(t-1) + dt * [(Vl + Vr)/2] * r * cos( a )
       * 	y(t) = y(t-1) + dt * [(Vl + Vr)/2] * r * sin( a )    (2),
       * 	a(t) = a(t-1) + dt * [Vr - Vl] * r / L
       *
       **/

      /* Update position and heading according to the physics equations */
      m_cPosition    += (CVector2((m_fCurrentWheelVelocityFromSensor[FOOTBOT_RIGHT_WHEEL]+m_fCurrentWheelVelocityFromSensor[FOOTBOT_LEFT_WHEEL])*CPhysicsEngine::GetSimulationClockTick()/2.0, 0).Rotate(m_cOrientation));
      m_cOrientation += CRadians((m_fCurrentWheelVelocityFromSensor[FOOTBOT_RIGHT_WHEEL] - m_fCurrentWheelVelocityFromSensor[FOOTBOT_LEFT_WHEEL])/
				 FOOTBOT_INTERWHEEL_DISTANCE * CPhysicsEngine::GetSimulationClockTick());
    }
  }
  
  /****************************************/
  /****************************************/
}

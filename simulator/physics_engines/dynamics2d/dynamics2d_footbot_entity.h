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
 * @file <argos2/simulator/physics_engines/dynamics2d_footbot_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS2D_FOOTBOT_ENTITY_H
#define DYNAMICS2D_FOOTBOT_ENTITY_H

namespace argos {
   class SDynamics2DEngineGripperData;
}

#include <argos2/simulator/physics_engines/dynamics2d/dynamics2d_entity.h>
#include <argos2/simulator/space/entities/footbot_entity.h>

namespace argos {

   class CDynamics2DFootBotEntity : public CDynamics2DEntity {

   public:

      CDynamics2DFootBotEntity(CDynamics2DEngine& c_engine,
                               CFootBotEntity& c_entity);
      virtual ~CDynamics2DFootBotEntity();
      
      virtual bool CheckIntersectionWithRay(Real& f_t_on_ray,
                                            const CRay& c_ray) const;

      virtual bool MoveTo(const CVector3& c_position,
                          const CQuaternion& c_orientation,
                          bool b_check_only = false);

      virtual void Reset();

      virtual void UpdateEntityStatus();
      virtual void UpdateFromEntityStatus();

   private:

      void TurretPassiveToActive();
      void TurretActiveToPassive();

   private:

      CFootBotEntity& m_cFootBotEntity;
      CWheeledEntity<2>& m_cWheeledEntity;
      CGripperEquippedEntity& m_cGripperEntity;

      cpFloat  m_fMass;
      cpShape* m_ptBaseShape;
      cpShape* m_ptGripperShape;
      cpBody*  m_ptActualBaseBody;
      cpBody*  m_ptControlBaseBody;
      cpBody*  m_ptActualGripperBody;
      cpBody*  m_ptControlGripperBody;
      cpConstraint* m_ptBaseControlLinearMotion;
      cpConstraint* m_ptBaseControlAngularMotion;
      cpConstraint* m_ptGripperControlLinearMotion;
      cpConstraint* m_ptGripperControlAngularMotion;
      cpConstraint* m_ptBaseGripperLinearMotion;
      cpConstraint* m_ptBaseGripperAngularMotion;

      SDynamics2DEngineGripperData* m_psGripperData;

      Real m_fCurrentWheelVelocityFromSensor[2];
      UInt8 m_unLastTurretMode;

      Real m_fPreviousTurretAngleError;

   };

}

#endif

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
 * @file <argos2/simulator/physics_engines/pointmass3d_eyebot.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "pointmass3d_eyebot.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/physics_engines/pointmass3d/pointmass3d_engine.h>

namespace argos {

   /* Values taken from Tim's 3D dynamics model in ARGoS1 */
   static const Real SURFACE_AREA = 0.2f;
   static const Real DRAG_COEFFICIENT = 16.6f; // Drag coefficient
   static const Real AIR_DENSITY = 1.205f; // Room Temperature
   static const Real MASS = 0.5f;
   static const Real EYEBOT_HEIGHT = 0.566;

   /****************************************/
   /****************************************/

   CPointMass3DEyeBot::CPointMass3DEyeBot(CPointMass3DEngine& c_engine,
                                          CEyeBotEntity& c_eyebot) :
      CPointMass3DEntity(c_engine, c_eyebot.GetEmbodiedEntity()),
      m_cEyeBotEntity(c_eyebot),
      m_fArenaHeight(CSimulator::GetInstance().GetSpace().GetArenaSize().GetZ()) {
   }

   /****************************************/
   /****************************************/

   bool CPointMass3DEyeBot::MoveTo(const CVector3& c_position,
                                   const CQuaternion& c_orientation,
                                   bool b_check_only) {
      if(! b_check_only) {
         m_cEyeBotEntity.GetEmbodiedEntity().SetPosition(c_position);
         m_cEyeBotEntity.GetEmbodiedEntity().SetOrientation(c_orientation);
      }
      return true;
   }

   /****************************************/
   /****************************************/

   void CPointMass3DEyeBot::UpdateEntityStatus() {
      /* The eye-bot can move only when it's detached from the ceiling */
      if(m_cEyeBotEntity.IsDetachedFromCeiling()) {
         /* Zero the force */
         m_cTotalForce = CVector3::ZERO;
         /* Move the eye-bot */
         if(m_cEyeBotEntity.GetMotionData().Source == CEyeBotEntity::SMotionData::MOTION_FROM_FORCES) {
            /* Apply wanted forces */
            /* Calculate a simple air-friction model */
            if(m_cVelocity != CVector3::ZERO) {
               CVector3 cFriction(m_cVelocity);
               cFriction.Normalize().Negate();
               Real fFrictionMag =
                  m_cVelocity.SquareLength() *
                  SURFACE_AREA *
                  AIR_DENSITY *
                  DRAG_COEFFICIENT *
                  MASS;
               Real fMaxFrictionMag = m_cVelocity.Length() * MASS / m_cEngine.GetSimulationClockTick();
               if(fFrictionMag > fMaxFrictionMag) {
                  fFrictionMag = fMaxFrictionMag;
               }
               cFriction *= fFrictionMag;
               /* Add friction to the total forces */
               m_cTotalForce += cFriction;
            }
            /* Add to the force the wanted forces */
            CVector3 cEyebotForce(m_cEyeBotEntity.GetMotionData().ForceX,
                                  - m_cEyeBotEntity.GetMotionData().ForceY,
                                  m_cEyeBotEntity.GetMotionData().ForceZ);
            cEyebotForce.Rotate(m_cEyeBotEntity.GetEmbodiedEntity().GetOrientation());
            m_cTotalForce += cEyebotForce;

            /* Subtract gravity */
            m_cTotalForce -= CVector3(0.0f,
                                      0.0f,
                                      MASS * 9.81f);
            /* Integrate the force to update motion */
            /* First update the position, using the old velocity */
            CVector3 cPosition(m_cVelocity);
            cPosition *= m_cEngine.GetSimulationClockTick();
            cPosition += m_cEyeBotEntity.GetEmbodiedEntity().GetPosition();
            if(cPosition.GetZ() < 0.0f) cPosition.SetZ(0.0f); /* Prevent the eye-bot from free falling under the floor */
            if(cPosition.GetZ() > (m_fArenaHeight - EYEBOT_HEIGHT)) cPosition.SetZ(m_fArenaHeight - EYEBOT_HEIGHT); /* Consider there is a ceiling! */
            m_cEyeBotEntity.GetEmbodiedEntity().SetPosition(cPosition);
            /* Then update the velocity for the next time step */
            m_cVelocity += (m_cTotalForce / MASS) * m_cEngine.GetSimulationClockTick();
std::cerr << "Current velocity eb " << m_cEyeBotEntity.GetId() << ": " << m_cVelocity << std::endl;
         }
         else {
            /* Apply wanted speeds */
            CRadians cAngle;
            CVector3 cTmp;
            /* Apply angular speed to update orientation */
            m_cEyeBotEntity.GetEmbodiedEntity().GetOrientation().ToAngleAxis(cAngle, cTmp);
            cAngle += CRadians(m_cEyeBotEntity.GetMotionData().AngularSpeed * m_cEngine.GetSimulationClockTick());
            cAngle.UnsignedNormalize();
            m_cEyeBotEntity.GetEmbodiedEntity().SetOrientation(CQuaternion(cAngle, cTmp));
            /* Apply linear speed to update position */
            m_cVelocity = CVector3::X;
            m_cVelocity.Rotate(m_cEyeBotEntity.GetEmbodiedEntity().GetOrientation());
            m_cVelocity *= m_cEyeBotEntity.GetMotionData().LinearSpeed;
            cTmp = m_cVelocity;
            cTmp *= m_cEngine.GetSimulationClockTick();
            cTmp += m_cEyeBotEntity.GetEmbodiedEntity().GetPosition();
            m_cEyeBotEntity.GetEmbodiedEntity().SetPosition(cTmp);
         }
      }
      else {
         /* The eye-bot is attached */
         m_cEyeBotEntity.GetEmbodiedEntity().SetPosition(
            CVector3(m_cEyeBotEntity.GetEmbodiedEntity().GetPosition().GetX(),
                     m_cEyeBotEntity.GetEmbodiedEntity().GetPosition().GetY(),
                     m_fArenaHeight - EYEBOT_HEIGHT));
      }
      /* Update the components */
      m_cEyeBotEntity.UpdateComponents();
   }

   /****************************************/
   /****************************************/

}

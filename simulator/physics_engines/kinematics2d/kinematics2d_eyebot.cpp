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
 * @file <argos2/simulator/physics_engines/kinematics2d_eyebot.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "kinematics2d_eyebot.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   CKinematics2DEyeBot::CKinematics2DEyeBot(CKinematics2DEngine& c_engine,
                                          CEyeBotEntity& c_eyebot) :
      CKinematics2DEntity(c_engine, c_eyebot.GetEmbodiedEntity()),
      m_cEyeBotEntity(c_eyebot),
      m_fArenaHeight(CSimulator::GetInstance().GetSpace().GetArenaSize().GetZ()) {
   }

   /****************************************/
   /****************************************/

   bool CKinematics2DEyeBot::MoveTo(const CVector3& c_position,
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

   void CKinematics2DEyeBot::UpdateEntityStatus() {
      /* The eye-bot can move only when it's detached from the ceiling */
      if(m_cEyeBotEntity.IsDetachedFromCeiling()) {
         /* Move the eye-bot */
         if(m_cEyeBotEntity.GetMotionData().Source == CEyeBotEntity::SMotionData::MOTION_FROM_FORCES) {
            /* Apply wanted forces */
            // TODO
         }
         else {
            /* Apply wanted speeds */
            CRadians cAngle;
            CVector3 cTmp;
            /* Apply angular speed to update orientation */
            m_cEyeBotEntity.GetEmbodiedEntity().GetOrientation().ToAngleAxis(cAngle, cTmp);
            cAngle += CRadians(m_cEyeBotEntity.GetMotionData().AngularSpeed * m_cEngine.GetSimulationClockTick());
            cAngle.UnsignedNormalize();
            LOGERR << "[KINEMATICS2D_EYEBOT] Axis = "
                   << cTmp
                   << ", Angle = "
                   << cAngle
                   << std::endl;
            m_cEyeBotEntity.GetEmbodiedEntity().SetOrientation(CQuaternion(cAngle, cTmp));
            /* Apply linear speed to update position */
            cTmp = CVector3::X;
            cTmp.Rotate(m_cEyeBotEntity.GetEmbodiedEntity().GetOrientation());
            cTmp *= m_cEyeBotEntity.GetMotionData().LinearSpeed * m_cEngine.GetSimulationClockTick();
            cTmp += m_cEyeBotEntity.GetEmbodiedEntity().GetPosition();
            LOGERR << "[KINEMATICS2D_EYEBOT] Pos = "
                   << cTmp
                   << std::endl;
            m_cEyeBotEntity.GetEmbodiedEntity().SetPosition(cTmp);
         }
      }
      else {
         /* The eye-bot is attached */
         m_cEyeBotEntity.GetEmbodiedEntity().SetPosition(
            CVector3(m_cEyeBotEntity.GetEmbodiedEntity().GetPosition().GetX(),
                     m_cEyeBotEntity.GetEmbodiedEntity().GetPosition().GetY(),
                     m_fArenaHeight));
      }
   }

   /****************************************/
   /****************************************/

}

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
 * @file <argos2/simulator/space/entities/distance_scanner_equipped_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#include "distance_scanner_equipped_entity.h"
#include <argos2/simulator/physics_engines/physics_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   CDistanceScannerEquippedEntity::CDistanceScannerEquippedEntity(CEntity* pc_parent) :
      CEntity(pc_parent),
      m_unMode(MODE_OFF),
      m_fRotationSpeed(0.0f) {}
   
   /****************************************/
   /****************************************/

   void CDistanceScannerEquippedEntity::Reset() {
      m_unMode = MODE_OFF;
      m_cRotation = CRadians::ZERO;
      m_fRotationSpeed = 0.0f;
   }

   /****************************************/
   /****************************************/

   void CDistanceScannerEquippedEntity::UpdateRotation() {
      if(m_unMode == MODE_SPEED_CONTROL &&
         m_fRotationSpeed != 0.0f) {
         m_cRotation += CRadians(m_fRotationSpeed * CPhysicsEngine::GetSimulationClockTick());
         m_cRotation.UnsignedNormalize();
      }
   }

   /****************************************/
   /****************************************/

}

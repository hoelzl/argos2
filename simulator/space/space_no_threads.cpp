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
 * @file <argos2/simulator/space/space_no_threads.cpp>
 *
 * @brief This file provides the implementation of the Swarmanoid 3D Space.
 *
 * This file provides the implementation of the Swarmanoid 3D Space.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "space_no_threads.h"
#include <argos2/simulator/simulator.h>

namespace argos {

   /****************************************/
   /****************************************/

   void CSpaceNoThreads::UpdateControllableEntities() {
      for(size_t i = 0; i < m_vecControllableEntities.size(); ++i) {
         m_vecControllableEntities[i]->Sense();
         m_vecControllableEntities[i]->ControlStep();
      }
      for(size_t i = 0; i < m_vecControllableEntities.size(); ++i) {
         m_vecControllableEntities[i]->Act();
      }
   }

   /****************************************/
   /****************************************/

   void CSpaceNoThreads::UpdatePhysics() {
      /* Update the physics engines */
      for(size_t i = 0; i < m_ptPhysicsEngines->size(); ++i) {
         (*m_ptPhysicsEngines)[i]->Update();
      }
      /* Perform entity transfer from engine to engine, if needed */
      for(size_t i = 0; i < m_ptPhysicsEngines->size(); ++i) {
         if((*m_ptPhysicsEngines)[i]->IsEntityTransferNeeded()) {
            (*m_ptPhysicsEngines)[i]->TransferEntities();
         }
      }
   }

   /****************************************/
   /****************************************/

}

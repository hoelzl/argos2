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
 * @file <argos2/simulator/actuators/range_and_bearing_actuator.cpp>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "range_and_bearing_actuator.h"
#include <argos2/simulator/space/entities/composable_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CRangeAndBearingActuator::CRangeAndBearingActuator() :
      m_pcRABEquippedEntity(NULL),
      m_fRange(0.0f) {
   }

   /****************************************/
   /****************************************/

   void CRangeAndBearingActuator::Init(TConfigurationNode& t_node) {
      try {
         GetNodeAttribute(t_node, "range", m_fRange);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error initializing range and bearing actuator", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CRangeAndBearingActuator::SetEntity(CEntity& c_entity) {
      /* Let's check if it is a composable entity with a RAB component */
      CComposableEntity* pcComposableEntity = dynamic_cast<CComposableEntity*>(&c_entity);
      if(pcComposableEntity != NULL &&
         pcComposableEntity->HasComponent("rab_equipped_entity<10>")) {
         /* All OK */
         m_pcRABEquippedEntity = &(pcComposableEntity->GetComponent< CRABEquippedEntity<10> >("rab_equipped_entity<10>"));
         /* Also, set the transmission range */
         m_pcRABEquippedEntity->SetRange(m_fRange);
      }
      else {
         /* Wrong entity associated */
         THROW_ARGOSEXCEPTION("Cannot associate a range and bearing actuator to a robot of type \"" << c_entity.GetTypeDescription() << "\"");
      }
   }
   
   /****************************************/
   /****************************************/

   void CRangeAndBearingActuator::SetData(const TRangeAndBearingReceivedPacket::TRangeAndBearingData& t_data) {
      ::memcpy(m_tData, t_data, 10);
   }

   /****************************************/
   /****************************************/

   void CRangeAndBearingActuator::Update() {
      m_pcRABEquippedEntity->SetData(m_tData);
   }

   /****************************************/
   /****************************************/

   void CRangeAndBearingActuator::Reset() {
      m_pcRABEquippedEntity->ClearData();
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CRangeAndBearingActuator,
                     "range_and_bearing", "default",
                     "The Swarmanoid range and bearing actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "TODO",
                     "Under development"
      );
}

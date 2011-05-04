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
 * @file <argos2/simulator/actuators/wifi_actuator.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "wifi_actuator.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/entities/composable_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CWiFiActuator::CWiFiActuator() :
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_pcEntity(NULL),
      m_pcWiFiEquippedEntity(NULL) {}

   /****************************************/
   /****************************************/

   void CWiFiActuator::Init(TConfigurationNode& t_tree) {
      /* INITIALIZATION GOES HERE, NOT IN THE CONSTRUCTOR */
   }

   /****************************************/
   /****************************************/

   void CWiFiActuator::SetEntity(CEntity& c_entity) {
      /* Treat the entity as composable */
      CComposableEntity* pcComposableEntity = dynamic_cast<CComposableEntity*>(&c_entity);
      if(pcComposableEntity != NULL) {
         /* The entity is composable, does it have the required component? */
         if(pcComposableEntity->HasComponent("wifi_equipped_entity")) {
            /* Yes, it does */
            m_pcWiFiEquippedEntity = &(pcComposableEntity->GetComponent<CWiFiEquippedEntity>("wifi_equipped_entity"));
            m_pcEntity = &c_entity;
         }
         else {
            /* No, error */
            THROW_ARGOSEXCEPTION("Cannot associate a wifi actuator to an entity of type \"" << c_entity.GetTypeDescription() << "\"");
         }
      }
   }

   /****************************************/
   /****************************************/

   void CWiFiActuator::Update() {
      /* ADD MESSAGE TO SEND TO THE WIFI MEDIUM */
      /* THE MESSAGE TO SEND IS SET BY THE METHODS
         SendMessageTo() AND BroadcastMessage()
       */
      /* HERE JUST A COPY HAPPENS, AND THE DELAY IS TAKEN
         INTO ACCOUNT TO DECIDE WHETHER OR NOT TO PERFORM
         THE COPY OR NOT */
   }

   /****************************************/
   /****************************************/

   void CWiFiActuator::Reset() {
   }

   /****************************************/
   /****************************************/

   void CWiFiActuator::SendMessageTo(const std::string& str_recipient,
                                     const std::string& str_payload,
                                     Real f_delay) {
      /* CREATE AND STORE MESSAGE TO SEND INTO THIS SENSOR */
   }

   /****************************************/
   /****************************************/

   void CWiFiActuator::BroadcastMessage(const std::string& str_payload,
                                        Real f_delay) {
      /* CREATE AND STORE MESSAGE TO SEND INTO THIS SENSOR */
   }

   /****************************************/
   /****************************************/

}

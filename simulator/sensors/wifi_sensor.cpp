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
 * @file <argos2/simulator/sensors/wifi_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "wifi_sensor.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/entities/composable_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CWiFiSensor::CWiFiSensor() :
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_pcEntity(NULL),
      m_pcWiFiEquippedEntity(NULL) {}

   /****************************************/
   /****************************************/

   void CWiFiSensor::Init(TConfigurationNode& t_tree) {
      /* INITIALIZATION GOES HERE, NOT IN THE CONSTRUCTOR */
   }

   /****************************************/
   /****************************************/

   void CWiFiSensor::SetEntity(CEntity& c_entity) {
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
            THROW_ARGOSEXCEPTION("Cannot associate a wifi sensor to an entity of type \"" << c_entity.GetTypeDescription() << "\"");
         }
      }
   }
      
   /****************************************/
   /****************************************/

   void CWiFiSensor::Update() {
      /* READ MESSAGES FROM THE WIFI MEDIUM ENTITY AND GET THOSE FOR THIS ROBOT */
   }

   /****************************************/
   /****************************************/

   void CWiFiSensor::Reset() {
      /* RESTORE STATUS OF THE SENSOR TO ITS STATUS RIGHT AFTER Init() WAS CALLED */
   }

   /****************************************/
   /****************************************/

   void CWiFiSensor::GetReceivedMessages(CCI_WiFiActuator::TMessageList& t_messages) {
      /* POPULATE THE ARRAY OF RECEIVED MESSAGES */
      /* USE THE INFORMATION CALCULATED IN THE Update() FUNCTION */
      /* USUALLY IN THIS FUNCTION NO CALCULATION HAPPENS, Update() HAS ALREADY DONE EVERYTHING */
   }

   /****************************************/
   /****************************************/

}

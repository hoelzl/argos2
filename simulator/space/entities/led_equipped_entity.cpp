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
 * @file <argos2/simulator/space/entities/led_equipped_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "led_equipped_entity.h"

namespace argos {

   /****************************************/
   /****************************************/

   CLedEquippedEntity::~CLedEquippedEntity() {
      while(! m_tLeds.empty()) {
         CLedEntity* pcTmp = m_tLeds.back();
         m_tLeds.pop_back();
         delete pcTmp;
      }
   }

   /****************************************/
   /****************************************/

   void CLedEquippedEntity::Init(TConfigurationNode& t_tree) {
      CEntity::Init(t_tree);
      for(UInt32 i = 0; i < m_tLeds.size(); ++i) {
         m_tLeds[i]->Init(t_tree);
         m_tLeds[i]->SetId(GetId() + "_led_" + ToString(i));
      }
   }

   /****************************************/
   /****************************************/

   void CLedEquippedEntity::Reset() {
      for(TLedEntityList::iterator it = m_tLeds.begin();
          it != m_tLeds.end();
          ++it) {
         (*it)->Reset();
      }
   }

   /****************************************/
   /****************************************/

}

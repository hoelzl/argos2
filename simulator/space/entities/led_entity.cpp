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
 * @file <argos2/simulator/space/entities/led_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "led_entity.h"

namespace argos {

   /****************************************/
   /****************************************/

   void CLedEntity::Reset() {
      m_cColor = CColor::BLACK;
   }

   /****************************************/
   /****************************************/

   void CLEDEntitySpaceHashUpdater::operator()(CAbstractSpaceHash<CLedEntity>& c_space_hash,
                                               CLedEntity& c_element) {
      /* Discard LEDs switched off */
      if(c_element.GetColor() != CColor::BLACK) {
         /* Calculate the position of the LED in the space hash */
         c_space_hash.SpaceToHashTable(m_nI, m_nJ, m_nK, c_element.GetPosition());
         /* Update the corresponding cell */
         c_space_hash.UpdateCell(m_nI, m_nJ, m_nK, c_element);
      }
   }

   /****************************************/
   /****************************************/

}

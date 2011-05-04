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

#include "entity.h"
#include <argos2/simulator/space/space.h>
#include <simulator.h>
#include <visitors/entity_visitor.h>
#include <argos2/common/utility/string_utilities.h>

namespace argos {

   /****************************************/
   /****************************************/

   void CEntity::Init(TConfigurationNode& t_tree)
   {
      try {
         /* Get the id of the entity */
         GetNodeAttribute(t_tree, "id", m_strId);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize an entity.", ex);
      }
   }

   /****************************************/
   /****************************************/

}

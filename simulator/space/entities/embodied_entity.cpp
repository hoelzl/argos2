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

#include "embodied_entity.h"
#include <argos2/simulator/space/space.h>
#include <simulator.h>
#include <visitors/entity_visitor.h>
#include <argos2/common/utility/string_utilities.h>
#include <argos2/common/utility/math/matrix3x3.h>

namespace argos {

   /****************************************/
   /****************************************/

   void CEmbodiedEntity::Init(TConfigurationNode& t_tree) {
      CPositionalEntity::Init(t_tree);
      m_bBoundingBoxRecalculationNeeded = true;
   }

   /****************************************/
   /****************************************/

   void CEmbodiedEntity::Reset() {
      CPositionalEntity::Reset();
      /* Reset collision data */
      ResetCollisionDetected();
      SetCollisionNumber(0);
      m_bBoundingBoxRecalculationNeeded = true;
   }

   /****************************************/
   /****************************************/

   bool CEmbodiedEntity::CheckIntersectionWithRay(Real& f_distance,
                                                  const CRay& c_ray) const {
      for(UInt32 i = 0; i < m_tPhysicsEngineEntityVector.size(); ++i)
         if(m_tPhysicsEngineEntityVector[i]->CheckIntersectionWithRay(f_distance, c_ray)) {
            return true;
      }
      return false;
   }

   /****************************************/
   /****************************************/

   bool CEmbodiedEntity::MoveTo(const CVector3& c_position,
                                const CQuaternion& c_orientation,
                                bool b_check_only) {
      bool bNoCollision = true;
      for(TPhysicsEngineEntityVector::const_iterator it = m_tPhysicsEngineEntityVector.begin();
          it != m_tPhysicsEngineEntityVector.end() && bNoCollision; ++it) {
         if(! (*it)->MoveTo(c_position, c_orientation, b_check_only)) {
            bNoCollision = false;
         }
      }
      if(bNoCollision && !b_check_only) {
         /* Update space position */
         SetPosition(c_position);
         SetOrientation(c_orientation);
         return true;
      }
      else {
         /* No Collision or check only, undo changes */
         for(TPhysicsEngineEntityVector::const_iterator it = m_tPhysicsEngineEntityVector.begin();
             it != m_tPhysicsEngineEntityVector.end(); ++it) {
            (*it)->MoveTo(GetPosition(), GetOrientation());
         }
         if(!bNoCollision) {
            /* Collision */
            return false;
         }
         else {
            /* No collision, it was a check-only */
            return true;
         }
      }
   }

   /****************************************/
   /****************************************/

   void CalculateBoundingBoxFromHalfSize(CEmbodiedEntity::SBoundingBox& s_bounding_box,
                                         const CVector3& c_half_size,
                                         const CVector3& c_center_pos,
                                         const CMatrix3x3& c_orientation) {
      CVector3 cExtent(Abs(c_orientation(0) * c_half_size.GetX()) +
                       Abs(c_orientation(1) * c_half_size.GetY()) +
                       Abs(c_orientation(2) * c_half_size.GetZ()),
                       Abs(c_orientation(3) * c_half_size.GetX()) +
                       Abs(c_orientation(4) * c_half_size.GetY()) +
                       Abs(c_orientation(5) * c_half_size.GetZ()),
                       Abs(c_orientation(6) * c_half_size.GetX()) +
                       Abs(c_orientation(7) * c_half_size.GetY()) +
                       Abs(c_orientation(8) * c_half_size.GetZ()));
      s_bounding_box.MinCorner =  c_center_pos;
      s_bounding_box.MinCorner -= cExtent;
      s_bounding_box.MaxCorner =  c_center_pos;
      s_bounding_box.MaxCorner += cExtent;
   }

   /****************************************/
   /****************************************/

   void CEmbodiedEntitySpaceHashUpdater::operator()(CAbstractSpaceHash<CEmbodiedEntity>& c_space_hash,
                                                    CEmbodiedEntity& c_element) {
      /* Update the bounding box */
      c_element.UpdateBoundingBox();
      /* Translate the min corner of the bounding box into the map's coordinate */
      c_space_hash.SpaceToHashTable(m_nMinX, m_nMinY, m_nMinZ, c_element.GetBoundingBox().MinCorner);
      /* Translate the max corner of the bounding box into the map's coordinate */                                     
      c_space_hash.SpaceToHashTable(m_nMaxX, m_nMaxY, m_nMaxZ, c_element.GetBoundingBox().MaxCorner);
      /* Finally, go through the affected cells and update them */
      for(SInt32 nK = m_nMinZ; nK <= m_nMaxZ; ++nK) {
         for(SInt32 nJ = m_nMinY; nJ <= m_nMaxY; ++nJ) {
            for(SInt32 nI = m_nMinX; nI <= m_nMaxX; ++nI) {
               c_space_hash.UpdateCell(nI, nJ, nK, c_element);
            }
         }
      }
   }

   /****************************************/
   /****************************************/

}

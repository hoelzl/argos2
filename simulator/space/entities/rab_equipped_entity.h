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
 * @file <argos2/simulator/space/entities/rab_equipped_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef RAB_EQUIPPED_ENTITY_H
#define RAB_EQUIPPED_ENTITY_H

#include <argos2/simulator/space/entities/entity.h>
#include <argos2/common/utility/math/vector3.h>

namespace argos {

   template <SInt32 MSG_SIZE> class CRABEquippedEntity : public CEntity {

   public:

      CRABEquippedEntity(CEntity* pc_parent) :
         CEntity(pc_parent),
         m_fRange(0.0f) {
         bool bFound = false;
         size_t i = 0;
         while(!bFound && i < AVAILABLE_IDS.size()) {
            if(AVAILABLE_IDS[i]) {
               m_unNumericId = i;
               AVAILABLE_IDS[i] = 0;
               bFound = true;
            }
            else {
               ++i;
            }
         }         
         if(!bFound) {
            THROW_ARGOSEXCEPTION("The total amount of range and bearing devices cannot be more than 65535.");
         }
         ::memset(m_punData, 0, MSG_SIZE);
      }
      virtual ~CRABEquippedEntity() {
         /* Mark the ID as available */
         AVAILABLE_IDS[m_unNumericId] = 1;
      }

      virtual void Reset() {
         ::memset(m_punData, 0, MSG_SIZE);
      }

      inline const CVector3& GetPosition() const {
         return m_cPosition;
      }

      inline void SetPosition(const CVector3& c_position) {
         m_cPosition = c_position;
      }

      inline void GetData(UInt8* pun_data) const {
         ::memcpy(pun_data, m_punData, MSG_SIZE);
      }

      inline void SetData(const UInt8* pun_data) {
         ::memcpy(m_punData, pun_data, MSG_SIZE);
      }

      inline Real GetRange() const {
         return m_fRange;
      }

      inline void SetRange(Real f_range) {
         m_fRange = f_range;
      }

      inline UInt16 GetNumericId() const {
         return m_unNumericId;
      }

      inline void ClearData() {
         ::memset(m_punData, 0, MSG_SIZE);
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "rab_equipped_entity<" + ToString(MSG_SIZE) + ">";
      }

   protected:

      CVector3 m_cPosition;
      UInt8 m_punData[MSG_SIZE];
      Real m_fRange;
      UInt16 m_unNumericId;

   private:

      static std::vector<UInt16> AVAILABLE_IDS;

   };

   template <SInt32 MSG_SIZE> std::vector<UInt16> CRABEquippedEntity<MSG_SIZE>::AVAILABLE_IDS(65535, 1);

}

#endif

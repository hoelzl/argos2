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
 * @file <argos2/simulator/space/entities/led_equipped_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef LED_EQUIPPED_ENTITY_H
#define LED_EQUIPPED_ENTITY_H

namespace argos {
   class CLedEquippedEntity;
   class CLedEntity;
}

#include <argos2/simulator/space/entities/led_entity.h>

namespace argos {

   class CLedEquippedEntity : public CEntity {

   public:

      CLedEquippedEntity(CEntity* pc_parent) :
         CEntity(pc_parent) {}
      virtual ~CLedEquippedEntity();

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Reset();

      inline void AddLed(const CVector3& c_position, const CColor& c_color = CColor::BLACK)
      {
         m_tLeds.push_back(new CLedEntity(this, c_position, c_color));
      }

      inline CLedEntity& GetLED(UInt32 un_index)
      {
         ARGOS_ASSERT(un_index < m_tLeds.size(),
                      "LED index out of bounds: un_index = " <<
                      un_index <<
                      ", m_tLEDs.size() = " <<
                      m_tLeds.size());
         return *m_tLeds[un_index];
      }

      inline TLedEntityList& GetAllLeds()
      {
         return m_tLeds;
      }

      inline void SetLedPosition(UInt32 un_index, const CVector3& c_position)
      {
         ARGOS_ASSERT(un_index < m_tLeds.size(),
                      "LED index out of bounds: un_index = " <<
                      un_index <<
                      ", m_tLEDs.size() = " <<
                      m_tLeds.size());
         m_tLeds[un_index]->SetPosition(c_position);
      }

      inline void SetLedColor(UInt32 un_index,
                              const CColor& c_color) {
         ARGOS_ASSERT(un_index < m_tLeds.size(),
                      "LED index out of bounds: un_index = " <<
                      un_index <<
                      ", m_tLEDs.size() = " <<
                      m_tLeds.size());
         m_tLeds[un_index]->SetColor(c_color);
      }

      inline void SetAllLedsColors(const std::vector<CColor>& vec_colors)
      {
         for(UInt32 i = 0; i < vec_colors.size(); ++i) {
            m_tLeds[i]->SetColor(vec_colors[i]);
         }
      }

      inline virtual void Accept(CEntityVisitor& visitor)
      {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const
      {
         return "led_equipped_entity";
      }

   protected:

      TLedEntityList m_tLeds;

   };

   typedef std::map<std::string, CLedEquippedEntity*> TLedEquippedEntityMap;

}

#endif

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
 * @file <argos2/simulator/space/entities/light_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef LIGHT_ENTITY_H
#define LIGHT_ENTITY_H

namespace argos {
   class CLightEntity;
   class CLedEquippedEntity;
}

#include <argos2/simulator/space/entities/positional_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>

namespace argos {

   class CLightEntity : public CPositionalEntity {

   public:

      CLightEntity();
      virtual ~CLightEntity() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      CLedEquippedEntity& GetLEDEquippedEntity() {
         return m_cLEDEquippedEntity;
      }

      CLedEntity& GetLEDEntity() {
         return m_cLEDEquippedEntity.GetLED(0);
      }

      inline virtual void SetPosition(const CVector3& c_position) {
         CPositionalEntity::SetPosition(c_position);
         m_cLEDEquippedEntity.SetLedPosition(0, c_position);
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "light_entity";
      }

      inline Real GetIntensity() const {
         return m_fIntensity;
      }

      inline void SetIntensity(Real f_intensity) {
         m_fIntensity = f_intensity;
      }

   protected:

      CLedEquippedEntity m_cLEDEquippedEntity;
      Real m_fIntensity;
      CColor m_cColor;

   };

}

#endif

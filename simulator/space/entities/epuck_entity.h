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
 * @file <simulator/space/entities/epuck_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EPUCK_ENTITY_H
#define EPUCK_ENTITY_H

namespace argos {
   class CEPuckEntity;
   class CEmbodiedEntity;
   class CControllableEntity;
   class CLedEquippedEntity;
   class CGripperEquippedEntity;
   class CDistanceScannerEquippedEntity;
   class CQuaternion;
}

#include <argos2/simulator/space/entities/composable_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>
#include <argos2/simulator/space/entities/wheeled_entity.h>
#include <argos2/simulator/space/entities/rab_equipped_entity.h>

namespace argos {

   class CEPuckEntity : public CComposableEntity {

   public:

      CEPuckEntity();
      virtual ~CEPuckEntity();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual CEntity& GetComponent(const std::string& str_component);
      virtual bool HasComponent(const std::string& str_component);

      virtual void UpdateComponents();
      
      inline CEmbodiedEntity& GetEmbodiedEntity() {
         return *m_pcEmbodiedEntity;
      }

      inline CControllableEntity& GetControllableEntity() {
         return *m_pcControllableEntity;
      }

      inline CWheeledEntity<2>& GetWheeledEntity() {
         return *m_pcWheeledEntity;
      }

      inline CLedEquippedEntity& GetLEDEquippedEntity() {
         return *m_pcLEDEquippedEntity;
      }

      inline CRABEquippedEntity<2>& GetRABEquippedEntity() {
         return *m_pcRABEquippedEntity;
      }

      inline virtual std::string GetTypeDescription() const {
         return "epuck_entity";
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
          visitor.Visit(*this);
      }

   private:

      void SetLedPosition();

   private:

      CEmbodiedEntity*                m_pcEmbodiedEntity;
      CControllableEntity*            m_pcControllableEntity;
      CWheeledEntity<2>*              m_pcWheeledEntity;
      CLedEquippedEntity*             m_pcLEDEquippedEntity;
      CRABEquippedEntity<2>*          m_pcRABEquippedEntity;

   };

}

#endif

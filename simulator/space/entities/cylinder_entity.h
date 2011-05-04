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
 * @file <simulator/space/entities/cylinder_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Giovanni Pini - <gpini@ulb.ac.be>
 */

#ifndef CYLINDER_ENTITY_H
#define CYLINDER_ENTITY_H

namespace argos {
   class CCylinderEntity;
   class CEmbodiedEntity;
   class CLedEquippedEntity;
}

#include <argos2/simulator/space/entities/composable_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>
#include <argos2/common/utility/math/matrix3x3.h>

namespace argos {

   class CCylinderEntity : public CComposableEntity {

   public:

      CCylinderEntity();
      virtual ~CCylinderEntity();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual CEntity& GetComponent(const std::string& str_component);
      virtual bool HasComponent(const std::string& str_component);

      virtual void UpdateComponents();

      inline CEmbodiedEntity& GetEmbodiedEntity() {
         return *m_pcEmbodiedEntity;
      }

      inline CLedEquippedEntity& GetLEDEquippedEntity() {
         return *m_pcLEDEquippedEntity;
      }

      inline Real GetRadius() const {
         return m_fRadius;
      }

      inline void SetRadius(Real c_radius) {
         m_fRadius = c_radius;
      }

      inline Real GetHeight() const {
         return m_fHeight;
      }

      inline void SetHeight(Real c_height) {
         m_fHeight = c_height;
      }

      inline Real GetMass() const {
         return m_fMass;
      }

      inline void SetMass(Real f_mass) {
         m_fMass = f_mass;
      }

      inline bool IsMovable() const {
         return m_bMovable;
      }

      inline bool IsVisible() const {
         return m_bVisible;
      }

      inline virtual std::string GetTypeDescription() const {
         return "cylinder_entity";
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

   private:

      CEmbodiedEntity*      m_pcEmbodiedEntity;
      CLedEquippedEntity*   m_pcLEDEquippedEntity;
      std::vector<CVector3> m_vecBaseLEDPositions;
      Real                  m_fRadius;
      Real                  m_fHeight;
      Real                  m_fMass;
      bool                  m_bMovable;
      bool                  m_bVisible;

   };

}

#endif

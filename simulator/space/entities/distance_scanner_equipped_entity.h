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
 * @file <argos2/simulator/space/entities/distance_scanner_equipped_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef DISTANCE_SCANNER_EQUIPPED_ENTITY_H
#define DISTANCE_SCANNER_EQUIPPED_ENTITY_H

namespace argos {
   class CDistanceScannerEquippedEntity;
}

#include <argos2/simulator/space/entities/entity.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/common/utility/math/ray.h>

// DEBUG
#include <argos2/common/utility/logging/argos_log.h>

namespace argos {
   class CDistanceScannerEquippedEntity : public CEntity {

   public:

      enum EMode {
         MODE_OFF,
         MODE_POSITION_CONTROL,
         MODE_SPEED_CONTROL
      };

   public:

      CDistanceScannerEquippedEntity(CEntity* pc_parent);
      virtual ~CDistanceScannerEquippedEntity() {}

      virtual void Reset();

      inline UInt32 GetMode() const {
         return m_unMode;
      }

      inline void SetMode(UInt32 un_mode) {
         m_unMode = un_mode;
      }

      inline const CRadians& GetRotation() const {
         return m_cRotation;
      }

      inline void SetRotation(const CRadians& c_rotation) {
         m_cRotation = c_rotation;
         m_cRotation.UnsignedNormalize();
         LOGERR << "m_cRotation = " << m_cRotation << std::endl;
      }

      inline Real GetRotationSpeed() const {
         return m_fRotationSpeed;
      }

      inline void SetRotationSpeed(Real f_speed) {
         m_fRotationSpeed = f_speed;
      }

      void UpdateRotation();

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "distance_scanner_equipped_entity";
      }

   private:

      UInt32 m_unMode;
      CRadians m_cRotation;
      Real m_fRotationSpeed;

   };
}

#endif

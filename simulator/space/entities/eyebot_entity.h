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
 * @file <simulator/space/entities/eyebot_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EYEBOT_ENTITY_H
#define EYEBOT_ENTITY_H

namespace argos {
   class CEyeBotEntity;
   class CEmbodiedEntity;
   class CControllableEntity;
   class CLedEquippedEntity;
   class CDistanceScannerEquippedEntity;
   class CQuaternion;
}

#include <argos2/simulator/space/entities/composable_entity.h>
#include <argos2/simulator/space/entities/rab_equipped_entity.h>

namespace argos {

   class CEyeBotEntity : public CComposableEntity {

   public:

      struct SMotionData {
         enum EMotionSource {
            MOTION_FROM_FORCES = 0,
            MOTION_FROM_SPEEDS = 1
         } Source;
         union {
            struct {
               Real ForceX, ForceY, ForceZ;
            };
            struct {
               Real LinearSpeed, AngularSpeed;
            };
         };

         SMotionData() :
            Source(MOTION_FROM_FORCES) {
            ForceX = 0.0f;
            ForceY = 0.0f;
            ForceZ = 0.0f;
         }

         SMotionData(const SMotionData& s_data) :
            Source(s_data.Source) {
            if(Source == MOTION_FROM_FORCES) {
               ForceX = s_data.ForceX;
               ForceY = s_data.ForceY;
               ForceZ = s_data.ForceZ;
            }
            else {
               LinearSpeed = s_data.LinearSpeed;
               AngularSpeed = s_data.AngularSpeed;
            }
         }

         SMotionData& operator=(const SMotionData& s_data) {
            if(&s_data != this) {
               Source = s_data.Source;
               if(Source == MOTION_FROM_FORCES) {
                  ForceX = s_data.ForceX;
                  ForceY = s_data.ForceY;
                  ForceZ = s_data.ForceZ;
               }
               else {
                  LinearSpeed = s_data.LinearSpeed;
                  AngularSpeed = s_data.AngularSpeed;
               }
            }
            return *this;
         }
      };

      CEyeBotEntity();
      virtual ~CEyeBotEntity();

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

      inline CLedEquippedEntity& GetLEDEquippedEntity() {
         return *m_pcLEDEquippedEntity;
      }

      inline CDistanceScannerEquippedEntity& GetDistanceScannerEquippedEntity() {
         return *m_pcDistanceScannerEquippedEntity;
      }

      inline CRABEquippedEntity<10>& GetRABEquippedEntity() {
         return *m_pcRABEquippedEntity;
      }

      inline bool IsAttachedToCeiling() const {
         return m_bAttachedToCeiling;
      }

      inline bool IsDetachedFromCeiling() const {
         return !m_bAttachedToCeiling;
      }

      inline void SetAttachedToCeiling(bool b_attached) {
         m_bAttachedToCeiling = b_attached;
      }

      inline const SMotionData& GetMotionData() const {
         return m_sMotionData;
      }

      inline void SetMotionData(const SMotionData& s_data) {
         m_sMotionData = s_data;
      }

      inline Real GetTargetAltitude() const {
         return m_fTargetAltitude;
      }

      inline void SetTargetAltitude(Real f_altitude) {
         m_fTargetAltitude = f_altitude;
      }

      inline virtual std::string GetTypeDescription() const {
         return "eyebot_entity";
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
          visitor.Visit(*this);
      }

   private:

      void SetLedPosition();

   private:

      CEmbodiedEntity*                m_pcEmbodiedEntity;
      CControllableEntity*            m_pcControllableEntity;
      CLedEquippedEntity*             m_pcLEDEquippedEntity;
      CDistanceScannerEquippedEntity* m_pcDistanceScannerEquippedEntity;
      CRABEquippedEntity<10>*         m_pcRABEquippedEntity;
      bool                            m_bAttachedToCeiling;
      SMotionData                     m_sMotionData;
      Real                            m_fTargetAltitude;

   };

}

#endif

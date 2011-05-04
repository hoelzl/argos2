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
 * @file <simulator/space/entities/footbot_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_ENTITY_H
#define FOOTBOT_ENTITY_H

namespace argos {
   class CFootBotEntity;
   class CEmbodiedEntity;
   class CControllableEntity;
   class CLedEquippedEntity;
   class CGripperEquippedEntity;
   class CDistanceScannerEquippedEntity;
   class CQuaternion;
}

#include <argos2/simulator/space/entities/composable_entity.h>
#include <argos2/simulator/space/entities/gripper_equipped_entity.h>
#include <argos2/simulator/space/entities/rab_equipped_entity.h>
#include <argos2/simulator/space/entities/distance_scanner_equipped_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>
#include <argos2/simulator/space/entities/wheeled_entity.h>
#include <argos2/simulator/space/entities/wifi_equipped_entity.h>

namespace argos {

   class CFootBotEntity : public CComposableEntity {

   public:

      CFootBotEntity();
      virtual ~CFootBotEntity();

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

      inline CGripperEquippedEntity& GetGripperEquippedEntity() {
         return *m_pcGripperEquippedEntity;
      }

      inline CDistanceScannerEquippedEntity& GetDistanceScannerEquippedEntity() {
         return *m_pcDistanceScannerEquippedEntity;
      }

      inline CRABEquippedEntity<10>& GetRABEquippedEntity() {
         return *m_pcRABEquippedEntity;
      }

      inline CWiFiEquippedEntity& GetWiFiEquippedEntity() {
         return *m_pcWiFiEquippedEntity;
      }

      inline const CRadians& GetTurretRotation() const {
         return m_cTurretRotation;
      }

      inline void SetTurretRotation(const CRadians& c_rotation) {
         m_cTurretRotation = c_rotation;
      }

      inline Real GetTurretRotationSpeed() const {
         return m_fTurretRotationSpeed;
      }

      inline void SetTurretRotationSpeed(Real f_speed) {
         m_fTurretRotationSpeed = f_speed;
      }

      inline UInt8 GetTurretMode() const {
         return m_unTurretMode;
      }

      inline void SetTurretMode(UInt8 un_mode) {
         m_unTurretMode = un_mode;
      }

      inline virtual std::string GetTypeDescription() const {
         return "footbot_entity";
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
      CGripperEquippedEntity*         m_pcGripperEquippedEntity;
      CDistanceScannerEquippedEntity* m_pcDistanceScannerEquippedEntity;
      CRABEquippedEntity<10>*         m_pcRABEquippedEntity;
      CWiFiEquippedEntity*            m_pcWiFiEquippedEntity;

      CRadians                        m_cTurretRotation;
      Real                            m_fTurretRotationSpeed;
      UInt8                           m_unTurretMode;

   };

}

#endif

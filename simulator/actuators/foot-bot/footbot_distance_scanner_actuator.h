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
 * @file <argos2/simulator/actuators/foot-bot/footbot_distance_scanner_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_DISTANCE_SCANNER_ACTUATOR_H
#define FOOTBOT_DISTANCE_SCANNER_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotDistanceScannerActuator;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_distance_scanner_actuator.h>
#include <argos2/simulator/actuators/foot-bot/footbot_actuator.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/distance_scanner_equipped_entity.h>

namespace argos {

   class CFootBotDistanceScannerActuator : public CFootBotActuator,
                                           public CCI_FootBotDistanceScannerActuator {

   public:

  	  static const Real RPM_TO_RADIANS_PER_SEC;

      CFootBotDistanceScannerActuator();
      virtual ~CFootBotDistanceScannerActuator() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotActuator::SetEntity(c_entity);
         m_pcDistanceScannerEquippedEntity = &(GetEntity().GetDistanceScannerEquippedEntity());
      }

      inline virtual void SetAngle(const CRadians& c_angle) {
         m_unDesiredMode = CDistanceScannerEquippedEntity::MODE_POSITION_CONTROL;
         m_cDesiredRotation = c_angle;
      }

      inline virtual void SetRPM(Real f_rpm) {
         m_unDesiredMode = CDistanceScannerEquippedEntity::MODE_SPEED_CONTROL;
         m_fDesiredRotationSpeed = f_rpm * RPM_TO_RADIANS_PER_SEC;
      }

      inline virtual void Enable() {
         m_unDesiredMode = CDistanceScannerEquippedEntity::MODE_POSITION_CONTROL;
      }

      inline virtual void Disable() {
         m_unDesiredMode = CDistanceScannerEquippedEntity::MODE_OFF;
      }

      virtual void Update();
      virtual void Reset();

   private:

      CDistanceScannerEquippedEntity* m_pcDistanceScannerEquippedEntity;

      CRadians m_cDesiredRotation;
      Real     m_fDesiredRotationSpeed;
      UInt8    m_unDesiredMode;

   };

}

#endif

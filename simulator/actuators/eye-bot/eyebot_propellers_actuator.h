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
 * @file <argos2/simulator/actuators/eye-bot/eyebot_propellers_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EYEBOT_PROPELLERS_ACTUATOR_H
#define EYEBOT_PROPELLERS_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEyeBotPropellersActuator;
}

#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_propellers_actuator.h>
#include <argos2/simulator/actuators/eye-bot/eyebot_actuator.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>

namespace argos {

   class CEyeBotPropellersActuator : public CEyeBotActuator,
                                     public CCI_EyeBotPropellersActuator {

   public:

      CEyeBotPropellersActuator();
      virtual ~CEyeBotPropellersActuator() {}

      virtual void Init(TConfigurationNode& t_tree) {}
      virtual void Destroy() {}

      inline virtual void SetVelocity(Real f_linear_velocity,
                                      Real f_angular_velocity) {
         m_sDesiredMotionData.Source = CEyeBotEntity::SMotionData::MOTION_FROM_SPEEDS;
         m_sDesiredMotionData.LinearSpeed = f_linear_velocity;
         m_sDesiredMotionData.AngularSpeed = f_angular_velocity;
      }

      inline virtual void SetForce(Real f_pitch_force,
                                   Real f_roll_force,
                                   Real f_thrust_force) {
         m_sDesiredMotionData.Source = CEyeBotEntity::SMotionData::MOTION_FROM_FORCES;
         m_sDesiredMotionData.ForceX = f_pitch_force;
         m_sDesiredMotionData.ForceY = f_roll_force;
         m_sDesiredMotionData.ForceZ = f_thrust_force;
      }
      
      inline virtual void SetYawRotation (Real f_yaw_rotation) {}

      inline virtual void AttachToCeiling() {
         m_bDesiredAttachedToCeiling = true;
      }

      inline virtual void DetachFromCeiling() {
         m_bDesiredAttachedToCeiling = false;
      }

      virtual void SetDesiredAltitude(Real f_altitude) {
         m_fDesiredAltitude = f_altitude;
      }

      virtual void Update();
      virtual void Reset();

   private:

      bool                       m_bDesiredAttachedToCeiling;
      CEyeBotEntity::SMotionData m_sDesiredMotionData;
      Real                       m_fDesiredAltitude;

   };

}

#endif

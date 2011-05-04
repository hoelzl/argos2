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
 * @file <common/control_interface/eyebot/ci_eyebot_propellers_actuator.h>
 *
 * @brief This file provides the definition of the eyebot propellers actuator.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef CI_EYEBOT_PROPELLERS_ACTUATOR_H
#define CI_EYEBOT_PROPELLERS_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EyeBotPropellersActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

   class CCI_EyeBotPropellersActuator: virtual public CCI_Actuator {

   public:

      /**
       * @brief Set the linear velocity of the Eyebot.
       *
       * @param f_linear_velocity The linear speed of the eyebot (m/s).
       **/
      virtual void SetVelocity(Real f_linear_velocity,
                               Real f_angular_velocity) = 0;

      /**
       * @brief Set the roll, pitch and upthrust of the Eyebot.
       *
       * @param f_pitch_force  Desired Pitch force
       * @param f_roll_force  Desired Roll force
       * @param f_thrust_force  Desired upwards thrust force
       **/
      virtual void SetForce(Real f_pitch_force,
                            Real f_roll_force,
                            Real f_thrust_force) = 0;
 
      /**
       * @brief Set the Yaw rotation of the Eyebot.
       *
       * @param f_yaw_rotation The desired yaw rotation fo the Eyebot
       **/
      virtual void SetYawRotation (Real f_yaw_rotation) = 0;

      virtual void AttachToCeiling() = 0;
      virtual void DetachFromCeiling() = 0;

      virtual void SetDesiredAltitude(Real f_altitude) = 0;

   };



};

#endif

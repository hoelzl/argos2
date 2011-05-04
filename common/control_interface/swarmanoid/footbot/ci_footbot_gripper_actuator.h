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
 * @file <common/control_interface/footbot/ci_footbot_gripper_actuator.h>
 *
 * @brief This file provides the definition of the gripper actuator.

 * This file provides the definition of the gripper actuator. It allows
 * to set the gripper aperture in the range [-pi/2:pi/2]. The gripper
 * can be locked in two directions: positive and negative. In the negative
 * direction the 2 side pins of the gripper move upwards and the middle pin
 * downwards.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_GRIPPER_ACTUATOR_H
#define CCI_FOOTBOT_GRIPPER_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_FootBotGripperActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>
#include <argos2/common/utility/math/angles.h>

namespace argos {

   class CCI_FootBotGripperActuator : virtual public CCI_Actuator {

   public:

      /* Useful gripper aperture values */
      static CRadians UNLOCKED;
      static CRadians LOCKED_POSITIVE;
      static CRadians LOCKED_NEGATIVE;

      /**
       * @brief Constructor.
       */
      CCI_FootBotGripperActuator() {}

      /**
       * @brief Destructor.
       */
      virtual ~CCI_FootBotGripperActuator() {}

      /**
       * @brief Sets gripper aperture in radians.
       *
       * @param c_aperture desired aperture.
       */
      virtual void SetAperture(const CRadians& c_aperture) = 0;

      /**
       * @brief Sets gripper aperture to lock, positive direction.
       */
      inline virtual void LockPositive() {
         SetAperture(LOCKED_POSITIVE);
      }

      /**
       * @brief Sets gripper aperture to lock, negative direction.
       */
      inline virtual void LockNegative() {
         SetAperture(LOCKED_NEGATIVE);
      }

      /**
       * @brief Unlock gripper: objects are released.
       */
      inline virtual void Unlock() {
         SetAperture(UNLOCKED);
      }

   };

}

#endif

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
 * @file <common/control_interface/swarmanoid/handbot/ci_handbot_arms_actuator.h>
 *
 * @brief This file provides the definition of the common interface to the
 *        handbot arms actuators (head, arms and grippers).
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#ifndef CCI_HANDBOT_ARMS_ACTUATOR_H
#define CCI_HANDBOT_ARMS_ACTUATOR_H

namespace argos {
   class CCI_HandBotArmsActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>
#include <argos2/common/utility/math/angles.h>

namespace argos {

   class CCI_HandBotArmsActuator : public CCI_Actuator {

   public:

      static const CRadians ARM_RETRACTED;
      static const CRadians ARM_EXTENDED;
      static const CRadians WRIST_STRAIGHT;
      static const CRadians WRIST_PERPENDICULAR;
      static const CRadians GRIPPER_OPEN;
      static const CRadians GRIPPER_CLOSED;

      CCI_HandBotArmsActuator(): m_bIsHandBotClimbingShelf(false) {
      }

      virtual ~CCI_HandBotArmsActuator() {
      }

      virtual void SetHeadRotation(const CRadians& c_rotation) = 0;

      virtual void SetLeftArmAperture(const CRadians& c_aperture) = 0;
      virtual void SetRightArmAperture(const CRadians& c_aperture) = 0;
      inline virtual void SetArmsAperture(const CRadians& c_left_aperture,
                                          const CRadians& c_right_aperture) {
         SetLeftArmAperture(c_left_aperture);
         SetRightArmAperture(c_right_aperture);
      }

      virtual void SetLeftGripperRotation(const CRadians& c_rotation) = 0;
      virtual void SetRightGripperRotation(const CRadians& c_rotation) = 0;
      inline virtual void SetGrippersRotation(const CRadians& c_left_rotation,
                                              const CRadians& c_right_rotation) {
         SetLeftGripperRotation(c_left_rotation);
         SetRightGripperRotation(c_right_rotation);
      }

      virtual void SetLeftGripperAperture(const CRadians& c_aperture) = 0;
      virtual void SetRightGripperAperture(const CRadians& c_aperture) = 0;
      inline virtual void SetGrippersAperture(const CRadians& c_left_aperture,
                                              const CRadians& c_right_aperture) {
         SetLeftGripperAperture(c_left_aperture);
         SetRightGripperAperture(c_right_aperture);
      }

      inline bool IsHandBotClimbing() {
          return m_bIsHandBotClimbingShelf;
      }

   protected:

      // Conversion factors from motor positions to handbot part angle
      static const Real ANGLE_TO_PID_HEAD_ROTATION;
      static const Real ANGLE_TO_PID_ARMS_APERTURE;
      static const Real ANGLE_TO_PID_GRIPPER_APERTURE;
      static const Real ANGLE_TO_PID_GRIPPER_ROTATION;

      /* When true the arms actuators do not take commands from the controller */
      bool m_bIsHandBotClimbingShelf;

      friend class CCI_HandbotArmEncodersSensor;
      friend class CRealHandBotArmEncodersSensor;

   };

}

#endif

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
 * @file <common/control_interface/handbot/ci_handbot_arm_encoders_sensor.h>
 *
 * @brief This file provides the definition of the handbot arms encoders sensor.
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#ifndef CCI_HANDBOT_ARM_ENCODERS_SENSOR_H
#define CCI_HANDBOT_ARM_ENCODERS_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_HandBotArmEncodersSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/control_interface/swarmanoid/handbot/ci_handbot_arms_actuator.h>
#include <argos2/common/utility/math/angles.h>

namespace argos {

   class CCI_HandBotArmEncodersSensor : public CCI_Sensor {

   public:

      struct SHandReading {
         CRadians Left;
         CRadians Right;

         SHandReading() {
         }

         SHandReading(const CRadians& c_left, const CRadians& c_right) :
            Left(c_left), Right(c_right) {
         }
      };

      struct TReading {
         CRadians HeadRotation;
         SHandReading ArmAperture;
         SHandReading GripperRotation;
         SHandReading GripperAperture;
      };

      virtual ~CCI_HandBotArmEncodersSensor() {
      }

      inline virtual const TReading& GetAllReadings() const {
         return m_tReading;
      }

      inline virtual const CRadians& GetHeadRotation() const {
         return m_tReading.HeadRotation;
      }

      inline virtual const CRadians& GetLeftArmAperture() const {
         return m_tReading.ArmAperture.Left;
      }

      inline virtual const CRadians& GetRightArmAperture() const {
         return m_tReading.ArmAperture.Right;
      }

      inline virtual const CRadians& GetLeftGripperRotation() const {
         return m_tReading.GripperRotation.Left;
      }

      inline virtual const CRadians& GetRightGripperRotation() const {
         return m_tReading.GripperRotation.Right;
      }

      inline virtual const CRadians& GetLeftGripperAperture() const {
         return m_tReading.GripperAperture.Left;
      }

      inline virtual const CRadians& GetRightGripperAperture() const {
         return m_tReading.GripperAperture.Right;
      }

   protected:

      TReading m_tReading;

   };

}

#endif

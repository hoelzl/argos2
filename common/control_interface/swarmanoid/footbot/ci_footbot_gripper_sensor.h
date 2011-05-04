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
 * @file <common/control_interface/swarmanoid/footbot/ci_footbot_gripper_sensor.h>
 *
 * @brief This file provides the common interface  definition of the gripper sensor.
 *
 * This file provides the common interface  definition of the gripper sensor.
 * The sensor measures the current gripper aperture, in the future it will also
 * integrate functions to query the fact that an object is currently gripped
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_GRIPPER_SENSOR_H
#define CCI_FOOTBOT_GRIPPER_SENSOR_H

namespace argos {
   class CCI_FootBotGripperSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>

namespace argos {

   class CCI_FootBotGripperSensor: public CCI_Sensor {

   public:


      enum EGripPhase {
         OBJECT_NOT_GRIPPED = 0,
         CHECK_IN_PROGRESS,
         OBJECT_GRIPPED
      };

      struct SReading {
         CRadians GripperAperture;
         bool ObjectInGripper;

         SReading() :
            GripperAperture(0.0),
            ObjectInGripper(false) {
         }

         SReading(const CRadians& GripperAperture,
                  bool b_object_in_gripper) :
            GripperAperture(GripperAperture),
            ObjectInGripper(b_object_in_gripper) {
         }

      };

      CCI_FootBotGripperSensor() :
         m_eGripPhase(OBJECT_NOT_GRIPPED) {}

			virtual ~CCI_FootBotGripperSensor() {}

      inline virtual const SReading& GetReading() const {
         return m_sReading;
      }

			inline virtual bool IsObjectInGripper() const {
         return m_sReading.ObjectInGripper;
      }

			inline virtual EGripPhase GetGripPhase() const {
         return m_eGripPhase;
      }

   protected:

      SReading m_sReading;
      EGripPhase m_eGripPhase;
   };

}

#endif

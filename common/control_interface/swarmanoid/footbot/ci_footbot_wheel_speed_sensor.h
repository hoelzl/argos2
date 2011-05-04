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
 * @file <common/control_interface/footbot/ci_footbot_wheel_speed_sensor.h>
 *
 * @brief This file provides the definition of the wheel speed sensor.
 *
 * This file provides the definition of the wheel speed sensor.
 * This sensor returns the current actual speed of the wheels as measured by
 * the sensors present on the robot. The return value is expressed in
 * cm/s and correspond to a linear velocity. For a more detailed explanation
 * of these concepts, see the footbot wheels actuator.
 *
 * @author Carlo Pinciroli - <cpinciro@iridia.ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_WHEEL_SPEED_SENSOR_H
#define CCI_FOOTBOT_WHEEL_SPEED_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_FootBotWheelSpeedSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>

namespace argos {

   class CCI_FootBotWheelSpeedSensor : public CCI_Sensor {

   public:

      struct TReading {
         Real LinearVelocityLeft;
         Real LinearVelocityRight;

         TReading(Real f_linear_velocity_left, Real f_linear_velocity_right) :
            LinearVelocityLeft(f_linear_velocity_left),
            LinearVelocityRight(f_linear_velocity_right) {
         }
      };

      CCI_FootBotWheelSpeedSensor() :
         m_tReading(0.0, 0.0) {
      }

      virtual ~CCI_FootBotWheelSpeedSensor() {
      }

      inline virtual const TReading& GetReading() const {
         return m_tReading;
      }

   protected:

      TReading m_tReading;
   };
}

#endif

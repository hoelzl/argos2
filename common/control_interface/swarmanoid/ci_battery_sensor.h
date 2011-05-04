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
 * @file <common/control_interface/argos/ci_battery_sensor.h>
 *
 * @brief This file provides the definition of the generic battery sensor
 * interface for all argos robots.
 *
 * The battery sensor gives information about the battery, such as the current
 * voltage in volts. At the moment, only the current voltage value is available
 * from the sensor. Plese note that the MinValue() and MaxValue() functions
 * define the total possible range (0-10V), while a robot-specific MinSafeValue()
 * defines the voltage up to which it's safe to operate the robot. Below
 * this value, the robot should be stopped and the battery be swapped.
 *
 * @author Arne Brutschy <arne.brutschy@ulb.ac.be>
 */

#ifndef CCI_BATTERY_SENSOR_H
#define CCI_BATTERY_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_BatterySensor;
}

#include <argos2/common/control_interface/ci_sensor.h>

namespace argos {

   class CCI_BatterySensor : public CCI_Sensor {

   public:

      virtual ~CCI_BatterySensor() {
      }

      /**
       * @brief Reads the voltage value of the battery.
       * @return voltage as a Real value.
       **/
      virtual Real GetVoltage() = 0;

      /**
       * @brief Returns the minimum voltage up to which the operation of the robot is safe.
       * @return minimum safe value (volts) as a Real value
       */
      inline Real GetMinSafeValue() const {
         return m_fMinSafeValue;
      }

   protected:

      Real m_fMinSafeValue;

      /**
       * @brief Sets the minimum voltage up to which the operation of the robot is safe.
       * This method should only be called by the robot-specific sensor implementation.
       * @param f_val minimum voltage up to which the operation of the robot is safe
       */
      inline void SetMinSafeValue(Real f_val) {
         m_fMinSafeValue = f_val;
      }
   };

}

#endif

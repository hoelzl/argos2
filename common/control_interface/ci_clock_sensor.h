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
 * @file <common/control_interface/ci_clock_sensor.h>
 *
 * @brief This file provides the definition of a clock sensor.
 *
 * The clock sensor allows the user to get the number of seconds that
 * passed since the start of the controller. Additionally, it provides
 * functions for control cycle independent counters.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.beh>
 * @author Rehan O'Grady - <rogrady@ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#ifndef CCI_CLOCK_SENSOR_H
#define CCI_CLOCK_SENSOR_H

namespace argos {
   class CCI_ClockSensor;
}

#include <string>
#include <vector>

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/logging/argos_log.h>

namespace argos {

   class CCI_ClockSensor : public CCI_Sensor {

   public:

      /**
       * Action period in progess.
       * Action period in progess.
       * @see CCI_ClockSensor::DoActionForPeriod()
       */
      static const UInt8 ACTION_PERIOD_IN_PROGRESS;

      /**
       * Action period finished.
       * Action period finished.
       * @see CCI_ClockSensor::DoActionForPeriod()
       */
      static const UInt8 ACTION_PERIOD_FINISHED;

      // Operations

   public:

      /**
       * Class destructor.
       * Class destructor.
       */
      virtual ~CCI_ClockSensor() {
      }

      /**
       * Returns the elapsed time from the time the controller was started on in seconds.
       * @return the elapsed time.
       */
      virtual Real GetElapsedTime() = 0;

      /**
       * Returns the length of the control time step in seconds.
       * @return the length of the control time step.
       */
      virtual Real GetClockTickLength() = 0;

      /**
       * Provides a time counter to execute actions for the wanted time.
       * It's a kind of Wait() function that allows to execute code for the wanted time in seconds. Before calling this method, you need to initialize the counter with
       * CCI_ClockSensor::InitialiseActionPeriodCounter(). You can reset the counter with CCI_ClockSensor::ResetActionPeriodCounter().
       * @param f_seconds The time (in seconds) to wait.
       * @param pn_current_step_buffer a buffer that stores a counter used internally.
       * @return CCI_ClockSensor::ACTION_PERIOD_FINISHED if the time to wait is expired, CCI_ClockSensor::ACTION_PERIOD_IN_PROGRESS otherwise.
       * @see CCI_ClockSensor::ACTION_PERIOD_FINISHED
       * @see CCI_ClockSensor::ACTION_PERIOD_IN_PROGRESS
       */
      inline virtual SInt32 DoActionForPeriod(Real f_seconds,
                                              SInt32* pn_current_step_buffer) {
         Real fpTimeWaitedSecs = GetClockTickLength()
                  * (Real)(*pn_current_step_buffer);

         if (f_seconds > fpTimeWaitedSecs) {
            (*pn_current_step_buffer)++;

            return CCI_ClockSensor::ACTION_PERIOD_IN_PROGRESS;
         }
         else {
            return CCI_ClockSensor::ACTION_PERIOD_FINISHED;
         }
      }

      /**
       * Initializes the counter used by DoActionForPeriod().
       * Initializes the counter used by DoActionForPeriod().
       * @param pn_current_step_buffer a buffer that stores the counter to initialize.
       */
      inline virtual void InitialiseActionPeriodCounter(SInt32* pn_current_step_buffer) {
         ResetActionPeriodCounter(pn_current_step_buffer);
      }

      /**
       * Resets (i.e. zeroes) the counter used by DoActionForPeriod().
       * Resets (i.e. zeroes) the counter used by DoActionForPeriod().
       * @param pn_current_step_buffer a buffer that stores the counter to reset.
       */
      inline virtual void ResetActionPeriodCounter(SInt32* pn_current_step_buffer) {
         *pn_current_step_buffer = 0;
      }

   };

}
;

#endif

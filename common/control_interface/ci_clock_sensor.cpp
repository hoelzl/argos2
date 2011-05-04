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
 * @file <common/control_interface/ci_clock_sensor.cpp>
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

#include "ci_clock_sensor.h"

namespace argos {

   const UInt8 CCI_ClockSensor::ACTION_PERIOD_IN_PROGRESS = -2;
   const UInt8 CCI_ClockSensor::ACTION_PERIOD_FINISHED = -3;

};

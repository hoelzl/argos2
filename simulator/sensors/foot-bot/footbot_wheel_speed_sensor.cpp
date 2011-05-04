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
 * @file <argos2/simulator/sensors/foot-bot/footbot_wheel_speed_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Giovanni Pini   - <gpini@ulb.ac.be>
 */

#include "footbot_wheel_speed_sensor.h"
#include <argos2/simulator/physics_engines/physics_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   CFootBotWheelSpeedSensor::CFootBotWheelSpeedSensor() {
   }

   /****************************************/
   /****************************************/

   void CFootBotWheelSpeedSensor::Update() {
      m_pcWheeledEntity->GetSpeed(m_fWheelSpeed);
      /* Convert speeds to cm/s*/
      m_tReading.LinearVelocityLeft  = m_fWheelSpeed[LEFT_WHEEL] * 100.0;
      m_tReading.LinearVelocityRight = m_fWheelSpeed[RIGHT_WHEEL] * 100.0;
   }

   /****************************************/
   /****************************************/

   void CFootBotWheelSpeedSensor::Reset() {
      m_tReading.LinearVelocityLeft  = 0.0f;
      m_tReading.LinearVelocityRight = 0.0f;
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CFootBotWheelSpeedSensor,
                   "footbot_wheel_speed", "default",
                   "The foot-bot wheel speed sensor",
                   "Giovanni Pini [gpini@ulb.ac.be]",
                   "This sensor accesses the foot-bot wheel sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_wheel_speed implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None for the time being.\n",
                   "Under development"
      );
   
}

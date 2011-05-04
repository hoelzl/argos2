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
 * @file <argos2/simulator/sensors/e-puck/epuck_encoder_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "epuck_encoder_sensor.h"
#include <argos2/simulator/physics_engines/physics_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   CEPuckEncoderSensor::CEPuckEncoderSensor() {
   }

   /****************************************/
   /****************************************/

   void CEPuckEncoderSensor::Update() {
      m_pcWheeledEntity->GetSpeed(m_fWheelSpeed);
      m_sReading.CoveredDistanceLeftWheel  = m_fWheelSpeed[LEFT_WHEEL] * CPhysicsEngine::GetSimulationClockTick() * 100;
      m_sReading.CoveredDistanceRightWheel = m_fWheelSpeed[RIGHT_WHEEL] * CPhysicsEngine::GetSimulationClockTick() * 100;
   }

   /****************************************/
   /****************************************/

   void CEPuckEncoderSensor::Reset() {
      m_sReading.CoveredDistanceLeftWheel  = 0.0f;
      m_sReading.CoveredDistanceRightWheel = 0.0f;
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEPuckEncoderSensor,
                   "epuck_encoder", "default",
                   "The e-puck wheel encoder sensor",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "This sensor accesses the e-puck wheel encoder sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <epuck_encoder implementation=\"default\" />\n"
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

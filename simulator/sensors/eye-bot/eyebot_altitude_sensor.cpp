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
 * @file <argos2/simulator/sensors/eye-bot/eyebot_altitude_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "eyebot_altitude_sensor.h"
#include <argos2/simulator/space/entities/embodied_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   void CEyeBotAltitudeSensor::Update() {
      m_fAltitude = GetEntity().GetEmbodiedEntity().GetPosition().GetZ();
   }

   /****************************************/
   /****************************************/

   void CEyeBotAltitudeSensor::Reset() {
      m_fAltitude = 0.0f;
   }
   
   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEyeBotAltitudeSensor,
                   "eyebot_altitude", "default",
                   "The eye-bot altitude sensor",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "This sensor returns the altitude of the eye-bot, that is its distance from the\n"
                   "floor.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <eyebot_altitude implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None.\n",
                   "Ready for use, although the sensor is currently noiseless."
      );

}

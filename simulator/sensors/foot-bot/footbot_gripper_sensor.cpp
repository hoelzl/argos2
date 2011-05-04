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
 * @file <argos2/simulator/sensors/foot-bot/footbot_gripper_sensor.cpp>
 *
 * @author Giovanni Pini - <gpini@ulb.ac.be>
 */


#include "footbot_gripper_sensor.h"
#include <argos2/simulator/physics_engines/physics_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   void CFootBotGripperSensor::Update() {
      m_sReading.GripperAperture.SetValue(m_pcGripperEquippedEntity->GetNativeLockState());
      if(m_pcGripperEquippedEntity -> IsGripping()) {
         m_sReading.ObjectInGripper = true;
         m_eGripPhase = CCI_FootBotGripperSensor::OBJECT_GRIPPED;
      }
      else {
         m_sReading.ObjectInGripper = false;
         m_eGripPhase = CCI_FootBotGripperSensor::OBJECT_NOT_GRIPPED;
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotGripperSensor::Reset() {
      m_sReading.ObjectInGripper = false;
      m_sReading.GripperAperture = CRadians::ZERO;
      m_eGripPhase = CCI_FootBotGripperSensor::OBJECT_NOT_GRIPPED;
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CFootBotGripperSensor,
                   "footbot_gripper", "default",
                   "The foot-bot gripper sensor",
                   "Giovanni Pini [gpini@ulb.ac.be]",
                   "This sensor accesses the foot-bot gripper sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_gripper implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None for the time being.\n",
                   "Under development."
      );
   
}

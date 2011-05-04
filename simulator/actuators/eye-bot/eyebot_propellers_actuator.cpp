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
 * @file <argos2/simulator/actuators/eye-bot/eyebot_propellers_actuator.cpp>
 *
 * @brief This file provides the implementation of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "eyebot_propellers_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/

   CEyeBotPropellersActuator::CEyeBotPropellersActuator() :
      m_bDesiredAttachedToCeiling(false),
      m_fDesiredAltitude(0.0f) {
   }
   
   /****************************************/
   /****************************************/

   void CEyeBotPropellersActuator::Update() {
      GetEntity().SetAttachedToCeiling(m_bDesiredAttachedToCeiling);
      GetEntity().SetMotionData(m_sDesiredMotionData);
      GetEntity().SetTargetAltitude(m_fDesiredAltitude);
   }

   /****************************************/
   /****************************************/

   void CEyeBotPropellersActuator::Reset() {
      m_bDesiredAttachedToCeiling = false;
      m_sDesiredMotionData.Source = CEyeBotEntity::SMotionData::MOTION_FROM_FORCES;
      m_sDesiredMotionData.ForceX = 0.0f;
      m_sDesiredMotionData.ForceY = 0.0f;
      m_sDesiredMotionData.ForceZ = 0.0f;
      m_fDesiredAltitude = 0.0f;
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CEyeBotPropellersActuator,
                     "eyebot_propellers", "default",
                     "The eye-bot propellers actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "********************************************************************************"
                     "This actuator controls the eye-bot propellers. For a complete description of\n"
                     "its usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <eyebot_propellers implementation=\"default\" />\n"
                     "        ...\n"
                     "      </actuators>\n"
                     "      ...\n"
                     "    </my_controller>\n"
                     "    ...\n"
                     "  </controllers>\n\n"
                     "OPTIONAL XML CONFIGURATION\n\n"
                     "None for the time being.\n",
                     "Under development"
      );
}

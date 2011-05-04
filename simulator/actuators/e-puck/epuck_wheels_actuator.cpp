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
 * @file <argos2/simulator/generic_actuators/e-puck/epuck_wheels_actuator.cpp>
 *
 * @brief This file provides the implementation of the epuck wheels actuator
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "epuck_wheels_actuator.h"
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/argos_random.h>

namespace argos {

   /****************************************/
   /****************************************/

   CEPuckWheelsActuator::CEPuckWheelsActuator() :
      m_pcWheeledEntity(NULL) {
      m_fCurrentVelocity[EPUCK_LEFT_WHEEL] = 0.0f;
      m_fCurrentVelocity[EPUCK_RIGHT_WHEEL] = 0.0f;
   }
   
   /****************************************/
   /****************************************/

   void CEPuckWheelsActuator::Init(TConfigurationNode& t_tree) {
      try {
         CCI_EPuckWheelsActuator::Init(t_tree);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in e-puck wheels actuator.", ex);
      }
   }

   /****************************************/
   /****************************************/
   
   void CEPuckWheelsActuator::SetLinearVelocity(Real f_left_velocity,
                                                Real f_right_velocity) {
      /* The speed is passed in cm/sec, so we have to transform it into m/sec */
      m_fCurrentVelocity[EPUCK_LEFT_WHEEL] = f_left_velocity * 0.01f;
      m_fCurrentVelocity[EPUCK_RIGHT_WHEEL] = f_right_velocity * 0.01f;
   }
   
   /****************************************/
   /****************************************/
   
   void CEPuckWheelsActuator::Update() {
      m_pcWheeledEntity->SetSpeed(m_fCurrentVelocity);
   }

   /****************************************/
   /****************************************/
   
   void CEPuckWheelsActuator::Reset() {
      m_fCurrentVelocity[EPUCK_LEFT_WHEEL]  = 0.0f;
      m_fCurrentVelocity[EPUCK_RIGHT_WHEEL] = 0.0f;
   }
   
   /****************************************/
   /****************************************/
   
   REGISTER_ACTUATOR(CEPuckWheelsActuator,
                     "epuck_wheels", "default",
                     "The e-puck wheels actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "This actuator controls the e-puck wheels. For a complete description of its\n"
                     "usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <epuck_wheels implementation=\"default\" />\n"
                     "        ...\n"
                     "      </actuators>\n"
                     "      ...\n"
                     "    </my_controller>\n"
                     "    ...\n"
                     "  </controllers>\n\n"
                     "OPTIONAL XML CONFIGURATION\n\n"
                     "It is possible to specify noisy speed in order to match the characteristics\n"
                     "of the real ropuck. This can be done with the xml parameter: 'noise_std_dev',\n" 
                     "which indicates the standard deviation of a gaussian noise applied to the\n"
                     "desired velocity of the wheels.",
                     "Under development"
      );
   
}

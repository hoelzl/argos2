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
 * @file <argos2/simulator/generic_actuators/foot-bot/footbot_wheels_actuator.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "footbot_wheels_actuator.h"
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/argos_random.h>

namespace argos {

   /****************************************/
   /****************************************/

   CFootBotWheelsActuator::CFootBotWheelsActuator() :
      m_pcWheeledEntity(NULL),
      m_pcRNG(NULL),
      m_fNoiseStdDeviation(0.0f) {
      m_fCurrentVelocity[FOOTBOT_LEFT_WHEEL] = 0.0f;
      m_fCurrentVelocity[FOOTBOT_RIGHT_WHEEL] = 0.0f;
   }
   
   /****************************************/
   /****************************************/

   void CFootBotWheelsActuator::Init(TConfigurationNode& t_tree) {
      try {
         CCI_FootBotWheelsActuator::Init(t_tree);
         /* Parse noise std deviation */
         GetNodeAttributeOrDefault(t_tree, "noise_std_dev", m_fNoiseStdDeviation, 0.0f);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in foot-bot wheels actuator.", ex);
      }
      /* Thread safe random number generator*/
      m_pcRNG = CARGoSRandom::CreateRNG("argos");
   }

   /****************************************/
   /****************************************/
   
   void CFootBotWheelsActuator::SetLinearVelocity(Real f_left_velocity,
                                                  Real f_right_velocity) {
      CCI_FootBotWheelsActuator::FOOTBOT_WHEELS_SPEED_RANGE.TruncValue(f_left_velocity);
      CCI_FootBotWheelsActuator::FOOTBOT_WHEELS_SPEED_RANGE.TruncValue(f_right_velocity);

      /* Convert speeds in m/s */
      m_fCurrentVelocity[FOOTBOT_LEFT_WHEEL] = f_left_velocity * 0.01f;
      m_fCurrentVelocity[FOOTBOT_RIGHT_WHEEL] = f_right_velocity * 0.01f;
      if(m_fNoiseStdDeviation != 0.0f) {
         AddGaussianNoise();
      }
   }
   
   /****************************************/
   /****************************************/
   
   void CFootBotWheelsActuator::Update() {
      m_pcWheeledEntity->SetSpeed(m_fCurrentVelocity);
   }

   /****************************************/
   /****************************************/
   
   void CFootBotWheelsActuator::Reset() {
      m_fCurrentVelocity[FOOTBOT_LEFT_WHEEL]  = 0.0f;
      m_fCurrentVelocity[FOOTBOT_RIGHT_WHEEL] = 0.0f;
   }
   
   /****************************************/
   /****************************************/
   
   void CFootBotWheelsActuator::AddGaussianNoise() {
      m_fCurrentVelocity[FOOTBOT_LEFT_WHEEL]  += m_fCurrentVelocity[FOOTBOT_LEFT_WHEEL] * m_pcRNG->Gaussian(m_fNoiseStdDeviation);
      m_fCurrentVelocity[FOOTBOT_RIGHT_WHEEL] += m_fCurrentVelocity[FOOTBOT_RIGHT_WHEEL] * m_pcRNG->Gaussian(m_fNoiseStdDeviation);
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CFootBotWheelsActuator,
                     "footbot_wheels", "default",
                     "The foot-bot wheels actuator",
                     "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                     "This actuator controls the foot-bot wheels. For a complete description of its\n"
                     "usage, refer to the common interface.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <footbot_wheels implementation=\"default\" />\n"
                     "        ...\n"
                     "      </actuators>\n"
                     "      ...\n"
                     "    </my_controller>\n"
                     "    ...\n"
                     "  </controllers>\n\n"
                     "OPTIONAL XML CONFIGURATION\n\n"
                     "It is possible to specify noisy speed in order to match the characteristics\n"
                     "of the real robot. This can be done with the xml parameter: 'noise_std_dev',\n" 
                     "which indicates the standard deviation of a gaussian noise applied to the\n"
                     "desired velocity of the wheels.",
                     "Under development"
      );
   
}

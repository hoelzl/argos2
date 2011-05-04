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
 * @file <argos2/simulator/generic_actuators/foot-bot/footbot_wheels_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_WHEELS_ACTUATOR_H
#define FOOTBOT_WHEELS_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotWheelsActuator;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_wheels_actuator.h>
#include <argos2/simulator/actuators/foot-bot/footbot_actuator.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/wheeled_entity.h>
#include <argos2/common/utility/argos_random.h>

namespace argos {

   class CFootBotWheelsActuator : public CFootBotActuator,
                                  public CCI_FootBotWheelsActuator {

   public:

      enum FOOTBOT_WHEELS {
         FOOTBOT_LEFT_WHEEL = 0,
         FOOTBOT_RIGHT_WHEEL = 1
      };

      /**
       *
       * @brief Constructor.
       *
       */
      CFootBotWheelsActuator();

      /**
       *
       * @brief Destructor.
       *
       */
      virtual ~CFootBotWheelsActuator() {}

      /**
       *
       * @brief Sets entity that is equipped with these wheels.
       *
       * @param c_entity entity equipped with the wheels.
       */
      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotActuator::SetEntity(c_entity);
         m_pcWheeledEntity = &(GetEntity().GetWheeledEntity());
      }

      /**
       *
       * @brief Initializes the wheels.
       *
       * @param t_tree XML configuration tree.
       */
      virtual void Init(TConfigurationNode& t_tree);

      /**
       *
       * @brief Sets the linear velocity of the two wheels.
       * Velocities are expressed in cm per second, actuated values
       * are truncated is they exceed the maximum allowed.
       *
       * @param f_left_velocity desired left wheel velocity.
       * @param f_right_velocity desired right wheel velocity.
       */
      virtual void SetLinearVelocity(Real f_left_velocity,
                                     Real f_right_velocity);

      /**
       *
       * @brief Update methd.
       *
       */
      virtual void Update();

      /**
       *
       * @brief Reset method.
       *
       */
      virtual void Reset();

   private:

      CWheeledEntity<2>* m_pcWheeledEntity;

      /** Random number generator */
      CARGoSRandom::CRNG* m_pcRNG;

      /** Noise parameters, at the moment noise is Gaussian */
      Real m_fNoiseStdDeviation;

      /** Adds noise to the wheels velocity */
      virtual void AddGaussianNoise();

   };

}

#endif

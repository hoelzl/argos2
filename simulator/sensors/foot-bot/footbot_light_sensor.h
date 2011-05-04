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
 * @file <argos2/simulator/sensors/foot-bot/footbot_light_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_LIGHT_SENSOR_H
#define FOOTBOT_LIGHT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotLightSensor;
   class CSpace;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_light_sensor.h>
#include <argos2/simulator/sensors/foot-bot/footbot_sensor.h>
#include <argos2/common/utility/argos_random.h>

namespace argos {

   class CFootBotLightSensor : public CFootBotSensor,
                               public CCI_FootBotLightSensor {

   public:

      CFootBotLightSensor();
      virtual ~CFootBotLightSensor();

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();
      virtual void Reset();

   private:

      CSpace& m_cSpace;
      bool m_bShowRays;
      CRadians m_cSensorSpacing;
      CRadians m_cSensorHalfSpacing;

      /* Random number generator */
      CARGoSRandom::CRNG* m_pcRNG;

      /* Noise parameter */
      Real m_fNoiseLevel;
   };

}

#endif

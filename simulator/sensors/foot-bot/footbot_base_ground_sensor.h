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
 * @file <argos2/simulator/sensors/foot-bot/footbot_base_ground_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_BASE_GROUND_SENSOR_H
#define FOOTBOT_BASE_GROUND_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotBaseGroundSensor;
   class CFloorEntity;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_base_ground_sensor.h>
#include <argos2/simulator/sensors/foot-bot/footbot_sensor.h>
#include <argos2/simulator/simulator.h>

namespace argos {

   class CFootBotBaseGroundSensor : public CFootBotSensor,
                                    public CCI_FootBotBaseGroundSensor {

   public:

      CFootBotBaseGroundSensor();
      virtual ~CFootBotBaseGroundSensor() {}

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();
      virtual void Reset();

   private:

      CSpace& m_cSpace;
      
      /* Flag for knowing if sensors are calibrated and readings normalised */
      bool m_bCalibrated;

      /* Random number generator */
      CARGoSRandom::CRNG* m_pcRNG;

      /* Noise parameter */
      Real m_fNoiseLevel;

      /* Adds noise to the sensor reading */
      virtual void AddNoise(UInt32 un_sensor_index);

   };

}

#endif

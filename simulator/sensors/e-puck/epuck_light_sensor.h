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
 * @file <argos2/simulator/sensors/e-puck/epuck_light_sensor.h>
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef EPUCK_LIGHT_SENSOR_H
#define EPUCK_LIGHT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckLightSensor;
   class CSpace;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_light_sensor.h>
#include <argos2/simulator/sensors/e-puck/epuck_sensor.h>
#include <argos2/common/utility/argos_random.h>

namespace argos {

   class CEPuckLightSensor : public CEPuckSensor,
                               public CCI_EPuckLightSensor {

   public:

      CEPuckLightSensor();
      CEPuckLightSensor(bool b_show_rays);
      virtual ~CEPuckLightSensor();

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();
      virtual void Reset();

      /* Adds noise to the sensor reading */
      virtual void AddNoise(UInt16 un_sensor_index);

   private:

      CSpace& m_cSpace;
      bool m_bShowRays;
      /* Random number generator */
      CARGoSRandom::CRNG* m_pcRNG;
      /* Uniform noise parameter */
      Real m_fNoiseLevel;

   };

}

#endif

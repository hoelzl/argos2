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
 * @file <argos2/simulator/sensors/e-puck/epuck_proximity_sensor.h>
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef EPUCK_PROXIMITY_SENSOR_H
#define EPUCK_PROXIMITY_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckProximitySensor;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_proximity_sensor.h>
#include <argos2/common/utility/math/range.h>
#include <argos2/simulator/sensors/e-puck/epuck_sensor.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/space/space.h>
#include <argos2/common/utility/argos_random.h>

namespace argos {
   
   class CEPuckProximitySensor : public CEPuckSensor,
                                 public CCI_EPuckProximitySensor {

   public:

      CEPuckProximitySensor();
      virtual ~CEPuckProximitySensor() {delete m_pcRNG;}

      virtual void Init(TConfigurationNode& t_tree);

      inline virtual void SetEntity(CEntity& c_entity) {
         CEPuckSensor::SetEntity(c_entity);
         m_pcEmbodiedEntity = &(GetEntity().GetEmbodiedEntity());
      }

      virtual void Update();
      virtual void Reset();

   protected:

      CSpace& m_cSpace;
      CSpaceHash<CEmbodiedEntity, CEmbodiedEntitySpaceHashUpdater>& m_cEmbodiedSpaceHash;
      CEmbodiedEntity* m_pcEmbodiedEntity;

      /* Flag for showing rays in the simulator */
      bool m_bShowRays;

      /* Random number generator */
      CARGoSRandom::CRNG* m_pcRNG;

      /* Uniform noise parameter */
      Real m_fNoiseLevel;

      /* Radings default range */
      static const CRange<Real> EPUCK_PROXIMITY_SENSORS_READINGS_RANGE;

      /* noise level in in the proximity range */
      Real m_fRangeNoiseLevel;
    
      /* Adds noise to the sensor reading */
      virtual void AddNoise(UInt16 un_sensor_index);

   };

}

#endif

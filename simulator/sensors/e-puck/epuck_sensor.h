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
 * @file <argos2/simulator/generic_sensors/e-puck/epuck_sensor.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EPUCK_SENSOR_H
#define EPUCK_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckSensor;
}

#include <argos2/simulator/sensors/simulated_sensor.h>
#include <argos2/simulator/space/entities/epuck_entity.h>

namespace argos {

   class CEPuckSensor : public CSimulatedSensor {

   public:

      CEPuckSensor() :
         m_pcEPuckEntity(NULL) {}
      virtual ~CEPuckSensor() {}

      inline virtual CEPuckEntity& GetEntity() {
         return *m_pcEPuckEntity;
      }
      inline virtual void SetEntity(CEntity& c_entity) {
         m_pcEPuckEntity = dynamic_cast<CEPuckEntity*>(&c_entity);
         if(m_pcEPuckEntity == NULL) {
            THROW_ARGOSEXCEPTION("Cannot associate a e-puck sensor to a robot of type \"" << c_entity.GetTypeDescription() << "\"");
         }
      }

   private:

      CEPuckEntity* m_pcEPuckEntity;

   };

}

#endif

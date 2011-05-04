/*
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
 * @file <argos2/simulator/sensors/clock_sensor.h>
 *
 * @brief This file provides the implementation of the clock sensor.
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef CLOCK_SENSOR_H
#define CLOCK_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CClockSensor;
}

#include <argos2/simulator/sensors/simulated_sensor.h>
#include <argos2/common/control_interface/ci_clock_sensor.h>
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/entities/composable_entity.h>

namespace argos {

   class CClockSensor : public CSimulatedSensor,
                        public CCI_ClockSensor {

   public:

	  CClockSensor() : m_cSpace(CSimulator::GetInstance().GetSpace()){}
      virtual ~CClockSensor() {}

      inline virtual void Init(TConfigurationNode& t_tree) {}

      inline virtual CEntity& GetEntity() {
         return *m_pcEmbodiedEntity;
      }
      inline virtual void SetEntity(CEntity& c_entity) {
    	  CComposableEntity* pcComposableEntity = dynamic_cast<CComposableEntity*>(&c_entity);
    	  if(pcComposableEntity != NULL) {
    		  /* The entity is composable, does it have the required components? */
    		  if(pcComposableEntity->HasComponent("embodied_entity")) {
    			  /* Yes, it does */
    			  m_pcEmbodiedEntity = &(pcComposableEntity->GetComponent<CEmbodiedEntity>("embodied_entity"));
    		  }
    	  }
      }

      inline virtual void Update(){}
      inline virtual void Reset(){}

      inline virtual Real GetElapsedTime(){
    	  return m_cSpace.GetSimulationClock() * GetClockTickLength();
      }

      inline virtual Real GetClockTickLength(){
    	  // we take the clocktick of the first physics engine, as they are all the same (it is set in the framework xml section)
    	  return m_pcEmbodiedEntity->GetPhysicsEngine(0).GetSimulationClockTick();
      }

   private:

      CSpace& m_cSpace;
      CEmbodiedEntity* m_pcEmbodiedEntity;

   };

}

#endif

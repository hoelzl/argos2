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
 * @file <argos2/simulator/space/entities/controllable_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "controllable_entity.h"
#include <argos2/simulator/actuators/simulated_actuator.h>
#include <argos2/simulator/sensors/simulated_sensor.h>

namespace argos {

   /****************************************/
   /****************************************/

   CControllableEntity::~CControllableEntity()
   {
      if(m_pcController != NULL) {
         delete m_pcController;
      }
   }

   /****************************************/
   /****************************************/

   void CControllableEntity::Init(TConfigurationNode& t_tree)
   {
      try {
         /* Init parent */
         CEntity::Init(t_tree);
         /* Get the controller of the controllable */
         GetNodeAttribute(t_tree, "controller", m_strControllerId);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize controllable entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CControllableEntity::Reset()
   {
      /* Clear rays */
      m_vecCheckedRays.clear();
      m_vecIntersectionPoints.clear();

      /* Reset sensors */
      for(std::map<std::string, CSimulatedSensor*>::iterator it = m_mapSensors.begin();
          it != m_mapSensors.end(); ++it) {
         it->second->Reset();
      }
      /* Reset actuators */
      for(std::map<std::string, CSimulatedActuator*>::iterator it = m_mapActuators.begin();
          it != m_mapActuators.end(); ++it) {
         it->second->Reset();
      }
      /* Reset user-defined controller */
      m_pcController->Reset();
   }

   /****************************************/
   /****************************************/

   void CControllableEntity::Destroy()
   {
      /* Clear rays */
      m_vecCheckedRays.clear();
      m_vecIntersectionPoints.clear();

      /* Destroy sensors */
      for(std::map<std::string, CSimulatedSensor*>::iterator it = m_mapSensors.begin();
          it != m_mapSensors.end(); ++it) {
         it->second->Destroy();
      }
      /* Destroy actuators */
      for(std::map<std::string, CSimulatedActuator*>::iterator it = m_mapActuators.begin();
          it != m_mapActuators.end(); ++it) {
         it->second->Destroy();
      }
      /* Destroy user-defined controller */
      if(m_pcController) {
         m_pcController->Destroy();
      }
   }

   /****************************************/
   /****************************************/

   void CControllableEntity::SetController(CCI_Controller& pc_controller) {
      /* Set the controller */
      m_pcController = &pc_controller;
      /* Set the simulated actuator list */
      for(TActuatorMap::iterator it = m_pcController->GetRobot().GetAllActuators().begin();
          it != m_pcController->GetRobot().GetAllActuators().end(); ++it) {
         m_mapActuators[it->first] = dynamic_cast<CSimulatedActuator*>(it->second);
      }
      /* Set the simulated sensor list */
      for(TSensorMap::iterator it = m_pcController->GetRobot().GetAllSensors().begin();
          it != m_pcController->GetRobot().GetAllSensors().end(); ++it) {
         m_mapSensors[it->first] = dynamic_cast<CSimulatedSensor*>(it->second);
      }
   }

   /****************************************/
   /****************************************/

   void CControllableEntity::Sense() {
      m_vecCheckedRays.clear();
      m_vecIntersectionPoints.clear();

      for(std::map<std::string, CSimulatedSensor*>::iterator it = m_mapSensors.begin();
          it != m_mapSensors.end(); ++it) {
         it->second->Update();
      }
   }

   /****************************************/
   /****************************************/

   void CControllableEntity::Act() {
      for(std::map<std::string, CSimulatedActuator*>::iterator it = m_mapActuators.begin();
          it != m_mapActuators.end(); ++it) {
         it->second->Update();
      }
   }

   /****************************************/
   /****************************************/

}

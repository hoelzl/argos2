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
 * @file <simulator/physics_engines/physics_engine.cpp>
 *
 * @brief This file provides the default implementation of the interface of a physics engine.
 *
 * This file provides the default implementation of the interface of a physics
 * engine. All the physics engines must implement this interface to be usable
 * with ARGOS.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include <cstdlib>
#include <physics_engines/physics_engine.h>
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/string_utilities.h>
#include <space/entities/entity.h>

namespace argos
{

   /* The map of physics engines */
   std::map<std::string, CPhysicsEngine_Maker *, std::less<std::string> > mapPhysicsEngineFactory;

   /* The default value of the simulation clock tick */
   Real CPhysicsEngine::m_fSimulationClockTick = 0.1f;
   Real CPhysicsEngine::m_fInverseSimulationClockTick = 1.0f / CPhysicsEngine::m_fSimulationClockTick;

   /****************************************/
   /****************************************/

   void CPhysicsEngine::Init(TConfigurationNode& t_tree)
   {
      /* Get physics engine id from the XML */
      GetNodeAttribute(t_tree, "id", m_strId);
   }

   /****************************************/
   /****************************************/

   Real CPhysicsEngine::GetSimulationClockTick() {
      return m_fSimulationClockTick;
   }
   
   /****************************************/
   /****************************************/

   Real CPhysicsEngine::GetInverseSimulationClockTick() {
      return m_fInverseSimulationClockTick;
   }
   
   /****************************************/
   /****************************************/

   void CPhysicsEngine::SetSimulationClockTick(Real f_simulation_clock_tick) {
      LOG << "[INFO] Using simulation clock tick = " << f_simulation_clock_tick << std::endl;
      m_fSimulationClockTick = f_simulation_clock_tick;         
      m_fInverseSimulationClockTick = 1.0f / f_simulation_clock_tick;         
   }

   /****************************************/
   /****************************************/

}

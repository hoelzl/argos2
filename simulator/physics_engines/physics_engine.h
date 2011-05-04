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
 * @file <argos2/simulator/physics_engines/physics_engine.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

namespace argos {
   class CPhysicsEngine;
   class CPhysicsEngineEntity;
   class CEntity;
}

#include <map>
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/common/utility/configuration/argos_configuration.h>
#include <argos2/common/utility/datatypes/datatypes.h>

namespace argos {

   class CPhysicsEngine : public CBaseConfigurableResource {

   protected:

      /** The physics engine's id. */
      std::string m_strId;

      /** How long a clock tick lasts (in seconds) */
      static Real m_fSimulationClockTick;

      /** The inverse of m_fSimulationClockTick */
      static Real m_fInverseSimulationClockTick;

      /** The current clock as seen by this physics engine */
      Real m_fPhysicsEngineClock;

   public:

      CPhysicsEngine() :
         m_fPhysicsEngineClock(0.0) {}
      virtual ~CPhysicsEngine() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset() = 0;
      virtual void Destroy() {}

      virtual void Update() = 0;

      virtual UInt32 GetNumPhysicsEngineEntities() = 0;
      virtual void AddEntity(CEntity& c_entity) = 0;
      virtual void RemoveEntity(CEntity& c_entity) = 0;
      inline virtual bool IsEntityTransferNeeded() const {
         return false;
      }
      virtual void TransferEntities() {}

      static Real GetSimulationClockTick();
      static Real GetInverseSimulationClockTick();
      static void SetSimulationClockTick(Real f_simulation_clock_tick);

      inline void SetPhysicsEngineClock(Real f_physics_engine_clock) {
         m_fPhysicsEngineClock = f_physics_engine_clock;
      }
      inline Real GetPhysicsEngineClock() const {
         return m_fPhysicsEngineClock;
      }

      inline const std::string& GetId() const {
         return m_strId;
      }
      void SetId(const std::string& str_id) {
         m_strId = str_id;
      }
               
   };

   typedef std::vector<CPhysicsEngine*> TPhysicsEngineList;
   typedef std::map<std::string, CPhysicsEngine*, std::less<std::string> > TPhysicsEngineMap;
}

/* Physics engine factory */
namespace argos {

   // typedef to make it easier to set up the physics engine factory
   typedef CPhysicsEngine *CPhysicsEngine_Maker();

   struct SPhysicsEnginePlugin {
      std::map < std::string, CPhysicsEngine_Maker *, std::less<std::string> > FactoryMap;
      std::map < std::string,            std::string, std::less<std::string> > ShortDescriptionMap;
      std::map < std::string,            std::string, std::less<std::string> > AuthorMap;
      std::map < std::string,            std::string, std::less<std::string> > LongDescriptionMap;
      std::map < std::string,            std::string, std::less<std::string> > StatusMap;
   };

   SPhysicsEnginePlugin* GetPhysicsEnginePlugin();

// to add the controller to the factory
#define REGISTER_PHYSICS_ENGINE(class_name, label, short_description, author, long_description, status) \
   extern "C" {                                                         \
      CPhysicsEngine* class_name ## _maker(){                           \
         return new class_name;                                         \
      }                                                                 \
                                                                        \
      class class_name ## _proxy {                                      \
      public:                                                           \
      class_name ## _proxy(){                                           \
         DEBUG_CONFIGURATION( "Registering physics engine <" #class_name ", " label ">\n" ); \
         argos::GetPhysicsEnginePlugin()->FactoryMap[label] = class_name ## _maker; \
         argos::GetPhysicsEnginePlugin()->ShortDescriptionMap[label] = short_description; \
         argos::GetPhysicsEnginePlugin()->AuthorMap[label] = author; \
         argos::GetPhysicsEnginePlugin()->LongDescriptionMap[label] = long_description; \
         argos::GetPhysicsEnginePlugin()->StatusMap[label] = status; \
      }                                                                 \
      };                                                                \
      class_name ## _proxy class_name ## _p;                            \
   }

}

#endif

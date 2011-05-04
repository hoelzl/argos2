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
 * @mainpage Autonomous Robots GO Swarming
 * @author Carlo Pinciroli <cpinciro@ulb.ac.be>
 *
 * @ref README "ARGOS QUICK GUIDE"
 * @include README
 *
 * @version  2.0
 * @see      http://iridia.ulb.ac.be/
 * @see      http://www.swarmanoid.org/
 *
 * ARGOS is an Adaptive Heterogeneous Swarm Simulator designed for the
 * Swarmanoid Project.
 */

/**
 * @file <simulator/simulator.h>
 *
 * @brief This file provides the definition of class CSimulator, the core class of ARGOS.
 *
 * This file provides class CSimulator, the core class of ARGOS.
 * CSimulator organises the flow of data coming from the modules of ARGOS
 * and provides the main simulation loop.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CSIMULATOR_H
#define CSIMULATOR_H

namespace argos {
   class CSimulator;
   class CLoopFunctions;
   class CRender;
   class CSpace;
   class CDynamicLinkingManager;
   class CProfiler;
}

#include <argos2/common/utility/argos_random.h>
#include <argos2/common/utility/configuration/argos_configuration.h>
#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/simulator/physics_engines/physics_engine.h>
#include <string>
#include <map>

/**
 * @brief The namespace containing all the ARGOS related code.
 *
 * The namespace containing all the ARGOS related code.
 */
namespace argos {

   /**
    * @class CSimulator
    *
    * @brief The core class of ARGOS.
    *
    * Class CSimulator is the core class of ARGOS. CSimulator organises the flow
    * of data coming from the modules of ARGOS and provides the main simulation
    * loop.
    *
    */
   class CSimulator {

   private:

      /** A reference to the renderer */
      CRender* m_pcRender;

      /** The vector of physics engines */
      TPhysicsEngineMap m_mapPhysicsEngines;
      TPhysicsEngineList m_vecPhysicsEngines;

      /** The space */
      CSpace* m_pcSpace;

      /** Reference to the loop functions */
      CLoopFunctions* m_pcLoopFunctions;

      /** The file name of the configuration XML file */
      std::string m_strExperimentConfigFileName;

      /** The controller manager */
      CDynamicLinkingManager* m_pcDynamicLinkingManager;

      /** The maximum simulation clock */
      UInt32 m_unMaxSimulationClock;

      /** The random seed used for initialisation */
      UInt32 m_unRandomSeed;

      /** The random number generator */
      CARGoSRandom::CRNG* m_pcRNG;

      /** The flag to remember if the random seed was set at the beginning or init with the time of the day  */
      bool m_bWasRandomSeedSet;

      /** XML configuration file */
      ticpp::Document m_tConfiguration;

      /** XML configuration file root node */
      TConfigurationNode m_tConfigurationRoot;

      /** Directory pointed to by ARGOSINSTALLDIR */
      std::string m_strInstallationDirectory;

      /** The number of parallel threads to split up the computation */
      UInt32 m_unThreads;

      /** Profiler class */
      CProfiler* m_pcProfiler;

      /** Profiler format */
      bool m_bHumanReadableProfile;

   private:

      CSimulator();

      CSimulator(const CSimulator&) {}

      CSimulator& operator=(const CSimulator&) {
         return *this;
      }

   public:

      ~CSimulator();

      static CSimulator& GetInstance();

      inline CSpace& GetSpace() const {
         return *m_pcSpace;
      }

      inline CPhysicsEngine& GetPhysicsEngine(const std::string& str_id) const {
         TPhysicsEngineMap::const_iterator it = m_mapPhysicsEngines.find(str_id);
         ARGOS_ASSERT(it != m_mapPhysicsEngines.end(), "Physics engine \"" << str_id << "\" not found.")
         return *(it->second);
      }

      inline TPhysicsEngineList& GetPhysicsEngines() {
         return m_vecPhysicsEngines;
      }

      inline CRender& GetRender() {
         ARGOS_ASSERT(m_pcRender != NULL, "No renderer specified in the XML file.");
         return *m_pcRender;
      }

      inline TConfigurationNode& GetConfigurationRoot() {
         return m_tConfigurationRoot;
      }

      inline CProfiler& GetProfiler() {
         return *m_pcProfiler;
      }

      inline bool IsProfiling() const {
         return m_pcProfiler != NULL;
      }

      void LoadExperiment();

      void Init();

      void Reset();

      inline void Reset(UInt32 un_new_random_seed) {
         SetRandomSeed(un_new_random_seed);
         Reset();
      }

      void Destroy();

      void Execute();

      void UpdateSpace();

      bool IsExperimentFinished() const;
      
      inline UInt32 GetRandomSeed() const {
         return m_unRandomSeed;
      }

      inline void SetRandomSeed(UInt32 un_random_seed) {
         m_unRandomSeed = un_random_seed;
         m_bWasRandomSeedSet = true;
      }

      inline CARGoSRandom::CRNG* GetRNG() {
         return m_pcRNG;
      }

      inline CDynamicLinkingManager& GetDynamicLinkingManager() {
         return *m_pcDynamicLinkingManager;
      }

      inline const std::string& GetExperimentFileName() const {
         return m_strExperimentConfigFileName;
      }

      inline void SetExperimentFileName(const std::string& str_file_name) {
         m_strExperimentConfigFileName = str_file_name;
      }

      inline CLoopFunctions& GetLoopFunctions() {
         return *m_pcLoopFunctions;
      }

      inline void SetLoopFunctions(CLoopFunctions& c_loop_functions) {
         m_pcLoopFunctions = &c_loop_functions;
      }

      inline UInt32 GetMaxSimulationClock() const {
         return m_unMaxSimulationClock;
      }

      inline void SetInstallationDirectory(const std::string& str_installation_dir) {
         m_strInstallationDirectory = str_installation_dir;
      }

      inline const std::string& GetInstallationDirectory() const {
         return m_strInstallationDirectory;
      }

      inline UInt32 GetNumThreads() const {
         return m_unThreads;
      }

   private:

      void InitFramework(TConfigurationNode& t_tree);
      void InitSpace(TConfigurationNode& t_tree);
      void InitPhysics(TConfigurationNode& t_tree);
      void InitRendering(TConfigurationNode& t_tree);
      void InitPhysicsEntitiesMapping(TConfigurationNode& t_tree);
   };

}

#endif

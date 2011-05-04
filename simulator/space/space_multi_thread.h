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
 * @file <argos2/simulator/space/space_multi_thread.h>
 *
 * @brief This file provides the definition of the Swarmanoid 3D Space.
 *
 * This file provides the definition of the Swarmanoid 3D Space.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef SPACE_MULTI_THREAD_H
#define SPACE_MULTI_THREAD_H

#include <argos2/simulator/space/space.h>
#include <pthread.h>

namespace argos {

   class CSpaceMultiThread : public CSpace {

      /****************************************/
      /****************************************/

   private:

      struct SUpdateThreadData {
         UInt32 ThreadId;
         CSpaceMultiThread* Space;
         
         SUpdateThreadData(UInt32 un_thread_id,
                           CSpaceMultiThread* pc_space) :
            ThreadId(un_thread_id),
            Space(pc_space) {}
      };

      /****************************************/
      /****************************************/

   private:

      /** Data structure needed to launch the threads */
      SUpdateThreadData** m_psUpdateThreadData;

      /** The update threads */
      pthread_t* m_ptUpdateThreads;

      /** Update thread related variables */
      UInt32 m_unSenseControlStepPhaseDoneCounter;
      UInt32 m_unActPhaseDoneCounter;
      UInt32 m_unPhysicsPhaseDoneCounter;

      /** Update thread conditional mutexes */
      pthread_mutex_t m_tSenseControlStepConditionalMutex;
      pthread_mutex_t m_tActConditionalMutex;
      pthread_mutex_t m_tPhysicsConditionalMutex;

      /** Update thread conditionals */
      pthread_cond_t m_tSenseControlStepConditional;
      pthread_cond_t m_tActConditional;
      pthread_cond_t m_tPhysicsConditional;

      /** Flag to know whether the assignment of controllable
          entities to threads must be recalculated */
      bool m_bIsControllableEntityAssignmentRecalculationNeeded;

   public:

      CSpaceMultiThread() :
         m_psUpdateThreadData(NULL),
         m_ptUpdateThreads(NULL),
         m_bIsControllableEntityAssignmentRecalculationNeeded(true) {}
      virtual ~CSpaceMultiThread() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Destroy();

      virtual void AddControllableEntity(CControllableEntity& c_entity);
      virtual void RemoveControllableEntity(CControllableEntity& c_entity);

      virtual void SetPhysicsEngines(TPhysicsEngineList& t_engines);

      virtual void UpdateControllableEntities();
      virtual void UpdatePhysics();

   private:

      void StartThreads();
      void UpdateThread(UInt32 un_id);
      friend void* LaunchUpdateThread(void* p_data);

   };

}

#endif

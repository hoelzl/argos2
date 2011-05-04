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
 * @file <argos2/common/utility/profiler/profiler.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */
#ifndef PROFILER_H
#define PROFILER_H

#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace argos {

   class CProfiler {

   public:

      CProfiler(const std::string& str_file_name,
                bool b_trunc=true);
      ~CProfiler();

      void Start();
      void Stop();
      void Flush(bool b_human_readable);
      void CollectThreadResourceUsage();

   private:

      void StartWallClock();
      void StopWallClock();

      void StartCPUProfiler();
      void StopCPUProfiler();

      void FlushHumanReadable();
      void FlushAsTable();

   private:

      std::ofstream m_cOutFile;
      ::timeval m_tWallClockStart;
      ::timeval m_tWallClockEnd;
      ::rusage m_tResourceUsageStart;
      ::rusage m_tResourceUsageEnd;
      std::vector< ::rusage > m_vecThreadResourceUsage;
      pthread_mutex_t m_tThreadResourceUsageMutex;

   };

}

#endif

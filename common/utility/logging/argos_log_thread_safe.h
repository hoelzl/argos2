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
 * @file <common/logging/argos_log.h>
 *
 * @brief This file provides some useful logging and debugging macros.
 *
 * These are the macro definitions. They are all constructed with the same pattern:
 *
 * DEBUG_TYPE(format, arguments...)
 *
 * and are meant to be used in these ways:
 *
 * DEBUG_TYPE(format)
 *
 * or
 *
 * DEBUG_TYPE(format, arguments)
 *
 * where "format" and "arguments" are the usual format string and arguments of a printf statement.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CARGOSLOG_H
#define CARGOSLOG_H

#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <pthread.h>
#include <sstream>
#include <map>
#include <vector>

namespace argos {
   class CARGOSLogger;
}

#include <argos2/common/utility/logging/argos_colored_text.h>

namespace argos {

   /** Debugging messages for generic simulator code. */
#ifdef ARGOS_DBG_SIMULATOR
#define DEBUG_SIMULATOR(format, ...) fprintf( stderr, "[DEBUG-SIMULATOR] " format, ## __VA_ARGS__ )
#else
#define DEBUG_SIMULATOR(format, ...)
#endif

   /** Debugging messages for aseba code. */
#ifdef ARGOS_DBG_ASEBA
#define DEBUG_ASEBA(format, ...) fprintf( stderr, "[DEBUG-ASEBA] " format, ## __VA_ARGS__ )
#else
#define DEBUG_ASEBA(format, ...)
#endif

   /** Debugging messages for configuration code. */
#ifdef ARGOS_DBG_CONFIGURATION
#define DEBUG_CONFIGURATION(format, ...) fprintf( stderr, "[DEBUG-CONFIGURATION] " format, ## __VA_ARGS__ )
#else
#define DEBUG_CONFIGURATION(format, ...)
#endif

   /** Debugging messages for simulated actuators code. */
#ifdef ARGOS_DBG_ACTUATORS
#define DEBUG_ACTUATORS(format, ...) fprintf( stderr, "[DEBUG-ACTUATORS] " format, ## __VA_ARGS__ )
#else
#define DEBUG_ACTUATORS(format, ...)
#endif

   /** Debugging messages for simulated sensors code. */
#ifdef ARGOS_DBG_SENSORS
#define DEBUG_SENSORS(format, ...) fprintf( stderr, "[DEBUG-SENSORS] " format, ## __VA_ARGS__ )
#else
#define DEBUG_SENSORS(format, ...)
#endif

   /** Debugging messages for simulator logging code. */
#ifdef ARGOS_DBG_LOGGING
#define DEBUG_LOGGING(format, ...) fprintf( stderr, "[DEBUG-LOGGING] " format, ## __VA_ARGS__ )
#else
#define DEBUG_LOGGING(format, ...)
#endif

   /** Debugging messages for physical engines code. */
#ifdef ARGOS_DBG_PHYSICS
#define DEBUG_PHYSICS(format, ...) fprintf( stderr, "[DEBUG-PHYSICS] " format, ## __VA_ARGS__ )
#else
#define DEBUG_PHYSICS(format, ...)
#endif

   /** Debugging messages for statistics code. */
#ifdef ARGOS_DBG_STATISTICS
#define DEBUG_STATISTICS(format, ...) fprintf( stderr, "[DEBUG-STATISTICS] " format, ## __VA_ARGS__ )
#else
#define DEBUG_STATISTICS(format, ...)
#endif

   /** Debugging messages for argos space code. */
#ifdef ARGOS_DBG_ARGOSSPACE
#define DEBUG_ARGOSSPACE(format, ...) fprintf( stderr, "[DEBUG-ARGOSSPACE] " format, ## __VA_ARGS__ )
#else
#define DEBUG_ARGOSSPACE(format, ...)
#endif

   /** Debugging messages for simulation visualization code. */
#ifdef ARGOS_DBG_VISUALISATION
#define DEBUG_VISUALISATION(format, ...) fprintf( stderr, "[DEBUG-VISUALISATION] " format, ## __VA_ARGS__ )
#else
#define DEBUG_VISUALISATION(format, ...)
#endif

   /** Debugging messages for controller code. */
#ifdef ARGOS_DBG_CONTROLLER
#define DEBUG_CONTROLLER(format, ...) fprintf( stderr, "[DEBUG-CONTROLLER] [robot id=\"%s\"] " format, GetRobot().GetRobotId().c_str(), ## __VA_ARGS__ )
#define DEBUG_ROBOT(id, format, ...) if (GetRobot().GetRobotId() == id) fprintf( stderr, "[DEBUG-CONTROLLER] [robot id=\"%s\"] " format, GetRobot().GetRobotId().c_str(), ## __VA_ARGS__ )
#define DEBUG_BT_CONTROLLER(format, ...) fprintf( stderr, "[DEBUG-CONTROLLER] [robot id=\"%s\"] " format, m_pcRobotData->GetRobot()->GetRobotId().c_str(), ## __VA_ARGS__ )
#define DEBUG_BT_ROBOT(id, format, ...) if (m_pcRobotData.GetRobot()->GetRobotId() == id) fprintf( stderr, "[DEBUG-CONTROLLER] [robot id=\"%s\"] " format, m_pcRobotData->GetRobot()->GetRobotId().c_str(), ## __VA_ARGS__ )
#else
#define DEBUG_CONTROLLER(format, ...)
#define DEBUG_ROBOT(id, format, ...)
#define DEBUG_BT_CONTROLLER(format, ...)
#define DEBUG_BT_ROBOT(id, format, ...)
#endif

   /** Debugging messages for user-specific code. */
#ifdef ARGOS_DBG_USER
#define DEBUG_USER(format, ...) fprintf( stderr, "[DEBUG-USER] " format, ## __VA_ARGS__ )
#else
#define DEBUG_USER(format, ...)
#endif

   class CARGoSLog {

   private:

      /** The stream to write to */
      std::ostream& m_cStream;

      /** The default output color */
      SLogColor m_sLogColor;

      /** True when we want to use color */
      bool m_bColoredOutput;

      /** Maps a thread to its visualization order */
      std::map<pthread_t, size_t> m_mapStreamOrder;

      /** Contains the buffer streams */
      std::vector<std::stringstream*> m_vecStreams;

      /** The mutex to protect the operations on the buffers */
      pthread_mutex_t m_tMutex;

   public:

      CARGoSLog(std::ostream& c_stream,
                const SLogColor& s_log_color,
                bool b_colored_output_enabled = true) :
         m_cStream(c_stream),
         m_sLogColor(s_log_color),
         m_bColoredOutput(b_colored_output_enabled) {
         pthread_mutex_init(&m_tMutex, NULL);
         AddThreadSafeBuffer();
      }

      ~CARGoSLog() {
         pthread_mutex_destroy(&m_tMutex);
         while(!m_vecStreams.empty()) {
            delete m_vecStreams.back();
            m_vecStreams.pop_back();
         }
      }

      inline void EnableColoredOutput() {
         m_bColoredOutput = true;
      }

      inline void DisableColoredOutput() {
         m_bColoredOutput = false;
      }

      inline bool IsColoredOutput() const {
         return m_bColoredOutput;
      }

      inline std::ostream& GetStream() {
         return m_cStream;
      }

      inline void Flush() {
         pthread_mutex_lock(&m_tMutex);
         for(size_t i = 0; i < m_vecStreams.size(); ++i) {
            m_cStream << m_vecStreams[i]->str();
            m_vecStreams[i]->str("");
         }
         pthread_mutex_unlock(&m_tMutex);
      }

      inline void AddThreadSafeBuffer() {
         pthread_mutex_lock(&m_tMutex);
         m_mapStreamOrder.insert(std::make_pair<pthread_t, size_t>(pthread_self(), m_vecStreams.size()));
         m_vecStreams.push_back(new std::stringstream);
         pthread_mutex_unlock(&m_tMutex);
      }
      
      inline CARGoSLog& operator<<(std::ostream& (*c_stream)(std::ostream&)) {
         *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << c_stream;
         return *this;
      }

      inline CARGoSLog& operator<<(const std::_Setw& t_msg) {
         *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << t_msg;
         return *this;
      }

      inline CARGoSLog& operator<<(const std::_Setiosflags& t_msg) {
         *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << t_msg;
         return *this;
      }

      template <typename T> CARGoSLog& operator<<(const T t_msg) {
         if(m_bColoredOutput) {
            *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << m_sLogColor << t_msg << reset;
         }
         else {
            *(m_vecStreams[m_mapStreamOrder.find(pthread_self())->second]) << t_msg;
         }
         return *this;
      }

   };

   extern CARGoSLog LOG;
   extern CARGoSLog LOGERR;

}

#endif

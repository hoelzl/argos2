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
 * @file <simulator/configuration/command_line_argument_parser.cpp>
 *
 * @brief This file provides the implementation of class CCommandLineArgumentParser to handle command line arguments.
 *
 * This file provides the implementation of class CCommandLineArgumentParser to
 * handle command line arguments.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "command_line_argument_parser.h"
#include <argos2/common/utility/configuration/argos_configuration.h>
#include <argos2/simulator/visualizations/render.h>
#include <argos2/simulator/physics_engines/physics_engine.h>
#include <argos2/simulator/space/entities/entity.h>
#include <argos2/simulator/actuators/simulated_actuator.h>
#include <argos2/simulator/sensors/simulated_sensor.h>

#include <cstdlib>
#include <cstring>
#include <string>

namespace argos {

   /****************************************/
   /****************************************/

   const std::string ARGOSINSTALLDIR("ARGOSINSTALLDIR");

   /* Accepted options */
   const char* const CCommandLineArgumentParser::m_pchShortOptions = "hc:q:n";
   const struct option CCommandLineArgumentParser::m_strLongOptions[] = { { "help", 0, NULL, 'h' }, /* Help */
                                                                          { "config-file", 1, NULL, 'c' }, /* Configuration file */
                                                                          { "query", 1, NULL, 'q' }, /* Configuration file */
                                                                          { "no-color", 0, NULL, 'n' }, /* Do not color the output */
                                                                          { NULL, 0, NULL, 0 } /* Required to end the array */
   };

   /****************************************/
   /****************************************/

   static void QueryShowActuatorList() {
      std::map < std::string, std::string, std::less<std::string> >&
         mapShortDescriptions = GetActuatorPlugin()->ShortDescriptionMap;
      LOG << "AVAILABLE ACTUATORS" << std::endl << std::endl;
      for(std::map < std::string, std::string, std::less<std::string> >::iterator it = mapShortDescriptions.begin();
          it != mapShortDescriptions.end(); ++it) {
         LOG << "   [ " << it->first << " ]" << std::endl;
         LOG << "      " << it->second << std::endl << std::endl;
      }
   }

   /****************************************/
   /****************************************/

   static void QueryShowSensorList() {
      std::map < std::string, std::string, std::less<std::string> >&
         mapShortDescriptions = GetSensorPlugin()->ShortDescriptionMap;
      LOG << "AVAILABLE SENSORS" << std::endl << std::endl;
      for(std::map < std::string, std::string, std::less<std::string> >::iterator it = mapShortDescriptions.begin();
          it != mapShortDescriptions.end(); ++it) {
         LOG << "   [ " << it->first << " ]" << std::endl;
         LOG << "      " << it->second << std::endl << std::endl;
      }
   }

   /****************************************/
   /****************************************/

   static void QueryShowPhysicsEngineList() {
      std::map < std::string, std::string, std::less<std::string> >&
         mapShortDescriptions = GetPhysicsEnginePlugin()->ShortDescriptionMap;
      LOG << "AVAILABLE PHYSICS ENGINES" << std::endl << std::endl;
      for(std::map < std::string, std::string, std::less<std::string> >::iterator it = mapShortDescriptions.begin();
          it != mapShortDescriptions.end(); ++it) {
         LOG << "   [ " << it->first << " ]" << std::endl;
         LOG << "      " << it->second << std::endl << std::endl;
      }
   }

   /****************************************/
   /****************************************/

   static void QueryShowVisualizationList() {
      std::map < std::string, std::string, std::less<std::string> >&
         mapShortDescriptions = GetRendererPlugin()->ShortDescriptionMap;
      LOG << "AVAILABLE VISUALIZATIONS" << std::endl << std::endl;
      for(std::map < std::string, std::string, std::less<std::string> >::iterator it = mapShortDescriptions.begin();
          it != mapShortDescriptions.end(); ++it) {
         LOG << "   [ " << it->first << " ]" << std::endl;
         LOG << "      " << it->second << std::endl << std::endl;
      }
   }

   /****************************************/
   /****************************************/

   static void QueryShowEntityList() {
      std::map < std::string, std::string, std::less<std::string> >&
         mapShortDescriptions = GetEntityPlugin()->ShortDescriptionMap;
      LOG << "AVAILABLE ENTITIES" << std::endl << std::endl;
      for(std::map < std::string, std::string, std::less<std::string> >::iterator it = mapShortDescriptions.begin();
          it != mapShortDescriptions.end(); ++it) {
         LOG << "   [ " << it->first << " ]" << std::endl;
         LOG << "      " << it->second << std::endl << std::endl;
      }
   }

   /****************************************/
   /****************************************/

   static void QuerySearchPlugins(const std::string& str_query,
                                  const std::map<std::string, std::string, std::less<std::string> >& map_status,
                                  const std::map<std::string, std::string, std::less<std::string> >& map_short_descriptions,
                                  const std::map<std::string, std::string, std::less<std::string> >& map_authors,
                                  const std::map<std::string, std::string, std::less<std::string> >& map_long_descriptions,
                                  std::vector<std::string>& vec_names,
                                  std::vector<std::string>& vec_status,
                                  std::vector<std::string>& vec_short_descriptions,
                                  std::vector<std::string>& vec_authors,
                                  std::vector<std::string>& vec_long_descriptions) {
      /* Cycle through the map of short descriptions */
      for(std::map<std::string, std::string, std::less<std::string> >::const_iterator it = map_short_descriptions.begin();
          it != map_short_descriptions.end(); ++it) {
         /* If the current plugin name contains the passed query */
         if(it->first.find(str_query) != std::string::npos) {
            const std::string& strName = it->first;
            /* Add the name to the vector of names */
            vec_names.push_back(strName);
            /* Add the short description to the vector of short descriptions */
            vec_short_descriptions.push_back(it->second);
            /* Add the author to the list of authors */
            vec_authors.push_back(map_authors.find(strName)->second);
            /* Add the long description to the vector of long descriptions */
            vec_long_descriptions.push_back(map_long_descriptions.find(strName)->second);
            /* Add the status to the list of status */
            vec_status.push_back(map_status.find(strName)->second);
         }
      }
   }

   /****************************************/
   /****************************************/

   static void QueryShowPluginDescription(const std::string& str_query) {
      LOG << "Plugins matching \"" << str_query << "\":" << std::endl << std::endl;
      /* Buffers to contain the search results */
      std::vector<std::string> vecNames;
      std::vector<std::string> vecStatus;
      std::vector<std::string> vecShortDescriptions;
      std::vector<std::string> vecAuthors;
      std::vector<std::string> vecLongDescriptions;
      /* Search among the actuators */
      QuerySearchPlugins(
         str_query,
         GetActuatorPlugin()->StatusMap,
         GetActuatorPlugin()->ShortDescriptionMap,
         GetActuatorPlugin()->AuthorMap,
         GetActuatorPlugin()->LongDescriptionMap,
         vecNames,
         vecStatus,
         vecShortDescriptions,
         vecAuthors,
         vecLongDescriptions
         );
      /* Search among the sensors */
      QuerySearchPlugins(
         str_query,
         GetSensorPlugin()->StatusMap,
         GetSensorPlugin()->ShortDescriptionMap,
         GetSensorPlugin()->AuthorMap,
         GetSensorPlugin()->LongDescriptionMap,
         vecNames,
         vecStatus,
         vecShortDescriptions,
         vecAuthors,
         vecLongDescriptions
         );
      /* Search among the physics engines */
      QuerySearchPlugins(
         str_query,
         GetPhysicsEnginePlugin()->StatusMap,
         GetPhysicsEnginePlugin()->ShortDescriptionMap,
         GetPhysicsEnginePlugin()->AuthorMap,
         GetPhysicsEnginePlugin()->LongDescriptionMap,
         vecNames,
         vecStatus,
         vecShortDescriptions,
         vecAuthors,
         vecLongDescriptions
         );
      /* Search among the visualizations */
      QuerySearchPlugins(
         str_query,
         GetRendererPlugin()->StatusMap,
         GetRendererPlugin()->ShortDescriptionMap,
         GetRendererPlugin()->AuthorMap,
         GetRendererPlugin()->LongDescriptionMap,
         vecNames,
         vecStatus,
         vecShortDescriptions,
         vecAuthors,
         vecLongDescriptions
         );
      /* Search among the entities */
      QuerySearchPlugins(
         str_query,
         GetEntityPlugin()->StatusMap,
         GetEntityPlugin()->ShortDescriptionMap,
         GetEntityPlugin()->AuthorMap,
         GetEntityPlugin()->LongDescriptionMap,
         vecNames,
         vecStatus,
         vecShortDescriptions,
         vecAuthors,
         vecLongDescriptions
         );
      /* Print the result */
      if(vecNames.empty()) {
         LOG << "   None found." << std::endl << std::endl;
      }
      else {
         LOG << "==============================================================================" << std::endl << std::endl;
         for(UInt32 i = 0; i < vecNames.size(); ++i) {
            LOG << "[ " << vecNames[i] << " ] " << std::endl;
            LOG << vecShortDescriptions[i] << std::endl;
            LOG << "by " << vecAuthors[i] << std::endl;
            LOG << "Status: " << vecStatus[i] << std::endl << std::endl;
            LOG << vecLongDescriptions[i] << std::endl;
            LOG << "==============================================================================" << std::endl << std::endl;
         }
      }
   }

   /****************************************/
   /****************************************/

   static void QueryPlugins(const std::string& str_query) {
      if(str_query == "actuators") {
         QueryShowActuatorList();
      } else if(str_query == "sensors") {
         QueryShowSensorList();
      } else if(str_query == "physics_engines") {
         QueryShowPhysicsEngineList();
      } else if(str_query == "visualizations") {
         QueryShowVisualizationList();
      } else if(str_query == "entities") {
         QueryShowEntityList();
      } else if(str_query == "all") {
         QueryShowActuatorList();
         QueryShowSensorList();
         QueryShowPhysicsEngineList();
         QueryShowVisualizationList();
         QueryShowEntityList();
      } else {
         QueryShowPluginDescription(str_query);
      }

      LOG.Flush();
      LOGERR.Flush();
      exit(0);
   }

   /****************************************/
   /****************************************/

   void CCommandLineArgumentParser::ParseCommandLine(SInt32 n_argument_count, char** ppch_argument_values) {
      /* Display the arguments */
      char pchArgs[1000];
      pchArgs[0] = '\0';
      for(SInt32 i = 0; i < n_argument_count; i++) {
         ::strcat(pchArgs, "\"");
         ::strcat(pchArgs, ppch_argument_values[i]);
         ::strcat(pchArgs, "\"");
         if (i < n_argument_count - 1) ::strcat(pchArgs, ", ");
      }

      SInt32 nNextOption;
      bool bIsConfigFile = false;
      bool bIsQuery = false;
      std::string strQuery;
      bool bPrintUsage = false;
      SInt32 nExitStatus = 0;
      CSimulator& cSimulator = CSimulator::GetInstance();

      do {
         nNextOption = getopt_long(n_argument_count, ppch_argument_values, m_pchShortOptions, m_strLongOptions, NULL);

         switch(nNextOption) {

            case 'h': /* -h or --help */
               bPrintUsage = true;
               break;

            case 'c': /* -c or --config-file */
               bIsConfigFile = true;
               LOG << "[INFO] Configuration file to parse is " << optarg << std::endl;
               cSimulator.SetExperimentFileName(optarg);
               break;

            case 'q': /* -q or --query */
               bIsQuery = true;
               strQuery = optarg;
               break;

            case 'n': /* -n or --no-color */
               LOG.DisableColoredOutput();
               LOGERR.DisableColoredOutput();
               break;

            case '?': /* the user specified an invalid option */
               bPrintUsage = true;
               nExitStatus = -1;
               break;

            case -1: /* Sone with options */
               break;

            default: /* Something unexpected */
               abort();
         }

      } while(nNextOption != -1);

      /* Check required parameters */
      if (!bIsConfigFile && !bIsQuery && !bPrintUsage) {
         LOG.DisableColoredOutput();
         LOGERR.DisableColoredOutput();
         LOGERR << "[FATAL] No --help, --config-file or --query options specified. Aborting." << std::endl << std::endl;
         PrintUsage(LOGERR, 1);
      }

      /* Options --help, --config-file and --query are mutually exclusive */
      if ((bPrintUsage && bIsConfigFile) ||
          (bPrintUsage && bIsQuery) ||
          (bIsConfigFile && bIsQuery)) {
         LOG.DisableColoredOutput();
         LOGERR.DisableColoredOutput();
         LOGERR << "[FATAL] Options --help, --config-file and --query are mutually exclusive. Aborting." << std::endl << std::endl;
         PrintUsage(LOGERR, 1);
      }

      /* Print usage */
      if(bPrintUsage) {
         LOG.DisableColoredOutput();
         LOGERR.DisableColoredOutput();
         PrintUsage(LOG, nExitStatus);
      }

      /* Query the plugins */
      if(bIsQuery) {
         LOG.DisableColoredOutput();
         LOGERR.DisableColoredOutput();
         QueryPlugins(strQuery);
      }

      /* Run the experiment */
      /* Check the presence of the environment variable ARGOSINSTALLDIR */
      char* pch_argos_install_dir = getenv(ARGOSINSTALLDIR.c_str());
      if (pch_argos_install_dir == NULL) {
         LOGERR << "[FATAL] Unable to find the required environment variable " << ARGOSINSTALLDIR << "." << std::endl;
	 LOG.Flush();
	 LOGERR.Flush();
         exit(-1);
      }
      cSimulator.SetInstallationDirectory(pch_argos_install_dir);

      LOG.Flush();
      LOGERR.Flush();
   }

   /****************************************/
   /****************************************/

   void CCommandLineArgumentParser::PrintUsage(CARGoSLog& c_log, SInt32 n_exit_code) {
      c_log << "Usage: argos [OPTIONS]" << std::endl;
      c_log << "The ARGOS simulator, the official simulator of the Swarmanoid Project." << std::endl;
      c_log << "Current version: 2.0" << std::endl;
      c_log << std::endl;
      c_log << "   -h        | --help                  display this usage information" << std::endl;
      c_log << "   -c FILE   | --config-file=FILE      the experiment XML configuration file" << std::endl;
      c_log << "   -q QUERY  | --query=QUERY           query the available plugins." << std::endl;
      c_log << "   -n        | --no-color=FILE         do not use colored output [OPTIONAL]" << std::endl << std::endl;
      c_log << "The options --config-file and --query are mutually exclusive. Either you use" << std::endl;
      c_log << "the first, and thus you run an experiment, or you use the second to query the" << std::endl;
      c_log << "plugins." << std::endl << std::endl;
      c_log << "EXAMPLES" << std::endl << std::endl;
      c_log << "To run an experiment, type:" << std::endl << std::endl;
      c_log << "   ./argos -c /path/to/myconfig.xml" << std::endl << std::endl;
      c_log << "To query the plugins, type:" << std::endl << std::endl;
      c_log << "   ./argos -q QUERY" << std::endl << std::endl;
      c_log << "where QUERY can have the following values:" << std::endl << std::endl;
      c_log << "   all                    print a list of all the available plugins" << std::endl;
      c_log << "   actuators              print a list of all the available actuators" << std::endl;
      c_log << "   sensors                print a list of all the available sensors" << std::endl;
      c_log << "   physics_engines        print a list of all the available physics engines" << std::endl;
      c_log << "   visualizations         print a list of all the available visualizations" << std::endl;
      c_log << "   entities               print a list of all the available entities" << std::endl << std::endl;
      c_log << "Alternatively, QUERY can be the name of a specific plugin as returned by the" << std::endl;
      c_log << "above commands. In this case, you get a complete description of the matching" << std::endl;
      c_log << "plugins." << std::endl << std::endl;
      CSimulator& cSimulator = CSimulator::GetInstance();
      cSimulator.Destroy();

      LOG.Flush();
      LOGERR.Flush();
      exit(n_exit_code);
   }

}

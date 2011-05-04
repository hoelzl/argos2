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
 * @file <simulator/configuration/command_line_argument_parser.h>
 *
 * @brief This file provides the definition of class CCommandLineArgumentParser to handle command line arguments.
 *
 * This file provides the definition of class CCommandLineArgumentParser to
 * handle command line arguments.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef COMMAND_LINE_ARGUMENT_PARSER_H
#define COMMAND_LINE_ARGUMENT_PARSER_H

namespace argos {
   class CCommandLineArgumentParser;
}

#include <argos2/simulator/simulator.h>
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/datatypes/datatypes.h>
#include <getopt.h>
#include <iostream>

namespace argos {

   /**
    * @class CCommandLineArgumentParser
    *
    * @brief This class handles command line arguments.
    *
    * This class handles command line arguments.
    *
    */
   class CCommandLineArgumentParser {

   private:

      /** This string defines the short command line arguments. */
      static const char* const m_pchShortOptions;

      /** This structure contains full information about the available command line arguments. */
      static const struct option m_strLongOptions[];

      // Operations
   public:

      /**
       * @brief Parses the command line and sends information to the core system.
       *
       * Parses the command line and sets sends information to the core system.
       *
       * @param n_argument_count The number of command line arguments given at the shell prompt.
       * @param ppch_argument_values The actual command line arguments.
       *
       * @see simulator/main.cpp
       * @see CSimulator
       */
      static void ParseCommandLine(SInt32 n_argument_count, char** ppch_argument_values);

      /**
       * @brief Prints usage information and exits the simulator.
       *
       * @param pc_log The log stream to print information to (LOG or CSimulatorLogger::LogErr(  )).
       * @param n_exit_code The exit code to return to the operating system.
       *
       * @see CSwarmanoidLogger
       */
      static void PrintUsage(CARGoSLog& c_log, SInt32 n_exit_code);

   };

}
;

#endif

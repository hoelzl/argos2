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
 * @file <simulator/main.cpp>
 *
 * @brief This file provides the standard main() function to run the AHSS
 * simulator.
 *
 * In this file the standard main() function is defined. It provides the
 * basic functionalities to run the AHSS simulator: parses the command line,
 * loads the experiment, runs the simulation and disposes all the data.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include <argos2/simulator/simulator.h>
#include <argos2/simulator/configuration/command_line_argument_parser.h>

/**
 * @brief The standard main() function to run the AHSS simulator.
 *
 * This main() function provides tha basic functionalities to run the AHSS
 * simulator: parses the command line, loads the experiment, runs the
 * simulation and disposes all the data.
 *
 * @param argc the number of command line arguments given at the shell.
 * @param argv the actual command line arguments.
 *
 * @return 0 if everything OK; -1 in case of errors.
 *
 */
int main(int argc, char** argv) {
   argos::CSimulator& cSimulator = argos::CSimulator::GetInstance();
   try {
      argos::CCommandLineArgumentParser::ParseCommandLine(argc, argv);
      cSimulator.LoadExperiment();
      cSimulator.Execute();
      cSimulator.Destroy();
   }
   catch(std::exception& ex) {
      /* A fatal error occurred: dispose of data, print error and exit */
      cSimulator.Destroy();
      argos::LOGERR << "[FATAL] " << ex.what() << std::endl;
      argos::LOG.Flush();
      argos::LOGERR.Flush();
      return -1;
   }
   /* Everything's ok, exit */
   return 0;
}

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
 * @file <simulator/dynamic_linking_manager.cpp>
 *
 * @brief This file provides the implementation of the functionalities to manage dynamic loading of robot controllers.
 *
 * This file defines class CDynamicLinkingManager and a map of registered
 * controllers. Adding controllers to the map, CDynamicLinkingManager provides the
 * functionalities to dynamically load controllers only when really needed -
 * when they are mentioned in the experiment configuration file.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamic_linking_manager.h"
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/string_utilities.h>
#include <argos2/common/control_interface/ci_robot.h>
#include <argos2/simulator/factories/actuators_factory.h>
#include <argos2/simulator/factories/sensors_factory.h>
#include <argos2/simulator/actuators/simulated_actuator.h>
#include <argos2/simulator/sensors/simulated_sensor.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/dynamic_linking/loop_functions.h>
#include <argos2/simulator/physics_engines/physics_engine_entity.h>
#include <argos2/simulator/space/entities/controllable_entity.h>

/* The map of controllers */
std::map<std::string, CCI_Controller_Maker *, std::less<std::string> > mapControllerFactory;

/* The map of loop functions */
std::map<std::string, CLoopFunctions_Maker *, std::less<std::string> > mapLoopFunctionFactory;
   
namespace argos {

   const std::string CONFIGURATION_LIBRARY_PATH = "library_path";
   const std::string CONFIGURATION_LIBRARY_NAME = "library_name";

   /****************************************/
   /****************************************/

   CDynamicLinkingManager::~CDynamicLinkingManager() {
      SInt32 n_errors = 0;

      /* Close dynamic linking */
      for(size_t i = 0; i < m_vecDLControllerHandles.size(); ++i) {

         n_errors = dlclose(m_vecDLControllerHandles[i]);
         if (n_errors) {
            LOGERR << "[ERROR] failed dlclose for controllers." << std::endl;
            exit(1);
         }
      }

      m_vecControllerLibraries.clear();
      m_vecControllerNames.clear();
   }

   /****************************************/
   /****************************************/

   void CDynamicLinkingManager::InitControllerDynamicLinking(TConfigurationNode& t_tree) {
      std::vector<std::string> vec_controller_libraries;
      std::vector<std::string> vec_controller_names;

      /* Parse the tree */
      try {
         m_tControllerConfigurationTree = GetNode(t_tree, "controllers");
         std::string strLibrary;

         TConfigurationNodeIterator tControllerIt;
         for(tControllerIt = tControllerIt.begin(&m_tControllerConfigurationTree);
             tControllerIt != tControllerIt.end();
             ++tControllerIt) {
            GetNodeAttribute<std::string> (*tControllerIt, "library", strLibrary);
            vec_controller_names.push_back(tControllerIt->Value());
            vec_controller_libraries.push_back(strLibrary);
         }
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error initializing controller dynamic linking", ex);
      }

      /* Load the controllers into the manager */
      for(size_t i = 0;
          i < vec_controller_libraries.size() && i < vec_controller_names.size();
          ++i) {
         LoadController(vec_controller_libraries[i], vec_controller_names[i]);
      }

   }

   /****************************************/
   /****************************************/

   bool CDynamicLinkingManager::InitLoopFunctionDynamicLinking(TConfigurationNode& t_tree) {
      TConfigurationNode tLoopFunctionsSubTree;
      try {
         tLoopFunctionsSubTree = GetNode(t_tree, "loop_functions");
      }
      catch(CARGoSException& ex) {
         LOGERR << "[WARNING] No loop functions specified in the <loop_functions> section of the configuration file." << std::endl;
         /* Load the standard loop functions and link them in the simulator */
         LoadLoopFunctions("", "");
         return false;
      }

      try {
         std::string strLibrary;
         GetNodeAttribute(tLoopFunctionsSubTree, "library", strLibrary);
         std::string strLabel;
         GetNodeAttribute(tLoopFunctionsSubTree, "label", strLabel);
         LoadLoopFunctions(strLibrary, strLabel);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error initializing loop functions dynamic linking", ex);
      }
      return true;
   }

   /****************************************/
   /****************************************/

   void CDynamicLinkingManager::LoadController(const std::string& str_controller_library,
                                               const std::string& str_controller_name) {
      /* Add the name and library to the lists, taking care of the $ARGOSINSTALLDIR variable */
      std::string strControllerLibrary(ExpandARGoSInstallDir(str_controller_library));
      m_vecControllerLibraries.push_back(strControllerLibrary);
      m_vecControllerNames.push_back(str_controller_name);

      /* Load the controller handle and add it to the list of handles */
      
      dl_controller = dlopen(strControllerLibrary.c_str(), RTLD_LOCAL | RTLD_NOW);
      if(dl_controller == NULL) {
         THROW_ARGOSEXCEPTION(
               "Failed opening controller library \""
               << strControllerLibrary << "\": " << dlerror()
               << std::endl);
      }
      m_vecDLControllerHandles.push_back(dl_controller);
   }

   /****************************************/
   /****************************************/

   void CDynamicLinkingManager::LoadLoopFunctions(const std::string& str_library_name,
                                                  const std::string& str_label) {
      CLoopFunctions* pcLoopFunctions;

      if (str_library_name != "") {

         /* Load the library handle, taking care of the $ARGOSINSTALLDIR variable */
         dl_loop_functions = dlopen(ExpandARGoSInstallDir(str_library_name).c_str(), RTLD_LOCAL | RTLD_LAZY);
         if(dl_loop_functions == NULL) {
            THROW_ARGOSEXCEPTION("Failed opening loop function library \""
                                 << str_library_name << "\": " << dlerror()
                                 << std::endl);
         }
         
         /* Create the loop functions */
         if(mapLoopFunctionFactory.find(str_label) == mapLoopFunctionFactory.end()) {
            THROW_ARGOSEXCEPTION("Unknown loop function type \"" << str_label
                                 << "\", probably your loop functions have been registered with a different name."
                                 << std::endl);
         }
         pcLoopFunctions = mapLoopFunctionFactory[str_label]();
      }

      else {
         /* No library name passed, create the standard (empty) loop functions */
         LOGERR << "[WARNING] Using standard (empty) loop functions." << std::endl;
         pcLoopFunctions = new CLoopFunctions();
      }

      CSimulator::GetInstance().SetLoopFunctions(*pcLoopFunctions);
   }

   /****************************************/
   /****************************************/

   CCI_Controller* CDynamicLinkingManager::NewController(CEntity& c_entity,
                                                         const std::string& str_controller_id,
                                                         TConfigurationNode& t_controller_parameters_subtree) {
      std::string strControllerName; // to store the name of the controller with the wanted id
      TConfigurationNode tControllerTree; // to store the XML tree of the controller with the wanted id
      try {
         std::string strId; // to search for the controller with the wanted id
         // Cycle through the controllers
         TConfigurationNodeIterator tControllerIterator;
         tControllerIterator = tControllerIterator.begin(&m_tControllerConfigurationTree);
         // Stop when the end is reached or when the wanted id has been found
         while(tControllerIterator != tControllerIterator.end() && strId != str_controller_id) {
            // Get the current node id
            GetNodeAttribute(*tControllerIterator, "id", strId);
            if (strId == str_controller_id) {
               // We found it!
               strControllerName = tControllerIterator->Value(); // store the controller's name
               tControllerTree = *tControllerIterator; // store the controller's tree
            }
            else {
               // Not found, try the next controller
               ++tControllerIterator;
            }
         }
         // The id was found?
         if(strControllerName == "") {
            THROW_ARGOSEXCEPTION("A controller with id \"" << str_controller_id << "\" has not been found");
         }
         // The controller name is correct?
         if(mapControllerFactory.find(strControllerName) == mapControllerFactory.end()) {
            THROW_ARGOSEXCEPTION("Unknown controller type \"" << strControllerName << "\"");
         }

         // Create a controller with the found name
         CCI_Controller* pcController = mapControllerFactory[strControllerName]();
         CCI_Robot* pcRobot = new CCI_Robot();

         // Initialize actuators
         std::string strActuatorName; // used to store the name of the actuator
         std::string strActuatorImplementation; // used to store the implementation of the actuator
         // Cycle through the the tags in the "actuators" subtree
         TConfigurationNode tActuators;
         tActuators = GetNode(tControllerTree, "actuators");
         TConfigurationNodeIterator tActuatorIterator;
         for(tActuatorIterator = tActuatorIterator.begin(&tActuators);
             tActuatorIterator != tActuatorIterator.end();
             ++tActuatorIterator) {
            strActuatorName = tActuatorIterator->Value(); // get the name of the actuator
            GetNodeAttribute(*tActuatorIterator, "implementation", strActuatorImplementation); // get its implementation
            // create the actuator
            CCI_Actuator* pcActuator = CActuatorsFactory::NewActuator(strActuatorName, strActuatorImplementation);
            pcActuator->Init(*tActuatorIterator);
            CSimulatedActuator* pcSimulatedActuator = dynamic_cast<CSimulatedActuator*> (pcActuator);
            pcSimulatedActuator->SetEntity(c_entity);
            pcRobot->AddActuator(strActuatorName, pcActuator);
         }

         // Initialize sensors
         std::string strSensorName; // used to store the name of the sensor
         std::string strSensorImplementation; // used to store the implementation of the sensor
         // Cycle through the the tags in the "actuators" subtree
         TConfigurationNode tSensors;
         tSensors = GetNode(tControllerTree, "sensors");
         TConfigurationNodeIterator tSensorIterator;
         for(tSensorIterator = tSensorIterator.begin(&tSensors);
             tSensorIterator != tSensorIterator.end();
             ++tSensorIterator) {
            strSensorName = tSensorIterator->Value(); // get the name of the sensor
            GetNodeAttribute(*tSensorIterator, "implementation", strSensorImplementation); // get its implementation
            // create the sensor
            CCI_Sensor* pcSensor = CSensorsFactory::NewSensor(strSensorName, strSensorImplementation);
            pcSensor->Init(*tSensorIterator);
            CSimulatedSensor* pcSimulatedSensor = dynamic_cast<CSimulatedSensor*> (pcSensor);
            pcSimulatedSensor->SetEntity(c_entity);
            pcRobot->AddSensor(strSensorName, pcSensor);
         }

         // Initialize the controller
         pcController->SetRobot(*pcRobot);
         pcController->SetControllerId(str_controller_id);
         pcController->GetRobot().SetRobotId(c_entity.GetId());
         pcController->Init(t_controller_parameters_subtree);

         /* Returns the controller */
         return pcController;
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error creating new controller \"" << str_controller_id << "\" for robot \"" << c_entity.GetId() << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CDynamicLinkingManager::Destroy() {
      /* Close dynamic linking */
      for(size_t i = 0; i < m_vecDLControllerHandles.size(); ++i) {
         SInt32 n_cc_errors = dlclose(m_vecDLControllerHandles[i]);
         if (n_cc_errors > 0) {
            LOGERR << "[WARNING] failed dlclose for controller '" << m_vecControllerNames[i] << "'" << std::endl;
         }
      }

      m_vecDLControllerHandles.clear();
      m_vecControllerLibraries.clear();
      m_vecControllerNames.clear();

      if(dl_loop_functions != NULL) {
         SInt32 n_lf_errors = dlclose(dl_loop_functions);
         if (n_lf_errors > 0) {
            LOGERR << "[WARNING] failed dlclose for loop functions" << std::endl;
         }
      }
   }

   /****************************************/
   /****************************************/

}

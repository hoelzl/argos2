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
 * @file <simulator/dynamic_linking_manager.h>
 *
 * @brief This file provides the definition of the functionalities to manage dynamic loading of robot controllers.
 *
 * This file defines class CDynamicLinkingManager and a map of registered
 * controllers. Adding controllers to the map, CDynamicLinkingManager provides the
 * functionalities to dynamically load controllers only when really needed -
 * when they are mentioned in the experiment configuration file.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CDYNAMIC_LINKING_MANAGER_H
#define CDYNAMIC_LINKING_MANAGER_H

#include <dlfcn.h>
#include <vector>
#include <map>

/* To avoid dependency problems when including */
namespace argos {
   class CDynamicLinkingManager;
   class CPhysicsEngineEntity;
   class CEntity;
   class CCI_Controller;
}

#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/common/control_interface/ci_controller.h>

namespace argos {

   /** Tag name in the XML configuration */
   const std::string CONFIGURATION_CONTROLLER_LIBRARY = "library";
   const std::string CONFIGURATION_CONTROLLER_ID = "id";
   const std::string CONFIGURATION_CONTROLLER_PARAMETERS = "parameters";
   const std::string CONFIGURATION_CONTROLLER_ACTUATORS = "actuators";
   const std::string CONFIGURATION_CONTROLLER_ACTUATOR_IMPLEMENTATION = "implementation";
   const std::string CONFIGURATION_CONTROLLER_SENSORS = "sensors";
   const std::string CONFIGURATION_CONTROLLER_SENSOR_IMPLEMENTATION = "implementation";

   /** The maximum number of characters the name of a controller can have. */
   const UInt32 CONTROLLER_NAME_MAX_LEN = 51;

   /**
    * @class CDynamicLinkingManager
    *
    * @brief This class provides the functionalities to dynamically load robot controllers.
    *
    * CDynamicLinkingManager provides the functionalities to dynamically load
    * robot controllers only when really needed - when they are mentioned in
    * the experiment configuration file.
    */
   class CDynamicLinkingManager : public CBaseConfigurableResource {

   protected:

      TConfigurationNode m_tControllerConfigurationTree;

   protected:

      /** A vector of handles internally used to dynamically load the needed controller classes. */
      std::vector<void*> m_vecDLControllerHandles;

      /** The list of robot controller libraries. */
      std::vector<std::string> m_vecControllerLibraries;

      /** The list of robot controller names. */
      std::vector<std::string> m_vecControllerNames;

      void* dl_controller;
      void* dl_loop_functions;

   public:

      /**
       * @brief class Constructor.
       */
      CDynamicLinkingManager() :
         dl_controller(NULL),
         dl_loop_functions(NULL) {
      }

      /**
       * @brief class Destructor.
       */
      virtual ~CDynamicLinkingManager();

      /**
       * @brief Initializes and configures the dynamic loading manager.
       *
       * @param t_configuration_tree The configuration subtree as given by CExperimentConfiguration::GetConfigurationSubTree( CONFIGURATION_CONTROLLERS )
       *
       * @see CExperimentConfiguration::GetConfigurationSubTree(  )
       */
      virtual void Init(TConfigurationNode& t_tree) {}

      /**
       * @brief Initializes and configures the controller dynamic loading manager.
       *
       * @param t_configuration_tree The configuration subtree as given by CExperimentConfiguration::GetConfigurationSubTree( CONFIGURATION_CONTROLLERS )
       *
       * @see CExperimentConfiguration::GetConfigurationSubTree(  )
       */
      void InitControllerDynamicLinking(TConfigurationNode& t_tree);

      /**
       * @brief Initializes and configures the loop function dynamic loading manager.
       *
       * @param t_configuration_tree The configuration subtree as given by CExperimentConfiguration::GetConfigurationSubTree( CONFIGURATION_CONTROLLERS )
       *
       * @see CExperimentConfiguration::GetConfigurationSubTree(  )
       */
      bool InitLoopFunctionDynamicLinking(TConfigurationNode& t_tree);

      /**
       * @brief Returns a new controller of the specified type.
       *
       * @param s_controller_name The registered type name of the controller to create.
       * @param s_robot_id The robot id.
       * @param pc_entity The physics engine entity of the robot
       * @param t_controller_parameters_subtree The configuration XML subtree to pass to the controller Init() method.
       *
       * @return A new controller object of the requested type, or NULL if the type is unknown.
       *
       * @see LoadController()
       */
      CCI_Controller* NewController(CEntity& c_entity,
                                    const std::string& str_controller_id,
                                    TConfigurationNode& t_controller_parameters_subtree);

      /**
       * @brief Disposes all the data about dynamic linking. It does *not* free the controllers created with NewController(  ).
       */
      void Destroy();

      /**
       * @brief Returns the number of registered controllers.
       *
       * @return The number of registered controllers.
       */
      inline size_t GetNumberControllers() const {
         return m_vecDLControllerHandles.size();
      }

      /**
       * @brief Returns an array containing the names of the loaded controllers. The given buffer should be large enough to store the data returned.
       *
       * @param ppch_controller_names a buffer filled with the name of the controllers.
       */
      inline void GetControllerNames(std::vector<std::string>& vec_controller_names) const {
         vec_controller_names = m_vecControllerNames;
      }

   protected:

      /**
       * @brief Loads (i.e. registers) a controller in the manager.
       *
       * @param str_controller_class_name The class name of the robot controller implemented by the user.
       * @param str_controller_name A name to store the controller in the map so that it can be used later to create a new object with NewController(  ).
       *
       * @see NewController(  )
       */
      void LoadController(const std::string& str_controller_class_name, const std::string& str_controller_libraries);

      /**
       * @brief Loads (i.e. registers) the loops functions in the simulator.
       *
       * @param str_library_name The path of the loop function library implemented by the user.
       * @param str_label The name of the loop function implemented by the user.
       *
       * @see NewController(  )
       */
      void LoadLoopFunctions(const std::string& str_library_name, const std::string& str_label);

   };
}

#include <argos2/simulator/dynamic_linking/loop_functions_registration.h>

/** The map of robot controllers. */
extern std::map<std::string, CCI_Controller_Maker *, std::less<std::string> > mapControllerFactory;

/* The map of loop functions */
extern std::map<std::string, CLoopFunctions_Maker *, std::less<std::string> > mapLoopFunctionFactory;

#endif

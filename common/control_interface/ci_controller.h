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
 * @file <common/control_interface/ci_controller.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_CONTROLLER_H
#define CCI_CONTROLLER_H

namespace argos {
   class CCI_Controller;
}

#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/common/utility/configuration/memento.h>
#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/common/control_interface/ci_robot.h>

namespace argos {

   class CCI_Controller : public CBaseConfigurableResource,
                          public CMemento {

   public:

      static const UInt8 RETURN_OK;
      static const UInt8 RETURN_ERROR;
      static const UInt8 RETURN_CONTINUE;
      static const UInt8 RETURN_FINISHED;

   public:

      virtual ~CCI_Controller() {
         if (m_pcRobot != NULL) delete m_pcRobot;
      }

      virtual void Init(TConfigurationNode& t_node) = 0;

      virtual void ControlStep() = 0;

      virtual void Reset() {}

      virtual void Destroy() = 0;

      inline CCI_Robot& GetRobot() {
         return *m_pcRobot;
      }

      inline void SetRobot(CCI_Robot& pc_robot) {
         m_pcRobot = &pc_robot;
      }

      inline const std::string& GetControllerId() const {
         return m_strControllerId;
      }

      inline void SetControllerId(const std::string& str_controller_id) {
         m_strControllerId = str_controller_id;
      }

      inline virtual bool IsControllerFinished() const {
         return false;
      }

      inline virtual void SetOnlineParameters(UInt32 un_num_params,
                                              const Real* pf_params ) {}

      inline virtual void SaveState(CByteArray& c_buffer) {}
      inline virtual void LoadState(CByteArray& c_buffer) {}

   private:

      CCI_Robot* m_pcRobot;
      std::string m_strControllerId;

   };

}

/* Definitions useful for dynamic linking of controllers */
#ifndef CROSSCOMPILING

// typedef to make it easier to set up controller factory
typedef argos::CCI_Controller *CCI_Controller_Maker();

// the actual controller factory
extern std::map<std::string, CCI_Controller_Maker *, std::less<std::string> > mapControllerFactory;

// to add the controller to the factory
#define REGISTER_CONTROLLER(class_name, label)                          \
   extern "C" {                                                         \
      CCI_Controller* class_name ## _maker(){                           \
         return new class_name;                                         \
      }                                                                 \
                                                                        \
      class class_name ## _proxy {                                      \
      public:                                                           \
      class_name ## _proxy(){                                           \
         mapControllerFactory[ label ] = class_name ## _maker;          \
      }                                                                 \
      };                                                                \
      class_name ## _proxy class_name ## _p;                            \
   }

#else

// typedef to make it easier to set up a single controller but with dynamic name
typedef argos::CCI_Controller *CCI_Controller_Maker();

// the actual controller maker
extern "C" {
   extern CCI_Controller_Maker* controllerMaker;
}

#define REGISTER_CONTROLLER(class_name, label)                      \
   extern "C" {                                                     \
   argos::CCI_Controller* class_name ## _maker() {                      \
         return new class_name;                                     \
      }                                                             \
      CCI_Controller_Maker* controllerMaker = class_name ## _maker; \
   }

#endif

#endif

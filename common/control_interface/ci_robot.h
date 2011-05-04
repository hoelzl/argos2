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
 * @file <common/control_interface/ci_robot.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_ROBOT_H
#define CCI_ROBOT_H

#include <map>
#include <string>

/* To avoid dependency problems when including */
namespace argos {
   class CCI_Robot;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

   class CCI_Robot {

   public:

      virtual ~CCI_Robot();

      virtual CCI_Actuator* InsertActuator(const std::string& str_actuator_type) {
          return NULL;
      }

      virtual CCI_Sensor* InsertSensor(const std::string& str_sensor_type) {
          return NULL;
      }

      inline virtual CCI_Actuator* GetActuator(const std::string& str_actuator_type) {
    	  TActuatorMap::const_iterator it = m_mapActuators.find(str_actuator_type);
    	  if (it != m_mapActuators.end()) return it->second;
    	  THROW_ARGOSEXCEPTION("Unknown actuator type " << str_actuator_type << " requested in controller");
      }

      inline virtual CCI_Sensor* GetSensor(const std::string& str_sensor_type) {
    	  TSensorMap::const_iterator it = m_mapSensors.find(str_sensor_type);
    	  if (it != m_mapSensors.end()) return it->second;
    	  THROW_ARGOSEXCEPTION("Unknown sensor type " << str_sensor_type << " requested in controller");
      }

      inline TActuatorMap& GetAllActuators() {
    	  return m_mapActuators;
      }

      inline TSensorMap& GetAllSensors() {
    	  return m_mapSensors;
      }

      inline void AddActuator(const std::string& str_actuator_type,
                                      CCI_Actuator* pc_actuator) {
         m_mapActuators[str_actuator_type] = pc_actuator;
      }

      inline void AddSensor(const std::string& str_sensor_type,
                                    CCI_Sensor* pc_sensor) {
         m_mapSensors[str_sensor_type] = pc_sensor;
      }

      inline const std::string& GetRobotId() const {
         return m_strRobotId;
      }

      inline void SetRobotId(const std::string& str_robot_id) {
         m_strRobotId = str_robot_id;
      }

   protected:

      TActuatorMap m_mapActuators;
      TSensorMap m_mapSensors;

      std::string m_strRobotId;

   };

}

#endif

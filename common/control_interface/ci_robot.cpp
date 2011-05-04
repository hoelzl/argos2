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
 * @file <common/control_interface/ci_robot.cpp>
 *
 * @brief This file provides the implementation of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "ci_robot.h"

namespace argos {

   /****************************************/
   /****************************************/

   CCI_Robot::~CCI_Robot() {
      /* Delete actuators*/
      for(TActuatorMap::iterator itActuators = m_mapActuators.begin();
          itActuators != m_mapActuators.end();
          ++itActuators) {
         delete itActuators->second;
      }
      m_mapActuators.clear();

      /* Delete sensors */
      for(TSensorMap::iterator itSensors = m_mapSensors.begin();
          itSensors != m_mapSensors.end();
          ++itSensors) {
         delete itSensors->second;
      }
      m_mapSensors.clear();
   }

   /****************************************/
   /****************************************/

}

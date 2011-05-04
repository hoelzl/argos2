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
 * @file <common/control_interface/epuck/ci_epuck_proximity_sensor.cpp>
 *
 * @brief This file provides the implementation of the epuck proximity sensor.
 *
 * This file provides the definition of the epuck proximity sensor.
 * The sensors are spaced on a ring around the base of the epuck.
 * Therefore, they do not turn with the turret. The readings are in the
 * following order (seeing the epuck from TOP, battery socket is the BACK):
 *
 *              front
 *
 *              0   7
 *     l     1         6    r
 *     e                    i
 *     f    2           5   g
 *     t                    h
 *             3     4      t
 *
 *              back
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#include "ci_epuck_proximity_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   const UInt16 CCI_EPuckProximitySensor::NUM_READINGS = 8;

   /****************************************/
   /****************************************/

   CCI_EPuckProximitySensor::CCI_EPuckProximitySensor() :
      m_tReadings(NUM_READINGS) {
      // Set the values for the proximity sensor angles
      m_tReadings[7].Angle = CRadians::PI/0.5247f;
      m_tReadings[6].Angle = CRadians::PI/0.5806f;
      m_tReadings[5].Angle = CRadians::PI/0.6667f;
      m_tReadings[4].Angle = CRadians::PI/0.8571f;
      m_tReadings[3].Angle = CRadians::PI/1.2f;
      m_tReadings[2].Angle = CRadians::PI_OVER_TWO;
      m_tReadings[1].Angle = CRadians::PI/3.5999f;
      m_tReadings[0].Angle = CRadians::PI/10.5884f;
   }

   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EPuckProximitySensor::SReading& s_reading) {
      c_os << "SReading("
           << s_reading.Value
           << ","
           << s_reading.Angle
           << ")";
      return c_os;
   }

   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EPuckProximitySensor::TReadings& t_readings) {
      if(! t_readings.empty()) {
         c_os << t_readings[0];
         for(UInt16 i = 1; i < t_readings.size(); ++i) {
            c_os << " " << t_readings[i];
         }
      }
      return c_os;
   }

   /****************************************/
   /****************************************/

}

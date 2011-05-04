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
 * @brief This file provides the interface of the footbot ground sensor.
 *
 * On the robot, there are two kinds of ground sensors.
 *
 * The BASE ground sensors are located on the main PCB, intertwined with the
 * proximity sensors and evenly spaced. They are 8 and are useful for detecting
 * holes.
 *
 * The MOTOR ground sensors are built on the motor PCB and located close to the
 * motors. They are 4 and useful to detect changes in color on the ground (i.e.,
 * for line following).
 *
 * This sensor provides access to the motor sensors. The readings are in the following
 * order (seeing the robot from TOP, battery socket is the BACK):
 *
 *       front
 *
 * l|w          r|w
 * e|h   0  3   i|h
 * f|e          g|e
 * t|e   1  2   h|e
 *  |l          t|l
 *
 *       back
 *
 * @author Carlo Pinciroli <cpinciro@ulb.ac.be>
 */

#include "ci_footbot_motor_ground_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   const UInt32       CCI_FootBotMotorGroundSensor::NUM_READINGS = 4;
   const CRange<Real> CCI_FootBotMotorGroundSensor::FOOTBOT_MOTOR_GROUND_SENSOR_READING_RANGE(0.0f, 1024.0f);

   /****************************************/
   /****************************************/
    
   CCI_FootBotMotorGroundSensor::CCI_FootBotMotorGroundSensor() :
      m_tReadings(NUM_READINGS) {
      // Set the values for the motor ground sensor offset (taken from the CAD model, in cm)
      m_tReadings[0].Offset.Set( 6.3, 1.16);
      m_tReadings[1].Offset.Set(-6.3, 1.16);
      m_tReadings[2].Offset.Set(-6.3,-1.16);
      m_tReadings[3].Offset.Set( 6.3,-1.16);
   }
    
   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_FootBotMotorGroundSensor::SReading& s_reading) {
      c_os << "Value=<" << s_reading.Value
           << ">, Offset=<" << s_reading.Offset << ">";
      return c_os;
   }

   /****************************************/
   /****************************************/
   
   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_FootBotMotorGroundSensor::TReadings& t_readings) {
      if(! t_readings.empty()) {
         c_os << "{ " << t_readings[0].Value << " }";
         for(UInt32 i = 1; i < t_readings.size(); ++i) {
            c_os << " { " << t_readings[0].Value << " }";
         }
         c_os << std::endl;
      }
      return c_os;
   }

   /****************************************/
   /****************************************/
   
}

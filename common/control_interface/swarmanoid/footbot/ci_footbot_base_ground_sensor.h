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
 * @brief This file provides the interface of the footbot base ground sensor.
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
 * This sensor provides access to the base sensors. The readings are in the following
 * order (seeing the robot from TOP, battery socket is the BACK):
 *
 *      front
 *
 *        0      r
 * l    1   7    i
 * e  2       6  g
 * f    3   5    h
 * t      4      t
 *
 *       back
 *
 * @author Carlo Pinciroli <cpinciro@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_BASE_GROUND_SENSOR_H
#define CCI_FOOTBOT_BASE_GROUND_SENSOR_H

namespace argos {
   class CCI_FootBotBaseGroundSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/vector2.h>
#include <vector>

namespace argos {

   class CCI_FootBotBaseGroundSensor : virtual public CCI_Sensor {

   public:

      struct SReading {
         Real Value;
         CVector2 Offset;
	 
         SReading() :
            Value(0.0f) {}
	 
         SReading(Real f_value,
                  const CVector2& c_offset) :
            Value(f_value),
            Offset(c_offset) {}
      };

      static const UInt32 NUM_READINGS;
      typedef std::vector<SReading> TReadings;

      CCI_FootBotBaseGroundSensor();
      virtual ~CCI_FootBotBaseGroundSensor() {}
      
      inline virtual const TReadings& GetReadings() const {
         return m_tReadings;
      }
      
   protected:

      TReadings m_tReadings;

      /* Readings default range */
      static const CRange<Real> FOOTBOT_BASE_GROUND_SENSOR_READING_RANGE;
   };

   std::ostream& operator<<(std::ostream& c_os, const CCI_FootBotBaseGroundSensor::SReading& s_reading);
   std::ostream& operator<<(std::ostream& c_os, const CCI_FootBotBaseGroundSensor::TReadings& t_readings);
}

#endif

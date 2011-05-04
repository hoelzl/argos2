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
 * @file <common/control_interface/epuck/ci_epuck_light_sensor.h>
 *
 * @brief This file provides the implementation of the epuck light sensor.
 *
 * This file provides the definition of the epuck light sensor.
 * The sensors are evenly spaced on a ring around the base of the ropuck.
 * Therefore, they do not turn with the turret. The readings are in the
 * following order (seeing the ropuck from TOP, battery socket is the BACK):
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
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef CCI_EPUCK_LIGHT_SENSOR_H
#define CCI_EPUCK_LIGHT_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EPuckLightSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>
#include <vector>

namespace argos {

   class CCI_EPuckLightSensor : public CCI_Sensor {

   public:

      struct SReading {
         Real Value;
         CRadians Angle;

         SReading() :
            Value(0.0f) {}

         SReading(Real f_value,
                  const CRadians& c_angle) :
            Value(f_value),
            Angle(c_angle) {}

      };

      static const UInt16 NUM_READINGS;
      typedef std::vector<SReading> TReadings;

      CCI_EPuckLightSensor();
      virtual ~CCI_EPuckLightSensor() {
      }

      inline virtual const TReadings& GetReadings() const {
         return m_tReadings;
      }

      inline virtual const Real& GetReading(UInt16 un_counter) const {
         return m_tReadings[un_counter].Value;
      }

      inline virtual const CRadians& GetAngle(UInt16 un_counter) const {
         return m_tReadings[un_counter].Angle;
      }

   protected:

      TReadings m_tReadings;

   };

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EPuckLightSensor::SReading& s_reading);

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EPuckLightSensor::TReadings& t_readings);

}

#endif

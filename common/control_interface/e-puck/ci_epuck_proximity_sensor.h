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
 * @file <common/control_interface/epuck/ci_epuck_proximity_sensor.h>
 *
 * @brief This file provides the definition of the epuck proximity sensor.
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

#ifndef CCI_EPUCK_PROXIMITY_SENSOR_H
#define CCI_EPUCK_PROXIMITY_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EPuckProximitySensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>

namespace argos {

   class CCI_EPuckProximitySensor : public CCI_Sensor {

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

      CCI_EPuckProximitySensor();
      virtual ~CCI_EPuckProximitySensor() {}

      inline virtual const TReadings& GetReadings() const {
         return m_tReadings;
      }

      inline virtual const Real& GetReadings(UInt16 un_counter) const {
         return m_tReadings[un_counter].Value;
      }

   protected:
      
      TReadings m_tReadings;

   };

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EPuckProximitySensor::SReading& s_reading);

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EPuckProximitySensor::TReadings& t_readings);

}

#endif

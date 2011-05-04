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
 * @brief This file provides the interface of the e-puck base ground sensor.
 *
 * The ground sensors are an additional part of the e-pucks.
 * They are located evenly spaced on the front of the robot. They are 3 and are useful for detecting
 * holes or lines that are placed on the ground.
 *
 * This sensor provides access to the base sensors. The readings are in the following
 * order (seeing the robot from TOP):
 *
 *      front
 *
 *      0 1 2    r
 * l             i
 * e             g
 * f             h
 * t             t
 *
 *       back
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef CCI_EPUCK_GROUND_SENSOR_H
#define CCI_EPUCK_GROUND_SENSOR_H

namespace argos {
   class CCI_EPuckGroundSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>
#include <vector>

namespace argos {

   class CCI_EPuckGroundSensor : virtual public CCI_Sensor {

   public:

      struct SReadings {
         Real Left;
         Real Center;
         Real Right;

         SReadings() :
            Left(0.0f),
            Center(0.0f),
            Right(0.0f) {}

         void Reset() {
            Left = 0.0f;
            Center = 0.0f;
            Right = 0.0f;
         }
      };

   public:

      CCI_EPuckGroundSensor() {}
      virtual ~CCI_EPuckGroundSensor() {}

      inline const SReadings& GetReadings() const {
         return m_sReadings;
      }

      inline Real GetLeftReading() const {
         return m_sReadings.Left;
      }

      inline Real GetCentralReading() const {
         return m_sReadings.Center;
      }

      inline Real GetRightReading() const {
         return m_sReadings.Right;
      }

      inline void GetReadingsAsArray(Real* pf_buffer) const {
         pf_buffer[0] = m_sReadings.Left;
         pf_buffer[1] = m_sReadings.Center;
         pf_buffer[2] = m_sReadings.Right;
      }

   protected:

      SReadings m_sReadings;

   };
}

#endif

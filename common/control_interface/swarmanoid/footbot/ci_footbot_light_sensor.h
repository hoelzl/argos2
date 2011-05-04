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
 * @file <common/control_interface/footbot/ci_footbot_light_sensor.h>
 *
 * @brief This file provides the definition of the footbot light sensor.
 *
 * This file provides the definition of the footbot light sensor.
 * The sensors are evenly spaced on a ring around the base of the robot.
 * Therefore, they do not turn with the turret. The readings are normalized
 * between 0 and 1, and are in the following order (seeing the robot from TOP,
 * battery socket is the BACK):
 *
 *              front
 *
 *              0 23
 *            1     22
 *          2         21
 *        3             20      r
 * l    4                 19    i
 * e  5                     18  g
 * f  6                     17  h
 * t    7                 16    t
 *        8             15
 *          9         14
 *            10     13
 *              11 12
 *
 *              back
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_LIGHT_SENSOR_H
#define CCI_FOOTBOT_LIGHT_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_FootBotLightSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>
#include <vector>

namespace argos {

   class CCI_FootBotLightSensor : public CCI_Sensor {

   public:

      static const UInt32 NUM_READINGS;

      /**
       * The DTO of the light sensor. It contains the reading of each sensor and
       * and the angle at which each sensor is placed.
       */
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


      typedef std::vector<SReading> TReadings;

      CCI_FootBotLightSensor();
      virtual ~CCI_FootBotLightSensor() {}

      virtual const TReadings& GetReadings() const {
         return m_tReadings;
      }

   protected:

      TReadings m_tReadings;
      static const CRange<Real> FOOTBOT_LIGHT_SENSOR_RANGE;
   };

   std::ostream& operator<<(std::ostream& c_os, const CCI_FootBotLightSensor::SReading& s_reading);
   std::ostream& operator<<(std::ostream& c_os, const CCI_FootBotLightSensor::TReadings& t_readings);
}

#endif

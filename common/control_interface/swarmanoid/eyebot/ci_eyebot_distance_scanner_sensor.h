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
 * @file <argos2/common/control_interface/eyebot/ci_eyebot_distance_scanner_sensor.h>
 *
 * @brief This file provides the definition of the long range distance scanner.
 * 
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef CI_EYEBOT_DISTANCE_SCANNER_SENSOR_H
#define CI_EYEBOT_DISTANCE_SCANNER_SENSOR_H


/* To avoid dependency problems when including */
namespace argos {

   class CCI_EyeBotDistanceScannerSensor;

}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>
#include <argos2/common/utility/configuration/argos_exception.h>

namespace argos {

   class CCI_EyeBotDistanceScannerSensor: virtual public CCI_Sensor {

   public:

      static const UInt32 NUM_READINGS;
      typedef std::map<CRadians, Real> TReadings;

   public:

      CCI_EyeBotDistanceScannerSensor() {}
      virtual ~CCI_EyeBotDistanceScannerSensor() {}

      virtual const TReadings& GetReadings() const {
         return m_tReadings;
      }

      inline Real GetReading(const CRadians& c_angle) {
         TReadings::const_iterator itValue = m_tReadings.find(c_angle);
         if(itValue != m_tReadings.end()) {
            return itValue->second;
         }
         else {
            THROW_ARGOSEXCEPTION("EyeBot Distance Scanner Sensor: there is no reading for angle " << c_angle);
         }
      }

   protected:

      TReadings m_tReadings;

   };

}

#endif

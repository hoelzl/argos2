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
 * @file <common/control_interface/eyebot/ci_eyebot_distance_Scanner_sensor.h>
 *
 * @brief This file provides the definition of the long range distance scanner 
 * 
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef CCI_EYEBOT_ALTITUDE_SENSOR_H
#define CCI_EYEBOT_ALTITUDE_SENSOR_H


/* To avoid dependency problems when including */
namespace argos {

   class CCI_EyeBotAltitudeSensor;

};

#include <argos2/common/control_interface/ci_sensor.h>

namespace argos {

   class CCI_EyeBotAltitudeSensor: public CCI_Sensor {

   public:

      CCI_EyeBotAltitudeSensor() :
         m_fAltitude(0.0f) {}

      inline virtual Real GetAltitude() {
         return m_fAltitude;
      }

   protected:

      Real m_fAltitude;

   };

};

#endif

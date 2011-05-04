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
 * @file <common/control_interface/swarmanoid/footbot/ci_footbot_turret_encoder_sensor.h>
 *
 * @brief This file provides the common interface definition of the footbot turret encoder
 * sensor. The sensor provides a measure of the rotation of the turret.
 *
 * The turret rotation is expressed in radians [-pi,pi], counter-clockwise positive when
 * looking from above.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_TURRET_ENCODER_SENSOR_H
#define CCI_FOOTBOT_TURRET_ENCODER_SENSOR_H

namespace argos {
   class CCI_FootBotTurretEncoderSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/vector2.h>

namespace argos {

   class CCI_FootBotTurretEncoderSensor : public CCI_Sensor {

   public:

      inline virtual const CRadians& GetRotation() const {
         return m_cRotation;
      }

   protected:

      CRadians m_cRotation;

      /** Define a range for the position */
      static const CRange<CRadians> FOOTBOT_TURRET_ANGULAR_RANGE;

      friend class CCI_FootBotTurretActuator;
      friend class CRealFootBotTurretActuator;

   };

}

#endif

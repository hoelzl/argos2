/* -*- Mode: C++ -*-
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
 * @file <argos2/simulator/sensors/eye-bot/eyebot_altitude_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EYEBOT_ALTITUDE_SENSOR_H
#define EYEBOT_ALTITUDE_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEyeBotAltitudeSensor;
}

#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_altitude_sensor.h>
#include <argos2/simulator/sensors/eye-bot/eyebot_sensor.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>

namespace argos {

   class CEyeBotAltitudeSensor : public CEyeBotSensor,
                                 public CCI_EyeBotAltitudeSensor {

   public:

      virtual ~CEyeBotAltitudeSensor() {}

      virtual void Update();
      virtual void Reset();

   };

}

#endif

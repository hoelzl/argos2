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
 * @file <argos2/simulator/sensors/foot-bot/footbot_encoder_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_ENCODER_SENSOR_H
#define FOOTBOT_ENCODER_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotEncoderSensor;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_encoder_sensor.h>
#include <argos2/simulator/sensors/foot-bot/footbot_sensor.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/wheeled_entity.h>

namespace argos {

   class CFootBotEncoderSensor : public CFootBotSensor,
                                 public CCI_FootBotEncoderSensor {

   public:

      enum EWheels {
         LEFT_WHEEL = 0,
         RIGHT_WHEEL = 1
      };

      CFootBotEncoderSensor();
      virtual ~CFootBotEncoderSensor() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotSensor::SetEntity(c_entity);
         m_pcWheeledEntity = &(GetEntity().GetWheeledEntity());
      }

      virtual void Update();
      virtual void Reset();

   private:

      CWheeledEntity<2>* m_pcWheeledEntity;
      Real m_fWheelSpeed[2];

   };

}

#endif

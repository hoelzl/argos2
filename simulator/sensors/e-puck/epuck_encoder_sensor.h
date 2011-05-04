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
 * @file <argos2/simulator/sensors/e-puck/epuck_encoder_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EPUCK_ENCODER_SENSOR_H
#define EPUCK_ENCODER_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckEncoderSensor;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_encoder_sensor.h>
#include <argos2/simulator/sensors/e-puck/epuck_sensor.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/space/entities/wheeled_entity.h>

namespace argos {

   class CEPuckEncoderSensor : public CEPuckSensor,
                                 public CCI_EPuckEncoderSensor {

   public:

      enum EWheels {
         LEFT_WHEEL = 0,
         RIGHT_WHEEL = 1
      };

      CEPuckEncoderSensor();
      virtual ~CEPuckEncoderSensor() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CEPuckSensor::SetEntity(c_entity);
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

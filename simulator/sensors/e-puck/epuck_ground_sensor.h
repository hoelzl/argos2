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
 * @file <argos2/simulator/sensors/e-puck/epuck_ground_sensor.h>
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef EPUCK_GROUND_SENSOR_H
#define EPUCK_GROUND_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckGroundSensor;
   class CFloorEntity;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_ground_sensor.h>
#include <argos2/simulator/sensors/e-puck/epuck_sensor.h>
#include <argos2/simulator/simulator.h>

namespace argos {

   class CEPuckGroundSensor : public CEPuckSensor,
                              public CCI_EPuckGroundSensor {

   public:

      CEPuckGroundSensor() :
         m_cSpace(CSimulator::GetInstance().GetSpace()) {
         m_cSensorPosOffset[0].Set(0.03f, -0.009f);
         m_cSensorPosOffset[1].Set(0.03f,  0.0f   );
         m_cSensorPosOffset[2].Set(0.03f,  0.009f);
      }

      virtual ~CEPuckGroundSensor() {}

      virtual void Update();
      virtual void Reset();

   private:

      CSpace& m_cSpace;
      CVector2 m_cSensorPosOffset[3];

   };

}

#endif

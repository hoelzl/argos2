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
 * @file <argos2/simulator/generic_actuators/e-puck/epuck_wheels_actuator.h>
 *
 * @brief This file provides the definition of the epuck wheels actuator
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EPUCK_WHEELS_ACTUATOR_H
#define EPUCK_WHEELS_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckWheelsActuator;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_wheels_actuator.h>
#include <argos2/simulator/actuators/e-puck/epuck_actuator.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/space/entities/wheeled_entity.h>

namespace argos {

   class CEPuckWheelsActuator : public CEPuckActuator,
                                  public CCI_EPuckWheelsActuator {

   public:

      enum EPUCK_WHEELS {
         EPUCK_LEFT_WHEEL = 0,
         EPUCK_RIGHT_WHEEL = 1
      };

      CEPuckWheelsActuator();
      virtual ~CEPuckWheelsActuator() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CEPuckActuator::SetEntity(c_entity);
         m_pcWheeledEntity = &(GetEntity().GetWheeledEntity());
      }

      virtual void Init(TConfigurationNode& t_tree);

      virtual void SetLinearVelocity(Real f_left_velocity,
                                     Real f_right_velocity);

      virtual void Update();
      virtual void Reset();

   private:

      CWheeledEntity<2>* m_pcWheeledEntity;
   };

}

#endif

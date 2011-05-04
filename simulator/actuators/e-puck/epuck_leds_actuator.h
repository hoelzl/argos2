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
 * @file <argos2/simulator/actuators/e-puck/epuck_leds_actuator.h>
 *
 * @brief This file provides the definition of the e-puck LEDs actuator.
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef EPUCK_LEDS_ACTUATOR_H
#define EPUCK_LEDS_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckLedsActuator;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_leds_actuator.h>
#include <argos2/simulator/actuators/e-puck/epuck_actuator.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>

namespace argos {

   class CEPuckLedsActuator : public CEPuckActuator,
                              public CCI_EPuckLedsActuator {

   public:

      CEPuckLedsActuator() :
         m_pcLedEquippedEntity(NULL) {}
      virtual ~CEPuckLedsActuator() {}

      virtual void Init(TConfigurationNode& t_tree) {}
      virtual void Destroy() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CEPuckActuator::SetEntity(c_entity);
         m_pcLedEquippedEntity = &(GetEntity().GetLEDEquippedEntity());
      }

      virtual void Update();
      virtual void Reset();

   private:

      CLedEquippedEntity* m_pcLedEquippedEntity;

   };

}

#endif

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
 * @file <argos2/simulator/generic_actuators/e-puck/epuck_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EPUCK_ACTUATOR_H
#define EPUCK_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckActuator;
}

#include <argos2/simulator/actuators/simulated_actuator.h>
#include <argos2/simulator/space/entities/epuck_entity.h>

namespace argos {

   class CEPuckActuator : public CSimulatedActuator {

   public:

      CEPuckActuator() :
         m_pcEPuckEntity(NULL) {}
      virtual ~CEPuckActuator() {}

      inline virtual CEPuckEntity& GetEntity() {
         return *m_pcEPuckEntity;
      }
      inline virtual void SetEntity(CEntity& c_entity) {
         m_pcEPuckEntity = dynamic_cast<CEPuckEntity*>(&c_entity);
         if(m_pcEPuckEntity == NULL) {
            THROW_ARGOSEXCEPTION("Cannot associate a e-puck actuator to a ropuck of type \"" << c_entity.GetTypeDescription() << "\"");
         }
      }

   private:

      CEPuckEntity* m_pcEPuckEntity;

   };

}

#endif

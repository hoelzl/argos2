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
 * @file <argos2/simulator/generic_actuators/eye-bot/eyebot_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EYEBOT_ACTUATOR_H
#define EYEBOT_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEyeBotActuator;
}

#include <argos2/simulator/actuators/simulated_actuator.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>

namespace argos {

   class CEyeBotActuator : public CSimulatedActuator {

   public:

      CEyeBotActuator() :
         m_pcEyeBotEntity(NULL) {}
      virtual ~CEyeBotActuator() {}

      inline virtual CEyeBotEntity& GetEntity() {
         return *m_pcEyeBotEntity;
      }
      inline virtual void SetEntity(CEntity& c_entity) {
         m_pcEyeBotEntity = dynamic_cast<CEyeBotEntity*>(&c_entity);
         if(m_pcEyeBotEntity == NULL) {
            THROW_ARGOSEXCEPTION("Cannot associate an eye-bot actuator to a robot of type \"" << c_entity.GetTypeDescription() << "\"");
         }
      }

   private:

      CEyeBotEntity* m_pcEyeBotEntity;

   };

}

#endif

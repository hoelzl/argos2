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
 * @file <argos2/simulator/generic_actuators/foot-bot/footbot_turret_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_TURRET_ACTUATOR_H
#define FOOTBOT_TURRET_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotTurretActuator;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_actuator.h>
#include <argos2/simulator/actuators/foot-bot/footbot_actuator.h>
#include <argos2/simulator/space/entities/footbot_entity.h>

namespace argos {

   class CFootBotTurretActuator : public CFootBotActuator,
                                  public CCI_FootBotTurretActuator {

   public:

      CFootBotTurretActuator();
      virtual ~CFootBotTurretActuator() {}

      inline virtual void SetRotation(const CRadians& c_angle) {
         m_cDesiredRotation = c_angle;
      }

      virtual void SetRotationSpeed(SInt32 n_speed_pulses);

      inline virtual void SetMode(ETurretModes e_mode) {
         m_eDesiredMode = e_mode;
      }

      virtual void Update();
      virtual void Reset();

   private:

      CRadians        m_cDesiredRotation;
      Real            m_fDesiredRotationSpeed;
      ETurretModes    m_eDesiredMode;

   };

}

#endif

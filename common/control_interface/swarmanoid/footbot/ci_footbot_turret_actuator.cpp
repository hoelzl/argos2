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
 * @file <common/control_interface/footbot/ci_footbot_turret_actuator.cpp>
 *
 * @brief This file provides the definition of the turret actuator. It allows
 * to set the turret rotation angle in the range [-90:90] degrees.
 * If a value outside this range is set, the command is ignored.
 * This is true now due to bugs in the device firmware. In the future, it
 * will be possible to set the angle in the range [-180:180].
 *
 * Additionally, the user can set the turret in blocked or unblocked mode.
 * In unblocked mode, the turret is loose and its rotation angle cannot
 * be set. In blocked mode, the turret rotation can be set and the robot
 * keeps it when pushed. At init, the turret is set to unblocked.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Giovanni Pini   - <gpini@iridia.ulb.ac.be>
 */

#include "ci_footbot_turret_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/

    const CRange<SInt32> CCI_FootBotTurretActuator::FOOTBOT_TURRET_SPEED_RANGE(-4,4);
    const CRange<Real> CCI_FootBotTurretActuator::FOOTBOT_TURRET_NORMALIZED_SPEED_RANGE(-1.0,1.0);

   /****************************************/
   /****************************************/

}

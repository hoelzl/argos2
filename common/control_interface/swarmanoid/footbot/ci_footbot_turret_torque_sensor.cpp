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
 * @file <common/control_interface/footbot/ci_footbot_turret_torque_sensor.cpp>
 *
 * @brief This file provides the common interface definition of the footbot turret torque
 * sensor. The sensor provides measures of the torque and traction applied to the turret.
 *
 * The traction can be retrieved in XY form (a vector containing X and Y components)
 * or in polar form (force and angle).
 *
 * When expressed in X-Y form the convention is the following:
 *
 *
 *        front
 *
 *          ^ X
 *          |
 *          |
 * Y <------|
 *
 *        back
 *
 * Values of the X and Y components are in [-1,1].
 *
 * When expressed in the polar form, the force has to be considered as a traction (pulling) force.
 * The point at which it is applied is determined by its angle: counter-clockwise positive when looking from
 * above, values are expressed in radians and are in the interval [-pi,pi].
 * The magnitude of the force is in [0,1]
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "ci_footbot_turret_torque_sensor.h"

namespace argos {
   
   /****************************************/
    /****************************************/
   
   const CRange<Real>     CCI_FootBotTurretTorqueSensor::FOOTBOT_TURRET_RAW_FORCEXY_RANGE(-1200.0f, 1200.0f);
   const CRange<Real>     CCI_FootBotTurretTorqueSensor::FOOTBOT_TURRET_NORMALIZED_FORCEXY_RANGE(-1.0f, 1.0f);
   const CRange<Real>     CCI_FootBotTurretTorqueSensor::FOOTBOT_TURRET_RAW_POLAR_RANGE(0.0f, 1200.0f);
   const CRange<Real>     CCI_FootBotTurretTorqueSensor::FOOTBOT_TURRET_NORMALIZED_POLAR_RANGE(0.0f, 1.0f);
   const CRange<Real>     CCI_FootBotTurretTorqueSensor::FOOTBOT_TURRET_RAW_FORCE_TORQUE_RANGE(-1200.0f, 1200.0f);
   const CRange<Real>     CCI_FootBotTurretTorqueSensor::FOOTBOT_TURRET_NORMALIZED_TORQUE_RANGE(-1.0f, 1.0f);
   const CRange<CRadians> CCI_FootBotTurretTorqueSensor::FOOTBOT_TURRET_ANGULAR_RANGE(CRadians(-ARGOS_PI), CRadians(ARGOS_PI));

   /****************************************/
   /****************************************/
   
}

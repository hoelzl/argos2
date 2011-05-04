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
 * @file <common/control_interface/swarmanoid/footbot/ci_footbot_turret_encoder_sensor.cpp>
 *
 * @brief This file provides the common interface definition of the footbot turret encoder
 * sensor. The sensor provides a measure of the rotation of the turret.
 *
 * The turret rotation is expressed in radians [-pi,pi], counter-clockwise positive when
 * looking from above.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "ci_footbot_turret_encoder_sensor.h"

namespace argos {
   
   /****************************************/
    /****************************************/
   
   const CRange<CRadians> CCI_FootBotTurretEncoderSensor::FOOTBOT_TURRET_ANGULAR_RANGE(CRadians(-ARGOS_PI), CRadians(ARGOS_PI));
   
   /****************************************/
   /****************************************/
   
}

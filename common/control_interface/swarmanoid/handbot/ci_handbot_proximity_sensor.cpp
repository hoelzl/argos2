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
 * @file <common/control_interface/handbot/ci_handbot_proximity_sensor.cpp>
 *
 * @brief This file provides the implementation of the handbot gripper proximity sensor.
 * There are in total 24 sensors, spread over the two grippers and their claws.
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#include "ci_handbot_proximity_sensor.h"

/****************************************/
/****************************************/

namespace argos {

   /****************************************/
   /****************************************/

   const UInt8 CCI_HandBotProximitySensor::NUM_READINGS_PER_HAND = 12;

   const CRange<Real>  CCI_HandBotProximitySensor::HANDBOT_PROXIMITY_RANGE(0.0,4095.0);

   /****************************************/
   /****************************************/

}


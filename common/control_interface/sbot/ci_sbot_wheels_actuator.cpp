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
 * @file <common/control_interface/sbot/ci_sbot_wheels_actuator.cpp>
 *
 * @brief This file provides the definition of the control interface
 * for the s-bot wheels.
 * 
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_sbot_wheels_actuator.h"
#include <math.h>

Real CCI_SBotWheelsActuator::MAX_ABSOLUTE_SPEED = M_PI*3/2; // rad/s (should approximately corresponds to 40 units on the real s-bot - to be checked!!)

CCI_SBotWheelsActuator::CCI_SBotWheelsActuator() {
  SetActuatorMinValue( -MAX_ABSOLUTE_SPEED );
  SetActuatorMaxValue(  MAX_ABSOLUTE_SPEED );
}

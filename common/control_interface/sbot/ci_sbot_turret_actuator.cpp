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
 * @file <common/control_interface/sbot/ci_sbot_turret_actuator.cpp>
 *
 * @brief This file provides the definition of
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "ci_sbot_turret_actuator.h"
#include <math.h>

/****************************************/
/****************************************/

Real CCI_SBotTurretActuator::SBOT_TURRET_MAX_ROTATION_SPEED = M_PI/6;

CCI_SBotTurretActuator::CCI_SBotTurretActuator() {

}



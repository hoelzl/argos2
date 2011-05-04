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
 * @file <common/control_interface/footbot/ci_footbot_wheels_actuator.cpp>
 *
 * @brief This file provides the definition of the footbot wheels actuator.
 *
 * This file provides the definition of the footbot wheels actuator.
 * This actuator sets the speed of the wheels. On the real robot, the speed is
 * set by a PID controller, which has a specific period here referred to as
 * T_PID. The actual value accepted by the robot as speed is expressed in pulse
 * per pid period.
 * In the common interface, the user can specify the linear velocity of the robot,
 * that is the distance covered by the robot (in cm) per second. This value is
 * related to the pulse input to the motors. Therefore, here we provide conversion
 * factors that are also used in other related sensors, such as the footbot wheel
 * speed sensor and the footbot encoder sensor.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "ci_footbot_wheels_actuator.h"

namespace argos {

    /****************************************/
    /****************************************/

    // minimal and maximal linear speed for the wheels in cm/sec
    Real CCI_FootBotWheelsActuator::MAX_VELOCITY_CM_SEC =  30.0;
    Real CCI_FootBotWheelsActuator::MIN_VELOCITY_CM_SEC = -30.0;

    // period of the PID speed controller, in seconds
    Real CCI_FootBotWheelsActuator::T_PID = 0.005;
    // conversion factors got from experimental data
    Real CCI_FootBotWheelsActuator::CM_TO_PULSE = 24156.0 / 50.0; // [pulse / cm]
    Real CCI_FootBotWheelsActuator::PULSE_TO_CM = 1.0 / CM_TO_PULSE; // [cm / pulse]
    // speed conversion factors
    Real CCI_FootBotWheelsActuator::PULSE_TPID_TO_CM_SEC = PULSE_TO_CM / T_PID;
    Real CCI_FootBotWheelsActuator::CM_SEC_TO_PULSE_TPID = 1.0
                    / PULSE_TPID_TO_CM_SEC;

    const CRange<Real> CCI_FootBotWheelsActuator::FOOTBOT_WHEELS_SPEED_RANGE(MIN_VELOCITY_CM_SEC,MAX_VELOCITY_CM_SEC);

    /****************************************/
    /****************************************/

}

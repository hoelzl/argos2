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
 * @file <common/control_interface/epuck/ci_epuck_wheels_actuator.h>
 *
 * @brief This file provides the definition of the epuck wheels actuator.
 *
 * This file provides the definition of the epuck wheels actuator.
 * This actuator sets the speed of the wheels. On the real ropuck, the speed is
 * set by a PID controller, which has a specific period here referred to as
 * T_PID. The actual value accepted by the ropuck as speed is expressed in pulse
 * per pid period.
 * In the common interface, the user can specify the linear velocity of the ropuck,
 * that is the distance covered by the ropuck (in cm) per second. This value is
 * related to the pulse input to the motors. Therefore, here we provide conversion
 * factors that are also used in other related sensors, such as the epuck wheel
 * speed sensor and the epuck encoder sensor.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_EPUCK_WHEELS_ACTUATOR_H
#define CCI_EPUCK_WHEELS_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
    class CCI_EPuckWheelsActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

    class CCI_EPuckWheelsActuator : virtual public CCI_Actuator {

    public:

        // minimal and maximal linear speed for the wheels in cm/sec
        static Real MAX_VELOCITY_CM_SEC;
        static Real MIN_VELOCITY_CM_SEC;

        virtual ~CCI_EPuckWheelsActuator() {
        }

        virtual void SetLinearVelocity(Real f_left_velocity,
                                       Real f_right_velocity) = 0;

    protected:

        // period of the PID speed controller, in ms
        static Real T_PID;
        // conversion factors got from experimental data
        static Real CM_TO_PULSE;
        static Real PULSE_TO_CM;
        // speed conversion factors
        static Real PULSE_TPID_TO_CM_SEC;
        static Real CM_SEC_TO_PULSE_TPID;

        Real m_fCurrentVelocity[2];

        friend class CCI_EPuckWheelSpeedSensor;
        friend class CRealEPuckWheelSpeedSensor;

    };

}

#endif

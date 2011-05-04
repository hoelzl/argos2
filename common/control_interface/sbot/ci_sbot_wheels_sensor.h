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
 * @file <common/control_interface/sbot/ci_sbot_wheels_sensor.h>
 *
 * @brief This file provides the definition of the sbot wheels sensor.
 * The Sbot Wheels Sensor groups all sensor values specific to the sbot wheels.
 * These values are:
 *  - angular velocity of each wheel (as set by the controller)
 *  - position of each wheel (as read from the encoder sensor)
 *  - torque of each wheel (as read from the torque sensor)
 * Min and max values can be overridden by the XML (see code for tag names).
 *
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef CCI_SBOTWHEELSSENSOR_H
#define CCI_SBOTWHEELSSENSOR_H

/* To avoid dependency problems when including */
namespace argos {
  class CCI_SBotWheelsSensor;
};


#include <argos2/common/control_interface/ci_sensor.h>

namespace argos {
  class CCI_SBotWheelsSensor: public CCI_Sensor {

    Real m_fMinSpeed;
    Real m_fMaxSpeed;

    Real m_fMinPosition;
    Real m_fMaxPosition;

    Real m_fMinTorque;
    Real m_fMaxTorque;


  public:

    static const unsigned int LEFT_WHEEL;
    static const unsigned int RIGHT_WHEEL;

    CCI_SBotWheelsSensor();
    virtual ~CCI_SBotWheelsSensor();

    virtual int Init( const TConfigurationTree t_tree );

    inline Real GetSensorMinSpeed() { return m_fMinSpeed; };
    inline Real GetSensorMaxSpeed() { return m_fMaxSpeed; };

    inline Real GetSensorMinPosition() { return m_fMinPosition; };
    inline Real GetSensorMaxPosition() { return m_fMaxPosition; };

    inline Real GetSensorMinTorque() { return m_fMinTorque; };
    inline Real GetSensorMaxTorque() { return m_fMaxTorque; };

    /**
     * @brief Returns the angular velocity of the wheels.
     * @param f_left_wheel_velocity  pointer to a Real where the velocity of the left wheel is saved to
     * @param f_right_wheel_velocity  pointer to a Real where the velocity of the right wheel is saved to
     */
    virtual void GetWheelsAngularVelocity ( Real* f_left_wheel_velocity, Real* f_right_wheel_velocity ) = 0;

    /**
     * @brief Returns the position of the wheels.
     * @param f_left_wheel_velocity  pointer to a Real where the position of the left wheel is saved to
     * @param f_right_wheel_velocity  pointer to a Real where the position of the right wheel is saved to
     */
    virtual void GetWheelsPosition ( Real* f_left_wheel_position, Real* f_right_wheel_position ) = 0;

    /**
     * @brief Returns the torque of the wheels.
     * @param f_left_wheel_velocity  pointer to a Real where the torque of the left wheel is saved to
     * @param f_right_wheel_velocity  pointer to a Real where the torque of the right wheel is saved to
     */
    virtual void GetWheelsTorque ( Real* f_left_wheel_torque, Real* f_right_wheel_torque ) = 0;

  };
};

#endif

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
 * @file <common/control_interface/sbot/ci_sbot_gripper_actuator.h>
 *
 * @brief This file provides the definition of the gripper actuator. It allows
 * to set the gripper aperture, elevation and aperture torque.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef CCI_SBOTGRIPPERACTUATOR_H
#define CCI_SBOTGRIPPERACTUATOR_H


/* To avoid dependency problems when including */
namespace argos {

  class CCI_SBotGripperActuator;

};

#include <argos2/common/control_interface/ci_actuator.h>


namespace argos {

  class CCI_SBotGripperActuator: public CCI_Actuator {
  private:
    Real m_fMinAperture;
    Real m_fMaxAperture;

    Real m_fThresholdAperture[2];
    bool   m_bUseThresholdAperture;


    Real m_fMinElevation;
    Real m_fMaxElevation;

    Real m_fMinApertureTorque;
    Real m_fMaxApertureTorque;

  public:
    static Real SBOT_GRIPPER_OPEN;
    static Real SBOT_GRIPPER_CLOSED;
    static Real SBOT_GRIPPER_OBJECT_GRIPPED;
    static Real SBOT_GRIPPER_OBJECT_RELEASED;
    static Real SBOT_GRIPPER_APERTURE_DEFAULT;
    static Real SBOT_GRIPPER_APERTURE_MAX_SPEED;

    static Real SBOT_GRIPPER_MIN_DISTANCE;
    static Real SBOT_GRIPPER_MIN_ANGLE;

  public:
    CCI_SBotGripperActuator();
    virtual ~CCI_SBotGripperActuator();

    virtual int Init( const TConfigurationTree t_tree );

    inline Real GetActuatorMinAperture() { return m_fMinAperture; };
    inline Real GetActuatorMaxAperture() { return m_fMaxAperture; };
    inline bool   UseThresholdAperture() { return m_bUseThresholdAperture; }
    inline Real GetThresholdAperture( unsigned int un_threshold ) { return m_fThresholdAperture[un_threshold]; }

    inline Real GetActuatorMinElevation() { return m_fMinElevation; };
    inline Real GetActuatorMaxElevation() { return m_fMaxElevation; };

    inline Real GetActuatorMinApertureTorque() { return m_fMinApertureTorque; };
    inline Real GetActuatorMaxApertureTorque() { return m_fMaxApertureTorque; };

    virtual void SetGripperAperture( const Real& f_aperture ) = 0;
    virtual void SetGripperElevation( const Real f_elevation ) = 0;
    virtual void SetGripperApertureTorque( const Real f_torque ) = 0;
  };

};

#endif

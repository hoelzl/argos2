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
 * @file <common/control_interface/sbot/ci_sbot_gripper_sensor.h>
 *
 * @brief This file provides the definition of a sensor which describes
 * several status properties of the gripper. Notice that not all these
 * functionalities exist in the real hardware.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef CCI_SBOTGRIPPERSENSOR_H
#define CCI_SBOTGRIPPERSENSOR_H

/* To avoid dependency problems when including */
namespace argos {
  class CCI_SBotGripperSensor;
};


#include <argos2/common/control_interface/ci_sensor.h>

namespace argos {
  class CCI_SBotGripperSensor: public CCI_Sensor {

    Real m_fMinAperture;
    Real m_fMaxAperture;

    Real m_fMinElevation;
    Real m_fMaxElevation;

    Real m_fMinElevationTorque;
    Real m_fMaxElevationTorque;

    Real m_fMinElevationMotorTorque;
    Real m_fMaxElevationMotorTorque;


  public:
    CCI_SBotGripperSensor();
    virtual ~CCI_SBotGripperSensor();

    virtual int Init( const TConfigurationTree t_tree );

    inline Real GetSensorMinAperture() { return m_fMinAperture; };
    inline Real GetSensorMaxAperture() { return m_fMaxAperture; };

    inline Real GetSensorMinElevation() { return m_fMinElevation; };
    inline Real GetSensorMaxElevation() { return m_fMaxElevation; };

    inline Real GetSensorMinElevationTorque() { return m_fMinElevationTorque; };
    inline Real GetSensorMaxElevationTorque() { return m_fMaxElevationTorque; };

    inline Real GetSensorMinElevationMotorTorque() { return m_fMinElevationMotorTorque; };
    inline Real GetSensorMaxElevationMotorTorque() { return m_fMaxElevationMotorTorque; };

    /**
     * @brief returns the gripper elevation
     */
    virtual Real GetGripperElevation( void ) = 0;

    /**
     * @brief returns the gripper aperture
     */
    virtual Real GetGripperAperture( void ) = 0;


    /**
     * @brief returns the gripper elevation torque (optical)
     */
    virtual Real GetGripperElevationTorque( void ) = 0;


    /**
     * @brief returns the gripper elevation torque (motor effort)
     */
    virtual Real GetGripperElevationMotorTorque( void ) = 0;

    /*
     * @brief enables the reading from the optical barrier - probably not necessay in the control interface
     */
    // virtual void EnableGripperOpticalBarrier( void ) = 0;

    /*
     * @brief disables the reading from the optical barrier - probably not necessay in the control interface
     */
    // virtual void DisableGripperOpticalBarrier( void ) = 0;

    /**
     * @brief gets the raw readings of the optical barrier
     *
     * @param ambient corresponds to the ambien light perceived by the sensor
     * @param internal corresponds to the light perceived when the internal led is active
     * @param external corresponds to the light perceived when the internal led is active
     * @param combined corresponds to the light perceived when both leds are active (maybe)
     */
    virtual void GetGripperOpticalBarrier( unsigned *ambient, unsigned *internal, unsigned *external, unsigned *combined ) = 0;

    /**
     * @brief pre-processing function to detect the presence of a
     * grippable object within the gripper claws
     *
     * @return true if there is a grippable object, false otherwise
     */
    virtual bool ObjectInGripper( void ) = 0;

    /**
     * @brief pre-processing function to detect is an object is being gripped by the the presence of a
     * grippable object within the gripper claws
     *
     * @return true if there is a grippable object, false otherwise
     */
    virtual bool ObjectIsGripped( void ) = 0;
  };
};

#endif

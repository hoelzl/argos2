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
 * @file <common/control_interface/sbot/ci_sbot_proximity_sensor.h>
 *
 * @brief This file provides the interface of the turret rotation sensor
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef CCI_SBOTTURRETROTATIONSENSOR_H
#define CCI_SBOTTURRETROTATIONSENSOR_H

/* To avoid dependency problems when including */
namespace argos {

  class CCI_SBotTurretRotationSensor;

};

#include <argos2/common/control_interface/ci_sensor.h>



namespace argos {

  class CCI_SBotTurretRotationSensor: public CCI_Sensor {
  protected:
    string       m_sTurretRotationEncoding;

  public:
    CCI_SBotTurretRotationSensor();

    virtual int Init( const TConfigurationTree t_configuration_tree );
    virtual const Real GetTurretRotation( bool standard_reference = true) = 0;

    virtual unsigned int GetNumberOfEncodedReadings( void );
    virtual void EncodeTurretRotation( Real* turret_rotation );
  };

};

#endif

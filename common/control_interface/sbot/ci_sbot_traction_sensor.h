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
 * @file <common/control_interface/sbot/ci_sbot_traction_sensor.h>
 *
 * @brief This file provides the definition of the sbot traction sensor, which
 * can read the internal forces between the tracks and the turret.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef CCI_SBOTTRACTIONSENSOR_H
#define CCI_SBOTTRACTIONSENSOR_H

/* To avoid dependency problems when including */
namespace argos {
  class CCI_SBotTractionSensor;
};

#include <argos2/common/control_interface/ci_sensor.h>



namespace argos {

  class CCI_SBotTractionSensor: public CCI_Sensor {
  protected:
    string       m_sTractionEncoding;

  public:
    CCI_SBotTractionSensor();
    ~CCI_SBotTractionSensor();
    
    virtual int Init( const TConfigurationTree t_configuration_tree );
    virtual void   GetSBotTraction(Real* x, Real* y, bool wrt_chassis = true) = 0;
    virtual Real GetSBotChassisRotation( void ) = 0;
    
    virtual unsigned int GetNumberOfEncodedReadings( void );
    virtual void EncodeRawTraction( Real* pf_buffer );
  };
};

#endif


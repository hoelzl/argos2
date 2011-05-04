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
 * @file <common/control_interface/sbot/ci_sbot_wheels_actuator.h>
 *
 * @brief This file provides the definition of the sbot wheels actuator.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef CCI_SBOTWHEELSACTUATOR_H
#define CCI_SBOTWHEELSACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
  class CCI_SBotWheelsActuator;
};

#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

  class CCI_SBotWheelsActuator: public CCI_Actuator {
  public:
    CCI_SBotWheelsActuator();

    static Real MAX_ABSOLUTE_SPEED;

    virtual void SetSBotWheelsAngularVelocity ( const Real& f_left_wheel_velocity, const Real& f_right_wheel_velocity ) = 0;


    //Functionalities of the sbot API not yet implemented in simulation
    //Uncomment these once you want to implement them also in simulation
    //virtual void SetTrackPosition(Real left, Real right);

  };

};

#endif

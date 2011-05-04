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
 * @brief This file provides the interface of the sbot ground sensor
 *
 * @author Arne Brutschy <arne.brutschy@ulb.ac.be>
 * @author Vito Trianni <vtrianni@istc.cnr.it>
 */

#ifndef _CCI_SBOTGROUNDSENSOR_H_
#define _CCI_SBOTGROUNDSENSOR_H_

/* To avoid dependency problems when including */
namespace argos {
  class CCI_SBotGroundSensor;
};


#include "ci_ground_sensor.h"

namespace argos {

  class CCI_SBotGroundSensor: public CCI_GroundSensor {

    public:

      static const unsigned int NUMBER_OF_GROUND_SENSORS;

      CCI_SBotGroundSensor();

  };
};

#endif

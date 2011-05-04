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
 * @file <common/control_interface/sbot/ci_sbot_slope_sensor.h>
 *
 * @brief This file provides the definition of the sbot slope sensor.
 *
 * @author Eliseo Ferrante - <eferrant@ulb.ac.be>
 */

#ifndef CCI_SBOTSLOPESENSOR_H
#define CCI_SBOTSLOPESENSOR_H

/* To avoid dependency problems when including */
namespace argos {

   class CCI_SBotSlopeSensor;

};

#include <argos2/common/control_interface/ci_sensor.h>



namespace argos {

   class CCI_SBotSlopeSensor: public CCI_Sensor {
	 // Associations
	 // Attributes
	 // Operations

      public:
        /** Read the slope pitch & roll angles of the robot
	\param pitch Pitch in degree pointer. [-180;180]
	\param roll Roll in degree pointer. [-180;180]
        */

        virtual void GetSBotSlope(Real* pitch, Real* roll) = 0;

   };

};

#endif



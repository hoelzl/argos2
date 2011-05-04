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
 * @file <common/control_interface/sbot/ci_sbot_leds_actuator.h>
 *
 * @brief This file provides the definition of sbot leds actuator
 * 
 * @author Alvaro Gutierrez - <aguti@etsit.upm.es>
 */

#ifndef CCI_SBOTLEDSACTUATOR_H
#define CCI_SBOTLEDSACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {

   class CCI_SBotLedsActuator;

};

#include <argos2/common/control_interface/ci_actuator.h>

/* Leds are mounted arround the turrent ring.
 * Number of leds is 8, and is defined on sbot_entity.h on simulator/swarmanoid_space/entities/
 * They are located at fixed angles: (360/NUMBER_OF_LEDS)*i for i in [0:NUMBER_OF_LEDS -1] CounterClockWise.
 *
 * Actuator is registered as :
 * 	REGISTER_ACTUATOR( CGenericSBotLedsActuator, "sbot_leds", "generic_sbot_leds");
 */

namespace argos {

   class CCI_SBotLedsActuator: public CCI_Actuator {

	 // Associations

	 // Attributes

	 // Operations

      public:

   /**
    * 
    * @brief Set one led given by (unLedNumber) of the SBot to the color given by unColor
    * Color has to be in hexadecimal (0xXXXXXX)
    * Leds start from the gripper an goes counterclockwise
    * Number of Leds is defined in sbot_entity.h
    *
    * @param unLedNumber The number of the Led [0:NUMBER_OF_LEDS -1]
    * @param unColor The Color of led
    * 
    * */

        
   virtual void SetSBotLedColor( const unsigned int unLedNumber, const unsigned int unColor ) = 0;
   
   /**
    * 
    * @brief Set all the leds of the SBot to the color given by unColor
    * Color has to be in hexadecimal (0xXXXXXX)
    * Leds start from the gripper an goes counterclockwise
    * Number of Leds is defined in sbot_entity.h
    * 
    * @param unColor The Color of led
    * 
    * */

   virtual void SetSBotLedsColor( const unsigned int unColor ) = 0;

   /**
    * 
    * @brief Set one led given by (unLedNumber) of the SBot to the color given by unColor
    * Color has to be normalized (0-1)
    * Leds start from the gripper an goes counterclockwise
    * Number of Leds is defined in sbot_entity.h
    *
    * @param unLedNumber The number of the Led [0:NUMBER_OF_LEDS -1]
    * @param fRedValue Value normalized [0-1] of Red on the Final Color
    * @param fGreenValue Value normalized [0-1] of Green on the Final Color
    * @param fBlueValue Value normalized [0-1] of Blue on the Final Color
    * 
    * */

   virtual void SetSBotLedColorRGB ( const unsigned int unLedNumber, Real fRedValue, Real fGreenValue, Real fBlueValue) = 0;
   
   /**
    * 
    * @brief Set all the leds of the SBot to the color given by unColor
    * Color has to be normalized (0-1)
    * Leds start from the gripper an goes counterclockwise
    * Number of Leds is defined in sbot_entity.h
    *
    * @param fRedValue Value normalized [0-1] of Red on the Final Color
    * @param fGreenValue Value normalized [0-1] of Green on the Final Color
    * @param fBlueValue Value normalized [0-1] of Blue on the Final Color
    * 
    * */

   virtual void SetSBotLedsColorRGB ( Real fRedValue, Real fGreenValue, Real fBlueValue) = 0;

   // Functionalities of the sbot API not yet implemented in simulation
   // Uncomment these once you want to implement them also in simulation
   // virtual void SetSBotIndividualLedsColor(Real fRedValue[8], Real fGreenValue[8], Real fBlueValue[8]) = 0;

   };

};

#endif

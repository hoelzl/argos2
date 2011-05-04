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
 * @file <argos2/common/control_interface/eyebot/ci_eyebot_leds_actuator.h>
 *
 * @brief This file provides the definition of eyebot leds actuator
 *
 * @author Manuele Brambilla- <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef CCI_EYEBOTLEDSACTUATOR_H
#define CCI_EYEBOTLEDSACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EyeBotLedsActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>
#include <argos2/common/utility/datatypes/color.h>

/*
 *
 * TODO write description
 *
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

namespace argos {

   class CCI_EyeBotLedsActuator: virtual public CCI_Actuator {

   public:

      static const UInt32 NUM_LEDS;

      enum ERingModes {
         BOTH_RINGS_OFF,
         SIDE_RING_ON,
         BOTTOM_RING_ON,
         BOTH_RINGS_ON
      };

      typedef std::vector<CColor> TLedSettings;


   public:

      CCI_EyeBotLedsActuator();
      virtual ~CCI_EyeBotLedsActuator() {}

      /**
       * Sets the color of a single LED.
       */
      virtual void SetSingleColor(UInt32 un_led_number, const CColor& c_color) = 0;

      /**
       * Sets the same color for all LEDs.
       */
      virtual void SetAllColors(const CColor& c_color) = 0;

      /**
       * Sets the colors of all LEDs individually.
       */
      virtual void SetAllColors(const TLedSettings& c_colors);

      /**
       * Sets the intensity of a single LED.
       */
      virtual void SetSingleIntensity(UInt32 un_led_number,
                                      UInt32 un_intensity);

      /**
       * Sets the same intensity for all LEDs.
       */
      virtual void SetAllIntensities(UInt32 un_intensity);

      /**
       * Enables a the different LED rings.
       *  0 = both off
       *  1 = bottom on, side off
       *  2 = side on, bottom off
       *  3 = both on
       */
      virtual void EnableRings(const ERingModes& e_mode) = 0;


   protected:

      TLedSettings m_tLedSettings;

   };

}

#endif

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
 * @file <common/control_interface/handbot/ci_handbot_beacon_leds_actuator.h>
 *
 * @brief This file provides the common interface definition of handbot beacon actuator.
 *
 * This file provides the common interface definition of handbot beacon actuator.
 * The beacon is located on the top part of the launcher, underneath the plastic cone.
 *
 * There are 6 LEDs in the beacon.
 * TODO: add indexing.
 *
 * The user can control the color and the intensity of each LED.
 * Intensity s stored in the alpha channel of the color. If the intensity
 * of the (one of the) LEDs is changed, its value is kept in memory
 * also when the color is changed (i.e SetColor(s) methods do not change
 * the intensity).
 * The method that takes a TLedSettings type as parameter, on the other hand,
 * also changes the intensity of the LEDs. It is up to the user to provide
 * a vector of CColor with the desired intensity if the method is called.
 *
 *
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#ifndef CCI_HANDBOT_BEACON_LEDS_ACTUATOR_H
#define CCI_HANDBOT_BEACON_LEDS_ACTUATOR_H

namespace argos {
    class CCI_HandBotBeaconLedsActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>
#include <argos2/common/utility/datatypes/color.h>

namespace argos {

    class CCI_HandBotBeaconLedsActuator : public CCI_Actuator {

    public:

        /** Number of LEDs */
        static const UInt8 NUM_LEDS;

        /** Desired LEDs colors */
        typedef std::vector<CColor> TLedSettings;

        /**
         *
         * Constructor.
         *
         */
        CCI_HandBotBeaconLedsActuator();

        /**
         *
         * Destructor.
         *
         */
        virtual ~CCI_HandBotBeaconLedsActuator() {
        }

        /**
         *
         * @brief Destroys the actuator.
         * Sets the all LEDs color to black.
         *
         * @see CColor
         *
         */
        inline virtual void  Destroy()
        {
            SetAllColors(CColor::BLACK);
        }

        /**
         *
         * @brief Sets the given LED to the given color.
         *
         * @param un_led_number index of the LED to set.
         * @param c_color color to be set.
         * @see CColor
         *
         */
        virtual void SetSingleColor(const UInt8 un_led_number, const CColor& c_color) = 0;

        /**
         *
         * @brief Sets all the LEds to the same given color
         *
         * @param c_color color to be set.
         * @see CColor
         *
         */
        virtual void SetAllColors(const CColor& c_color) = 0;

        /**
         *
         * @brief Sets all the LEds to the given colors set.
         *
         * @param c_colors colors to be set.
         * @see CColor
         *
         */
        virtual void SetAllColors(const TLedSettings& c_colors) = 0;

        /**
         *
         * @brief Sets the intensity of the specified LED.
         *
         * @param un_led_number led which intensity has to be set.
         * @param un_intensity intensity to be set.
         * @see CColor
         *
         */
        virtual void SetSingleIntensity(const UInt8 un_led_number, const UInt8 un_intensity);

        /**
         *
         * @brief Sets the intensity of all the LEDs.
         *
         * @param un_intensity intensity to be set.
         * @see CColor
         *
         */
        virtual void SetAllIntensities(const UInt8 un_intensity);


    protected:

        TLedSettings m_tLedSettings;

    };

}

#endif

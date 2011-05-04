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
 * @file <common/control_interface/footbot/ci_footbot_leds_actuator.h>
 *
 * @brief This file provides the definition of footbot LEDs actuator.
 *
 * This file provides the definition of footbot LEDs actuator.
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
 * The LEDs are distributed evenly around the robot, in the same module
 * as the gripper. When the gripper rotates, so do the LEDs. The total
 * number of LEDs is 12 and they are distributed as follows:
 *
 *       00 G 11
 *     01       10
 *   02           09
 *   03           08
 *     04       07
 *        05 06
 *
 * The G depicts the gripper. Please notice that in ASEBA the LEDs indexing
 * is opposite to the one here indicated.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 * @author Giovanni Pini   - <gpini@iridia.ulb.ac.be>
 * @author Arne Brutschy - <arne.brutschy@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_LEDS_ACTUATOR_H
#define CCI_FOOTBOT_LEDS_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
    class CCI_FootBotLedsActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>
#include <argos2/common/utility/datatypes/color.h>

namespace argos {

    class CCI_FootBotLedsActuator : virtual public CCI_Actuator {

    public:

        static const UInt8 NUM_LEDS;
        typedef std::vector<CColor> TLedSettings;

        /**
         *
         * @brief Constructor.
         *
         */
        CCI_FootBotLedsActuator();

        /**
         *
         * @brief Destructor.
         *
         */
        virtual ~CCI_FootBotLedsActuator() {
        }

        /**
         *
         * @brief Sets the color of a single LED.
         * The method does not impact on the LED intensity: if the intensity was changed,
         * the method updates the color but preserves the intensity previously set.
         *
         * @param un_led_number LED that must be set
         * @param c_color color to set
         *
         */
        virtual void SetSingleColor(const UInt8 un_led_number,
                                    const CColor& c_color) = 0;

        /**
         *
         * @brief Sets the color of the whole LED ring.
         * All the LEDs in the ring will be lit up in the same color.
         * The method does not impact on the LED intensity: if the intensity was changed,
         * the method updates the color but preserves the intensity previously set.
         *
         * @param c_color color to set
         *
         */
        virtual void SetAllColors(const CColor& c_color) = 0;

        /**
         *
         * @brief Sets the color of the whole LED ring.
         * All the LEDs in the ring will be lit up, it is possible
         * to have a different color for each LED. Notice that the method
         * also impacts on the intensity of the LED color: it is up to
         * the user to modulate the alpha channel of the color if
         * intensity reduction is needed.
         *
         * @param c_colors color to set for each LED.
         *
         */
        virtual void SetAllColors(const TLedSettings& c_colors) = 0;

        /**
         *
         * @brief Sets the intensity of a single LED in the ring.
         * Intensity is expressed in [0-255].
         *
         * @param un_led_number index of the LED whose intensity must be set.
         * @param un_intensity color to set for each LED.
         *
         */
        virtual void SetSingleIntensity(const UInt8 un_led_number,
                                        const UInt8 un_intensity);

        /**
         *
         * @brief Sets the intensity of all the LEDs in the ring.
         * Intensity is expressed in [0-255].
         *
         * @param un_intensity color to set for each LED.
         *
         */
        virtual void SetAllIntensities(const UInt8 un_intensity);

    protected:

        TLedSettings m_tLedSettings;

    };

}

#endif

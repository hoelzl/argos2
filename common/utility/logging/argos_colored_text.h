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
 * @file <common/logging/argos_colored_text.h>
 *
 * @brief This file provides a list of functions to add colors to std::ostreams.
 *
 * This file provides a list of functions to add colors to std::ostreams.
 * Credit for some of the ideas in this file to Vincent Godin.
 * http://www.codeproject.com/KB/cpp/cout_color.aspx (accessed May 10th, 2010)
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef ARGOS_COLORED_TEXT_H
#define ARGOS_COLORED_TEXT_H

#include <argos2/common/utility/datatypes/datatypes.h>

namespace argos {

    enum EARGoSLogAttributes {
        ARGOS_LOG_ATTRIBUTE_RESET = 0,
        ARGOS_LOG_ATTRIBUTE_BRIGHT = 1,
        ARGOS_LOG_ATTRIBUTE_DIM = 2,
        ARGOS_LOG_ATTRIBUTE_UNDERSCORE = 3,
        ARGOS_LOG_ATTRIBUTE_BLINK = 5,
        ARGOS_LOG_ATTRIBUTE_REVERSE = 7,
        ARGOS_LOG_ATTRIBUTE_HIDDEN = 8
    };

    enum EARGoSLogColors {
        ARGOS_LOG_COLOR_BLACK = 0,
        ARGOS_LOG_COLOR_RED = 1,
        ARGOS_LOG_COLOR_GREEN = 2,
        ARGOS_LOG_COLOR_YELLOW = 3,
        ARGOS_LOG_COLOR_BLUE = 4,
        ARGOS_LOG_COLOR_MAGENTA = 5,
        ARGOS_LOG_COLOR_CYAN = 6,
        ARGOS_LOG_COLOR_WHITE = 7
    };

    struct SLogColor {
        UInt8 Attribute;
        UInt8 Foreground;
        UInt8 Background;

        SLogColor() :
            Attribute(ARGOS_LOG_ATTRIBUTE_RESET),
            Foreground(ARGOS_LOG_COLOR_WHITE),
            Background(ARGOS_LOG_COLOR_BLACK) {}

        SLogColor(EARGoSLogAttributes e_attribute,
                  EARGoSLogColors e_foreground_color,
                  EARGoSLogColors e_background_color) :
            Attribute(e_attribute),
            Foreground(e_foreground_color),
            Background(e_background_color) {}
    };

    inline std::ostream& operator<<(std::ostream& c_os, const SLogColor& s_log_color)
    {
        c_os << "\033["
             << s_log_color.Attribute << ";"
             << (s_log_color.Foreground + 30) << ";"
             << (s_log_color.Background + 40) << "m";
        return c_os;
    }

#define DEFINE_ARGOS_STREAM_COLOR_HELPER(lc_color, uc_color) \
    inline std::ostream& lc_color(std::ostream& c_os) { \
        c_os << SLogColor(ARGOS_LOG_ATTRIBUTE_BRIGHT, ARGOS_LOG_COLOR_ ## uc_color, ARGOS_LOG_COLOR_BLACK); \
        return c_os; \
    }

    DEFINE_ARGOS_STREAM_COLOR_HELPER(red, RED);
    DEFINE_ARGOS_STREAM_COLOR_HELPER(green, GREEN);
    DEFINE_ARGOS_STREAM_COLOR_HELPER(yellow, YELLOW);
    DEFINE_ARGOS_STREAM_COLOR_HELPER(blue, BLUE);
    DEFINE_ARGOS_STREAM_COLOR_HELPER(magenta, MAGENTA);
    DEFINE_ARGOS_STREAM_COLOR_HELPER(cyan, CYAN);
    DEFINE_ARGOS_STREAM_COLOR_HELPER(white, WHITE);

    inline std::ostream& reset(std::ostream& c_os) {
        c_os << SLogColor(ARGOS_LOG_ATTRIBUTE_RESET, ARGOS_LOG_COLOR_WHITE, ARGOS_LOG_COLOR_BLACK);
        return c_os;
    }

}

#endif

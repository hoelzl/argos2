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
 * @file <argos2/common/utility/datatypes/color.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCOLOR_H
#define CCOLOR_H

#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/common/utility/string_utilities.h>
#include <string.h>
#include <iostream>


namespace argos {

   class CColor {

   public:

      static CColor BLACK;
      static CColor WHITE;
      static CColor RED;
      static CColor GREEN;
      static CColor BLUE;
      static CColor MAGENTA;
      static CColor CYAN;
      static CColor YELLOW;
      static CColor ORANGE;
      static CColor GRAY10;
      static CColor GRAY20;
      static CColor GRAY30;
      static CColor GRAY40;
      static CColor GRAY50;
      static CColor GRAY60;
      static CColor GRAY70;
      static CColor GRAY80;
      static CColor GRAY90;

      CColor() {}

      explicit CColor(const UInt8 un_red,
                      const UInt8 un_green,
                      const UInt8 un_blue,
                      const UInt8 un_alpha = 255) :
         m_tChannels(un_red, un_green, un_blue, un_alpha) {}

      inline Real ToGrayScale() const {
         return
            0.299f * m_tChannels.m_unRed +
            0.587f * m_tChannels.m_unGreen +
            0.114f * m_tChannels.m_unBlue;
      }

      inline UInt8 GetRed() const { return m_tChannels.m_unRed; }
      inline void SetRed(const UInt8 un_red) { m_tChannels.m_unRed = un_red; }

      inline UInt8 GetGreen() const { return m_tChannels.m_unGreen; }
      inline void SetGreen(const UInt8 un_green) { m_tChannels.m_unGreen = un_green; }

      inline UInt8 GetBlue() const { return m_tChannels.m_unBlue; }
      inline void SetBlue(const UInt8 un_blue) { m_tChannels.m_unBlue = un_blue; }

      inline UInt8 GetAlpha() const { return m_tChannels.m_unAlpha; }
      inline void SetAlpha(const UInt8 un_alpha) { m_tChannels.m_unAlpha = un_alpha; }

      inline void Set(const UInt8 un_red,
                      const UInt8 un_green,
                      const UInt8 un_blue,
                      const UInt8 un_alpha = 255) {
         SetRed(un_red);
         SetGreen(un_green);
         SetBlue(un_blue);
         SetAlpha(un_alpha);
      }

      inline operator UInt32()
      {
         return *reinterpret_cast<UInt32*>(&m_tChannels);
      }

      inline bool operator==(const CColor& c_color2) const
      {
         return m_tChannels == c_color2.m_tChannels;
      }

      inline bool operator!=(const CColor& c_color2) const
      {
         return m_tChannels != c_color2.m_tChannels;
      }

      friend std::ostream& operator<<(std::ostream& os, const CColor& c_color)
      {
         if      (c_color == CColor::BLACK)   os << "black";
         else if (c_color == CColor::WHITE)   os << "white";
         else if (c_color == CColor::RED)     os << "red";
         else if (c_color == CColor::GREEN)   os << "green";
         else if (c_color == CColor::BLUE)    os << "blue";
         else if (c_color == CColor::MAGENTA) os << "magenta";
         else if (c_color == CColor::CYAN)    os << "cyan";
         else if (c_color == CColor::YELLOW)  os << "yellow";
         else if (c_color == CColor::ORANGE)  os << "orange";
         else if (c_color == CColor::GRAY10)  os << "gray10";
         else if (c_color == CColor::GRAY20)  os << "gray20";
         else if (c_color == CColor::GRAY30)  os << "gray30";
         else if (c_color == CColor::GRAY40)  os << "gray40";
         else if (c_color == CColor::GRAY50)  os << "gray50";
         else if (c_color == CColor::GRAY60)  os << "gray60";
         else if (c_color == CColor::GRAY70)  os << "gray70";
         else if (c_color == CColor::GRAY80)  os << "gray80";
         else if (c_color == CColor::GRAY90)  os << "gray90";
         else {
            os << c_color.m_tChannels.m_unRed
               << "," << c_color.m_tChannels.m_unGreen
               << "," << c_color.m_tChannels.m_unBlue
               << "," << c_color.m_tChannels.m_unAlpha;
         }
         return os;
      }

      friend std::istream& operator>>(std::istream& is,
                                      CColor& c_color) {
         try {
            std::string strColor;
            is >> strColor;
            if      (strColor == "black")   c_color = CColor::BLACK;
            else if (strColor == "white")   c_color = CColor::WHITE;
            else if (strColor == "red")     c_color = CColor::RED;
            else if (strColor == "green")   c_color = CColor::GREEN;
            else if (strColor == "blue")    c_color = CColor::BLUE;
            else if (strColor == "magenta") c_color = CColor::MAGENTA;
            else if (strColor == "cyan")    c_color = CColor::CYAN;
            else if (strColor == "yellow")  c_color = CColor::YELLOW;
            else if (strColor == "orange")  c_color = CColor::ORANGE;
            else if (strColor == "gray10")  c_color = CColor::GRAY10;
            else if (strColor == "gray20")  c_color = CColor::GRAY20;
            else if (strColor == "gray30")  c_color = CColor::GRAY30;
            else if (strColor == "gray40")  c_color = CColor::GRAY40;
            else if (strColor == "gray50")  c_color = CColor::GRAY50;
            else if (strColor == "gray60")  c_color = CColor::GRAY60;
            else if (strColor == "gray70")  c_color = CColor::GRAY70;
            else if (strColor == "gray80")  c_color = CColor::GRAY80;
            else if (strColor == "gray90")  c_color = CColor::GRAY90;
            else {
               UInt8 unValues[4];
               ParseValues<UInt8>(strColor, 4, unValues, ',');
               c_color.Set(unValues[0], unValues[1], unValues[2], unValues[3]);
            }
         }
         catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED("Error while parsing color input string", ex);
         }
         return is;
      }


   private:

      struct TChannels {
         UInt8 m_unRed;
         UInt8 m_unGreen;
         UInt8 m_unBlue;
         UInt8 m_unAlpha;

         TChannels() :
            m_unRed(0),
            m_unGreen(0),
            m_unBlue(0),
            m_unAlpha(255) {}

         TChannels(const UInt8 un_red,
                   const UInt8 un_green,
                   const UInt8 un_blue,
                   const UInt8 un_alpha = 255) :
            m_unRed(un_red),
            m_unGreen(un_green),
            m_unBlue(un_blue),
            m_unAlpha(un_alpha) {}

         inline bool operator==(const TChannels& t_channels) const {
            return
               (m_unRed == t_channels.m_unRed) &&
               (m_unGreen == t_channels.m_unGreen) &&
               (m_unBlue == t_channels.m_unBlue) &&
               (m_unAlpha == t_channels.m_unAlpha);
         }

         inline bool operator!=(const TChannels& t_channels) const {
            return
               (m_unRed != t_channels.m_unRed) ||
               (m_unGreen != t_channels.m_unGreen) ||
               (m_unBlue != t_channels.m_unBlue) ||
               (m_unAlpha != t_channels.m_unAlpha);
         }

      } m_tChannels;

   };

}

#endif

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
 * @file <common/utility/datatypes/datatypes.h>
 *
 * @brief This file provides
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>

namespace argos {

#ifdef ARGOS_DOUBLE_PRECISION
   typedef double Real;
#else
   typedef float Real;
#endif

   typedef signed char SInt8;
   inline std::ostream& operator<<(std::ostream& c_os, const SInt8 n_value) {
       c_os << static_cast<signed int>(n_value);
       return c_os;
   }
   typedef unsigned char UInt8;
   inline std::ostream& operator<<(std::ostream& c_os, const UInt8 un_value) {
       c_os << static_cast<unsigned int>(un_value);
       return c_os;
   }

   typedef signed short SInt16;
   typedef unsigned short UInt16;

   typedef signed int SInt32;
   typedef unsigned int UInt32;

   typedef signed long long SInt64;
   typedef unsigned long long UInt64;

}

#endif

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

#ifndef GENERAL_H
#define GENERAL_H

#include <argos2/common/utility/datatypes/datatypes.h>

namespace argos {

   /****************************************/
   /****************************************/

   template<typename T> T Abs(const T& t_v) {
      if(t_v > T(0)) return t_v;
      if(t_v < T(0)) return -t_v;
      return T(0);
   }

   inline SInt32 Abs(SInt32 t_v) {
      if(t_v > 0) return t_v;
      if(t_v < 0) return -t_v;
      return 0;
   }

   inline Real Abs(Real t_v) {
      if(t_v > 0.0f) return t_v;
      if(t_v < 0.0f) return -t_v;
      return 0.0f;
   }

   /****************************************/
   /****************************************/

   template<typename T> T Min(const T& t_v1, const T& t_v2) {
      return t_v1 < t_v2 ? t_v1 : t_v2;
   }

   template<typename T> T& Min(T& t_v1, T& t_v2) {
      return t_v1 < t_v2 ? t_v1 : t_v2;
   }

   template<typename T> T Max(const T& t_v1, const T& t_v2) {
      return t_v1 > t_v2 ? t_v1 : t_v2;
   }

   template<typename T> T& Max(T& t_v1, T& t_v2) {
      return t_v1 > t_v2 ? t_v1 : t_v2;
   }

   /****************************************/
   /****************************************/

   template<typename T> SInt32 Sign(const T& t_v) {
      if(t_v > T(0)) return 1;
      if(t_v < T(0)) return -1;
      return 0;
   }

   /****************************************/
   /****************************************/

   template<typename T> T Square(const T& t_v) {
      return t_v * t_v;
   }

   /****************************************/
   /****************************************/

   /* Profiled, it takes 50% of the time of ::floor() */
   inline SInt32 Floor(Real f_value) {
      SInt32 nI = static_cast<SInt32>(f_value);
      if(f_value >= 0.0f) return nI;
      return nI - 1;
   }

   /* Profiled, it takes 50% of the time of ::ceil() */
   inline SInt32 Ceil(Real f_value) {
      SInt32 nI = static_cast<SInt32>(f_value);
      if(nI < f_value) return nI + 1;
      return nI;
   }

   inline SInt32 RoundClosestToZero(Real f_value) {
      if(f_value > 0.0f) return Floor(f_value);
      return Ceil(f_value);
   }

   /****************************************/
   /****************************************/

   inline bool DoubleEq(Real f_value1, Real f_value2){
      return Abs(f_value1 - f_value2) <= 0.0001f * Max(1.0f, Max(Abs(f_value1), Abs(f_value2)));
   }

   inline bool DoubleEqAbsolute(Real f_value1, Real f_value2, Real f_epsilon ){
      return Abs(f_value1 - f_value2) <= f_epsilon * Max (1.0f, Max(Abs(f_value1), Abs(f_value2)));
   }

   /****************************************/
   /****************************************/

}

#endif

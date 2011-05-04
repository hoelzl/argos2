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
 * @file <common/utility_classes/frac_time.cpp>
 *
 * @brief This file provides the implementation of a class that implements
 * time with a finer granularity than the simulation clock tick.
 *
 * @author Frederick Ducatelle - <frederick@idsia.ch>
 */

#include "frac_time.h"
#include <argos2/common/utility/logging/argos_log.h>

namespace argos {

   /****************************************/
   /****************************************/

   CFracTime::CFracTime() {
      m_nClockTick = 0;
      m_fClockTickFraction = 0;
   }

   /****************************************/
   /****************************************/

   CFracTime::CFracTime(UInt32 tick, Real fraction) {
      m_nClockTick = tick;
      m_fClockTickFraction = fraction;
      m_nClockTick += static_cast<SInt32> (fraction);
      m_fClockTickFraction -= static_cast<SInt32> (fraction);
   }

   /****************************************/
   /****************************************/

   CFracTime::~CFracTime() {
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetFracTime(const CFracTime& rcFracTime) {
      m_nClockTick = rcFracTime.m_nClockTick;
      m_fClockTickFraction = rcFracTime.m_fClockTickFraction;
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetFracTime(UInt32 tick, Real fraction) {
      m_nClockTick = tick;
      m_fClockTickFraction = fraction;
      m_nClockTick += static_cast<SInt32> (fraction);
      m_fClockTickFraction -= static_cast<SInt32> (fraction);
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetClockTick(UInt32 tick) {
      m_nClockTick = tick;
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetClockTickFraction(Real fraction) {
      m_fClockTickFraction = fraction;
      m_nClockTick += static_cast<SInt32> (fraction);
      m_fClockTickFraction -= static_cast<SInt32> (fraction);
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetToMax(const CFracTime& rcFracTime1,
                            const CFracTime& rcFracTime2) {
      if (rcFracTime1 < rcFracTime2) {
         SetFracTime(rcFracTime2);
      }
      else {
         SetFracTime(rcFracTime1);
      }
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetToMax(const CFracTime& rcFracTime, UInt32 tick) {
      if (rcFracTime < tick) {
         SetFracTime(tick, 0);
      }
      else {
         SetFracTime(rcFracTime);
      }
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetToMax(const CFracTime& rcFracTime) {
      if ((*this) < rcFracTime) {
         SetFracTime(rcFracTime);
      }
   }

   /****************************************/
   /****************************************/

   void CFracTime::SetToMax(UInt32 tick) {
      if ((*this) < tick) {
         SetFracTime(tick, 0);
      }
   }

   /****************************************/
   /****************************************/

   UInt32 CFracTime::GetClockTick() {
      return m_nClockTick;
   }

   /****************************************/
   /****************************************/

   Real CFracTime::GetClockTickFraction() {
      return m_fClockTickFraction;
   }

   /****************************************/
   /****************************************/

   void CFracTime::AddClockTick(UInt32 tick) {
      m_nClockTick += tick;
   }

   /****************************************/
   /****************************************/

   void CFracTime::AddClockTickFraction(Real fraction) {
      m_fClockTickFraction += fraction;
      m_nClockTick += static_cast<SInt32> (m_fClockTickFraction);
      m_fClockTickFraction -= static_cast<SInt32> (m_fClockTickFraction);
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator==(const CFracTime& rcFracTime) const {
      return ((m_nClockTick == rcFracTime.m_nClockTick)
               && (m_fClockTickFraction == rcFracTime.m_fClockTickFraction));
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator!=(const CFracTime& rcFracTime) const {
      return ((m_nClockTick != rcFracTime.m_nClockTick)
               || (m_fClockTickFraction != rcFracTime.m_fClockTickFraction));
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator>(const CFracTime& rcFracTime) const {
      return (m_nClockTick == rcFracTime.m_nClockTick) ? (m_fClockTickFraction
               > rcFracTime.m_fClockTickFraction) : (m_nClockTick
               > rcFracTime.m_nClockTick);
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator>(UInt32 tick) const {
      return (m_nClockTick == tick) ? m_fClockTickFraction > 0 : m_nClockTick
               > tick;
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator<(const CFracTime& rcFracTime) const {
      return (m_nClockTick == rcFracTime.m_nClockTick) ? (m_fClockTickFraction
               < rcFracTime.m_fClockTickFraction) : (m_nClockTick
               < rcFracTime.m_nClockTick);
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator<(UInt32 tick) const {
      return (m_nClockTick < tick);
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator>=(const CFracTime& rcFracTime) const {
      return (m_nClockTick == rcFracTime.m_nClockTick) ? (m_fClockTickFraction
               >= rcFracTime.m_fClockTickFraction) : (m_nClockTick
               > rcFracTime.m_nClockTick);
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator>=(UInt32 tick) const {
      return (m_nClockTick >= tick);
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator<=(const CFracTime& rcFracTime) const {
      return (m_nClockTick == rcFracTime.m_nClockTick) ? (m_fClockTickFraction
               <= rcFracTime.m_fClockTickFraction) : (m_nClockTick
               < rcFracTime.m_nClockTick);
   }

   /****************************************/
   /****************************************/

   bool CFracTime::operator<=(UInt32 tick) const {
      return (m_nClockTick == tick) ? (m_fClockTickFraction == 0)
               : (m_nClockTick < tick);
   }

   /****************************************/
   /****************************************/

   CFracTime& CFracTime::operator=(const CFracTime& rcFracTime) {
      m_nClockTick = rcFracTime.m_nClockTick;
      m_fClockTickFraction = rcFracTime.m_fClockTickFraction;
      return *this;
   }

   /****************************************/
   /****************************************/

   CFracTime& CFracTime::operator+=(const CFracTime& rcFracTime) {
      m_nClockTick += rcFracTime.m_nClockTick;
      m_fClockTickFraction += rcFracTime.m_fClockTickFraction;
      m_nClockTick += static_cast<int> (m_fClockTickFraction);
      m_fClockTickFraction -= static_cast<int> (m_fClockTickFraction);
      return *this;
   }

   /****************************************/
   /****************************************/

   CFracTime CFracTime::operator+(const CFracTime& rcFracTime) const {
      return CFracTime((m_nClockTick + rcFracTime.m_nClockTick),
                       (m_fClockTickFraction + rcFracTime.m_fClockTickFraction));
   }

/****************************************/
/****************************************/

}

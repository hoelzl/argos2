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
 * @file <common/utility_classes//frac_time.h>
 *
 * @brief This file provides the definition of a class that implements time
 * with a finer granularity than the simulation clock tick: it stores an
 * (unsigned long) int representing a clock tick and a Real representing a
 * fraction of a clock tick (not a fraction of a second or so!).
 *
 * @author Frederick Ducatelle - <frederick@idsia.ch>
 */

#ifndef _C_FRACTIME_H_
#define _C_FRACTIME_H_

namespace argos {
   class CFracTime;
}

#include <argos2/common/utility/datatypes/datatypes.h>

namespace argos {

   /*
    * This class expresses time with a finer granularity than just the
    * number of clock ticks. In particular, it contains the number of clock
    * ticks and a Real expressing an additional fraction of a clock tick.
    * This way, you can express e.g. that you are in timestep 208.0035. It is
    * developed for use in the wifi radio simulator, that typically works
    * with much smaller scales of time that the simulation of physical
    * movements.
    *
    */
   class CFracTime {

   private:

      UInt32 m_nClockTick;
      Real m_fClockTickFraction; /**< Expresses the decimal part of the clock ticks, is \in [0,1[ */

      // Operations

   public:

      CFracTime();
      CFracTime(UInt32 tick, Real fraction);
      ~CFracTime();

      void SetFracTime(const CFracTime& rcFracTime);
      void SetFracTime(UInt32 tick, Real fraction);
      void SetClockTick(UInt32 tick);
      void SetClockTickFraction(Real fraction);
      void SetToMax(const CFracTime& rcFracTime1, const CFracTime& rcFracTime2);
      void SetToMax(const CFracTime& rcFracTime, UInt32 tick);
      void SetToMax(const CFracTime& rcFracTime);
      void SetToMax(UInt32 tick);
      UInt32 GetClockTick();
      Real GetClockTickFraction();
      void AddClockTick(UInt32 tick);
      void AddClockTickFraction(Real fraction);

      bool operator==(const CFracTime& rcFracTime) const;
      bool operator!=(const CFracTime& rcFracTime) const;
      bool operator>(const CFracTime& rcFracTime) const;
      bool operator>(UInt32 tick) const;
      bool operator<(const CFracTime& rcFracTime) const;
      bool operator<(UInt32 tick) const;
      bool operator>=(const CFracTime& rcFracTime) const;
      bool operator>=(UInt32 tick) const;
      bool operator<=(const CFracTime& rcFracTime) const;
      bool operator<=(UInt32 tick) const;
      CFracTime& operator=(const CFracTime& rcFracTime);
      CFracTime& operator+=(const CFracTime& rcFracTime);
      CFracTime operator+(const CFracTime& rcFracTime) const;

   };

}

#endif

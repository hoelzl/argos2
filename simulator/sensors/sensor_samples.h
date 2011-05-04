/* -*- Mode: C++ -*- */

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
 * @file <simulator/sensors/sensor_samples.h>
 *
 * @brief This file provides the logic to manage the sensor samples
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef _CSENSORSAMPLES_H_
#define _CSENSORSAMPLES_H_


/* To avoid dependency problems when including */
namespace argos {
   class CSensorSamples;
}

#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/math/range.h>
#include <argos2/common/utility/math/angles.h>
#include <argos2/common/utility/math/general.h>

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>

namespace argos {

   class CSensorSamples {

   public:
      CSensorSamples();
      CSensorSamples(const std::string& str_filename);
      ~CSensorSamples();

      inline UInt32 GetNumSensors() {
         return m_unNumSensors;
      }

      inline Real GetMinValue() {
         return m_cValueRange.GetMin();
      }

      inline Real GetMaxValue() {
         return m_cValueRange.GetMax();
      }

      inline Real GetMinDistance() {
         return m_cDistanceRange.GetMin();
      }

      inline Real GetMaxDistance() {
         return m_cDistanceRange.GetMax();
      }

      /**
       * @brief This funcion returns the sample readings corresponding
       * to a given distance and angle under which an object is
       * perceived. For instance, given a wall at distance d and angle
       * alpha, calling this function for a proximity sample map will
       * return the readings of all the proximity sensors, as they are
       * determined by the presence of the wall
       *
       * @param f_distance the distance of the perceived object
       * @param f_angle the angle of the perceived object
       *
       * @return a pointer to the sensor readings for the given distance and angle
       */
      const Real* GetSensorReadings(Real f_distance,
                                    CRadians& c_angle);

   private:

      UInt32       m_unNumSensors;       ///< number of individual sensors contemporary sampled
      UInt32       m_unNumDistances;     ///< number of sampled distances
      UInt32       m_unNumAngles;        ///< number of sampled angles
      UInt32       m_unNumReadings;      ///< number of samples taken (= distances * angles)

      CRange<Real> m_cDistanceRange;     ///< range of sampling distances
      Real         m_fMinDistance;       ///< minimum sampling distance
      Real         m_fMaxDistance;       ///< maximum sampling distance

      CRange<Real> m_cValueRange;        ///< range of sample values
      Real         m_fMinValue;          ///< minimum sensor value
      Real         m_fMaxValue;          ///< maximum sensor value

      Real**       m_pfSamples;          ///< the actual samples

   };

}

#endif

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

#include "sensor_samples.h"
#include <argos2/simulator/simulator.h>

namespace argos {

/****************************************/
/****************************************/

   CSensorSamples::CSensorSamples() :
      m_unNumSensors(0),
      m_unNumDistances(0),
      m_unNumAngles(0),
      m_unNumReadings(0),
      m_cDistanceRange(0,1),
      m_cValueRange(0,1),
      m_pfSamples(NULL) {
   }

/****************************************/
/****************************************/

   CSensorSamples::CSensorSamples(const std::string& str_filename) :
      m_unNumSensors(0),
      m_unNumDistances(0),
      m_unNumAngles(0),
      m_unNumReadings(0),
      m_cDistanceRange(0,1),
      m_cValueRange(0,1),
      m_pfSamples(NULL) {

      std::string strBaseDir(CSimulator::GetInstance().GetInstallationDirectory());
      std::string strSamples = strBaseDir + str_filename;

      std::ifstream in(strSamples.c_str(), std::ios::in);
      if(!in) {
         THROW_ARGOSEXCEPTION("[FATAL] CSensorSamples: could not open file '" << strSamples << "'");
      }

      Real fMinDistance, fMaxDistance, fMinValue, fMaxValue;
      if(!(in >> m_unNumSensors ) ||
         !(in >> m_unNumDistances) ||
         !(in >> m_unNumAngles  ) ||
         !(in >> fMinDistance ) ||
         !(in >> fMaxDistance ) ||
         !(in >> fMinValue    ) ||
         !(in >> fMaxValue    )) {
         THROW_ARGOSEXCEPTION("[FATAL] CSensorSamples::CSensorSamples: error in reading parameters from file '" << str_filename << "'");
      }

      m_cDistanceRange.Set(fMinDistance, fMaxDistance);
      m_cValueRange.Set(fMinValue, fMaxValue);

      // allocate memory for the new sample table
      m_unNumReadings = m_unNumDistances * m_unNumAngles;
      m_pfSamples     = new Real*[m_unNumReadings];
      for(UInt32 i = 0; i < m_unNumReadings; ++i) {
         m_pfSamples[i] = new Real[m_unNumSensors];
      }

      // reads the sensor values
      for(UInt32 i = 0; i < m_unNumReadings; ++i) {
         for(UInt32 j = 0; j < m_unNumSensors; ++j) {
            if(!(in >> m_pfSamples[i][j])) {
               THROW_ARGOSEXCEPTION("[FATAL] CSensorSamples::CSensorSamples: error in reading samples from file '" << str_filename << "'");
            }
         }
      }
   }


/****************************************/
/****************************************/

   CSensorSamples::~CSensorSamples() {
      if(m_pfSamples) {
         for(UInt32 i = 0; i < m_unNumReadings; ++i) {
            delete [] m_pfSamples[i];
         }
         delete[] m_pfSamples;
      }
   }


/****************************************/
/****************************************/

   const Real* CSensorSamples::GetSensorReadings(Real f_distance,
                                                 CRadians& c_angle) {
      if(m_pfSamples == NULL) return NULL;

      // do not compute readings if distance is too large
      if(f_distance >= m_cDistanceRange.GetMax()) {
         return NULL;
      }

      // normalise distance within range
      if(f_distance < m_cDistanceRange.GetMin()) {
         f_distance = m_cDistanceRange.GetMin();
      }

      // normilise angle in [0,2*pi]
      c_angle.UnsignedNormalize();

      // quantisation of distnace and angles, in order to get the table index
      UInt32 unDistance = static_cast<UInt32>(Floor(m_cDistanceRange.NormalizeValue(f_distance) * m_unNumDistances));
      UInt32 unAngle    = static_cast<UInt32>(Floor(c_angle/CRadians::TWO_PI * m_unNumAngles));
      UInt32 unIndex    = unAngle + unDistance * m_unNumAngles;


      ARGOS_ASSERT(unIndex < m_unNumReadings,
                   "Error in accessing the sample table"
                   << " - distance: " << f_distance
                   << " - angle: "    << ToDegrees(c_angle)
                   << " - distance index: " << unDistance
                   << " - angle index: " << unAngle
                   << " -> index " << unIndex << " is not < than " << m_unNumReadings);


      return m_pfSamples[unIndex];
   }

/****************************************/
/****************************************/

}

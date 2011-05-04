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
 * @file <simulator/sensors/generic_sampled_sensor.cpp>
 *
 * @brief This file provides the general implementatio of a sensor
 * simulated through the sampling technique
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "generic_sampled_sensor.h"

namespace argos {

/****************************************/
   /****************************************/

   CGenericSampledSensor::CGenericSampledSensor() {

   }

   /****************************************/
   /****************************************/

   CGenericSampledSensor::~CGenericSampledSensor() {
      for(TMapSensorSamplesIterator it = m_tSensorSamples.begin();
           it != m_tSensorSamples.end();
           ++it) {
         delete it->second;
      }

      m_tSensorSamples.clear();
   }

   /****************************************/
   /****************************************/

   void CGenericSampledSensor::Init(TConfigurationNode& t_tree) {
      TConfigurationNodeIterator itSamples;
      for(itSamples  = itSamples.begin(&t_tree);
          itSamples != itSamples.end();
          ++itSamples) {
         std::string strEntityType;
         GetNodeAttribute(*itSamples, "entity", strEntityType);

         std::string strFilename;
         GetNodeAttribute(*itSamples, "filename", strFilename);

         // load the samples
         LoadSensorSamples(strEntityType, strFilename);
      }
   }


   /****************************************/
   /****************************************/

   void CGenericSampledSensor::Destroy() {
      for(TMapSensorSamplesIterator it = m_tSensorSamples.begin();
           it != m_tSensorSamples.end();
           ++it) {
         delete it->second;
      }

      m_tSensorSamples.clear();
   }


   /****************************************/
   /****************************************/

   void CGenericSampledSensor::LoadSensorSamples(const std::string& str_entity_type,
                                                 const std::string& str_filename) {
      m_tSensorSamples[str_entity_type] = new CSensorSamples(str_filename);
   }


   /****************************************/
   /****************************************/

   Real CGenericSampledSensor::GetMaxSensorRange() {
      Real fMaxRange = 0;
      for(TMapSensorSamplesIterator it = m_tSensorSamples.begin();
          it != m_tSensorSamples.end(); ++it) {
         fMaxRange = Max(fMaxRange, it->second->GetMaxDistance());
      }
      return fMaxRange;
   }

   /****************************************/
   /****************************************/

   UInt32 CGenericSampledSensor::GetNumberOfSampledSensorReadings() {
      UInt32 unNumSampledSensors = 0;
      for(TMapSensorSamplesIterator it = m_tSensorSamples.begin();
          it != m_tSensorSamples.end(); ++it) {
         UInt32 unNumSamples = it->second->GetNumSensors();
         if(unNumSampledSensors == 0) {
            unNumSampledSensors = unNumSamples;
         }
         else if(unNumSampledSensors != unNumSamples) {
            return 0;
         }
      }

      return unNumSampledSensors;
   }


   /****************************************/
   /****************************************/

   bool CGenericSampledSensor::CheckSamplesForEntityType(const std::string& str_entity_type) {
      return (m_tSensorSamples.find(str_entity_type) != m_tSensorSamples.end());
   }


   /****************************************/
   /****************************************/

   const Real* CGenericSampledSensor::GetSensorReadings(const std::string& str_entity_type,
                                                        Real f_distance,
                                                        CRadians& c_angle) {
      return m_tSensorSamples[str_entity_type]->GetSensorReadings(f_distance, c_angle);
   }

   /****************************************/
   /****************************************/

}

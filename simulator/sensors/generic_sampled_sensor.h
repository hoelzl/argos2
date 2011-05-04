/* -*- Mode: C++ -*-
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
 * @file <simulator/sensors/generic_sampled_sensor.h>
 *
 * @brief This file provides the general implementatio of a sensor
 * simulated through the sampling technique
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef GENERIC_SAMPLED_SENSOR_H
#define GENERIC_SAMPLED_SENSOR_H


/* To avoid dependency problems when including */
namespace argos {
   class CGenericSampledSensor;
}

#include <argos2/simulator/sensors/simulated_sensor.h>
#include <argos2/simulator/sensors/sensor_samples.h>

namespace argos {

   typedef std::map<std::string, CSensorSamples*>           TMapSensorSamples;
   typedef std::map<std::string, CSensorSamples*>::iterator TMapSensorSamplesIterator;


   class CGenericSampledSensor {

   protected:

      TMapSensorSamples	m_tSensorSamples;


   public:

      CGenericSampledSensor();
      virtual ~CGenericSampledSensor();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Destroy();

   protected:

      /**
       * @brief This function loads and creates the samples from a given
       * file, which correspond to a given entity type
       *
       * @param str_entity_type the type of entity to which the samples refer
       * @param str_filename the name of the file containing the samples
       */
      virtual void LoadSensorSamples(const std::string& str_entity_type,
                                     const std::string& s_filename);

      /**
       * @brief This function returns the maximum sensor range among the
       * loaded sensor samples
       *
       * @return the maximum sensor range
       */
      virtual Real GetMaxSensorRange();

      /**
       * @brief Check all the loaded sample tables and returns the
       * number of sensor readings, if all tables have the same value.
       *
       * @return the number of sensor readings, if all tables have the
       * same value - 0 otherwise.
       */
      virtual UInt32 GetNumberOfSampledSensorReadings();


      /**
       * @brief checks if samples have been loaded for the given entity
       * type
       *
       * @param str_entity_type the type of entity to check
       * @return true if the samples exist, false otherwise
       */
      virtual bool CheckSamplesForEntityType(const std::string& str_entity_type);


      /**
       * @brief This function returns the senso readings for a given entity
       * type, positioned at a given disntance and angle from the
       * sensing entity.
       *
       * @param str_entity_type the type of the perceived entity
       * @param f_distance the distance of the perceived entity
       * @param f_angle the angle of the perceived entity
       *
       * @return the readings produced by the perceived entity, or NULL
       * if an error occured
       */
      virtual const Real* GetSensorReadings(const std::string& str_entity_type,
                                            Real f_distance,
                                            CRadians& c_angle);


      /**
       * @brief This function adds the readings computed for a certain
       * entity to the current readings vector. The modality of the sum
       * depend on the particular sensor type. For instance, proximity
       * sensors readings sum by simply taking the maximum value;
       *
       * @param pf_readings the pointer to the readings from a given
       * entity
       */
      virtual void AddReadings(const Real* pf_readings) = 0;

   };
};

#endif


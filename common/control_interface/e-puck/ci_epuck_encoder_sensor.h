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
 * @file <common/control_interface/e-puck/ci_epuck_encoder_sensor.h>
 *
 * @brief This file provides the definition of the epuck encoder sensor. It

 * This file provides the definition of the epuck encoder sensor. It
 * returns the distance covered by the wheels in the last control step.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_EPUCK_ENCODER_SENSOR_H
#define CCI_EPUCK_ENCODER_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EPuckEncoderSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>

namespace argos {

   class CCI_EPuckEncoderSensor : public CCI_Sensor {

   public:

	   /**
	    * The DTO of the encoder
	    * It returns the distance covered by the wheels in the last timestep
	    */
      struct SReading {
         Real CoveredDistanceLeftWheel;
         Real CoveredDistanceRightWheel;
         
         SReading() :
            CoveredDistanceLeftWheel(0.0f),
            CoveredDistanceRightWheel(0.0f){}
         
         SReading(Real f_covered_distance_left_wheel,
                  Real f_covered_distance_right_wheel) :
                     CoveredDistanceLeftWheel(f_covered_distance_left_wheel),
                     CoveredDistanceRightWheel(f_covered_distance_right_wheel){
         }

      };

      /**
       * Constructor
       */
      CCI_EPuckEncoderSensor() :
         m_sReading() {
      }

      /**
       * Destructor
       */
      virtual ~CCI_EPuckEncoderSensor() {
      }

      /**
       * @brief Returns the reading of the encoder sensor
       * Returns the reading of the encoder sensor
       */
      virtual const SReading& GetReading() const {
         return m_sReading;
      }

   protected:

      SReading m_sReading;
   };

}

#endif

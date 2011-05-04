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
 * @file <common/control_interface/footbot/ci_footbot_encoder_sensor.h>
 *
 * @brief This file provides the definition of the footbot encoder sensor. It

 * This file provides the definition of the footbot encoder sensor. It
 * returns the distance covered by the wheels in the last control step.
 * Moreover, the interaxis distance of each robot is unique.
 * On the footbot there is a sensor that, at start-up, measure this distance,
 * i.e. the external distance between the two wheels.
 * This value is measured once at start-up and then is left constant.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_ENCODER_SENSOR_H
#define CCI_FOOTBOT_ENCODER_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_FootBotEncoderSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>

namespace argos {

   class CCI_FootBotEncoderSensor : public CCI_Sensor {

   public:

	   /**
	    * The DTO of the encoder
	    * It returns the distance covered by the wheels in the last timestep
	    * In addition it returns the value of the interaxis distance.
	    * i.e. the external distance between the two wheels.
	    * This value is measured once at start-up and then is left constant.
	    */
      struct SReading {
         Real CoveredDistanceLeftWheel;
         Real CoveredDistanceRightWheel;
         Real WheelAxisLength;
         
         SReading() :
            CoveredDistanceLeftWheel(0.0f),
            CoveredDistanceRightWheel(0.0f),
            WheelAxisLength(0.0f) {}
         
         SReading(Real f_covered_distance_left_wheel,
                  Real f_covered_distance_right_wheel,
                  Real f_wheel_axis_length) :
                     CoveredDistanceLeftWheel(f_covered_distance_left_wheel),
                     CoveredDistanceRightWheel(f_covered_distance_right_wheel),
                     WheelAxisLength(f_wheel_axis_length) {
         }

      };

      /**
       * Constructor
       */
      CCI_FootBotEncoderSensor() :
         m_sReading() {
      }

      /**
       * Destructor
       */
      virtual ~CCI_FootBotEncoderSensor() {
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

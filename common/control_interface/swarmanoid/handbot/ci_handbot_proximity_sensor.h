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
 * @file <common/control_interface/handbot/ci_handbot_proximity_sensor.h>
 *
 * @brief This file provides the definition of the handbot gripper proximity sensor.
 * There are in total 24 sensors, spread over the two grippers and their claws.
 *
 * The sketch below shows a direct view of the hand-bot gripper from the front.
 * The numbers show the indexes of the proximity sensors used in ARGOS.
 * Number in parenthesis are the indexes used in ASEBA
 *
 *                         ------------------
 *                         | 5(5) 4(4) 3(3) |
 *                         |                |
 *   ----------------------|                |---------------------
 *   | 11(9)  10(10) 9(11) |                | 2(2)   1(1)   0(0) |
 *   ----------------------|                |---------------------
 *                         |                |
 *                         | 8(6) 7(7) 6(8) |
 *                         ------------------
 *
 * @author Giovanni Pini  - <gpini@iridia.ulb.ac.be>
 * @author Nithin Mathews - <nmathews@ulb.ac.be>
 *
 */

#ifndef CCI_HANDBOT_PROXIMITY_SENSOR_H
#define CCI_HANDBOT_PROXIMITY_SENSOR_H

namespace argos {
   class CCI_HandBotProximitySensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/range.h>

namespace argos {

   class CCI_HandBotProximitySensor : public CCI_Sensor {

   public:

      static const UInt8 NUM_READINGS_PER_HAND;
      typedef std::vector<Real> THandReadings;

      struct TReadings {
         THandReadings Left;
         THandReadings Right;

         TReadings() :
            Left(NUM_READINGS_PER_HAND),
            Right(NUM_READINGS_PER_HAND) {
         }
      };

      virtual ~CCI_HandBotProximitySensor() {
      }

      virtual const TReadings& GetAllReadings() const {
         return m_tHandReadings;
      }

      inline virtual const THandReadings& GetReadingsLeft() const {
         return m_tHandReadings.Left;
      }

      inline virtual const THandReadings& GetReadingsRight() const {
         return m_tHandReadings.Right;
      }

   protected:

      TReadings m_tHandReadings;
      static const CRange<Real>     HANDBOT_PROXIMITY_RANGE;

   };

}

#endif

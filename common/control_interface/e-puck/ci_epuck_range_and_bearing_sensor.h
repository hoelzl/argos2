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
 * @file <common/control_interface/e-puck/ci_epuck_range_and_bearing_sensor.h>
 *
 * @brief This file provides the definition of the sensor part of the
 *        range and bearing system.
 *
 * The range and bearing sensor/actuator pair allows robots to
 * sense other robots in their locality and exchange data with them.
 * When the presence of a robot cannot be sensed anymore (i.e., the sensing
 * robot does not receive an IR beam from the robot), the data sent
 * over the local radio is ignored. Thus, this sensor/actuator pair
 * provides localization and local communication to the robot.
 * The range of the sensor depends on the robot type.
 *
 * For each sensed robot, the following data is provided:
 *
 *  1) range (=distance) in meters relative to the sensing robot
 *  2) bearing horizontal (=angle) in signed radians relative to the sensing robot
 *  3) data (16 bits) transmitted by the other robot
 *
 * All this data is encapsulated in a TRangeAndBearingReceivedPacket struct.
 *
 * The sensor provides a vector that holds the last received packets.
 * The vector can be accessed by calling the
 * CCI_RangeAndBearingSensor::GetLastReceivedPackets() method.
 *
 * Additionally to the data described above, each packet is assigned a unique,
 * sequentially increased number upon reception. Together with the method
 * CCI_RangeAndBearingSensor::GetLatestPacketId(), controllers can check if
 * there are new packets arrived since the last call and can iterate over
 * the list of packages.
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef CCI_EPUCK_RANGE_AND_BEARING_SENSOR_H
#define CCI_EPUCK_RANGE_AND_BEARING_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EPuckRangeAndBearingSensor;
}

#include <string>
#include <vector>
#include <iostream>

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/angles.h>

namespace argos {

   /**
    * This struct defines a received range and bearing packet.
    * It holds the id of the sending robot, the distance (in cms), the horizontal,
    * the packet payload data (8 bits) and a packet id, that is sequentially 
    * increased each time a packet is received.
    *
    * Please note that this packet is only used to hold data on the receiving
    * end of the communication.
    */
   struct TEPuckRangeAndBearingReceivedPacket {

      typedef UInt8 TRangeAndBearingData[2];
      typedef UInt16 TRawValues[12];

      /* Distance in cms. */
      Real Range;

      /* Horizontal angle, in radians, counter-clock-wise. */
      CRadians BearingHorizontal;

      /* Datatype for the range and bearing payload. */
      TRangeAndBearingData Data;

      /* Raw values used for the calibration of the 3D bearing. Don't remove */
      TRawValues RawValues;

      /* The id of the packet. */
      UInt16 Id;

      /* Constructor. */
      TEPuckRangeAndBearingReceivedPacket() :
         Range(0.0), BearingHorizontal(0.0), Id(0) {
      }

      TEPuckRangeAndBearingReceivedPacket(const TEPuckRangeAndBearingReceivedPacket& t_packet) :
         Range(t_packet.Range), BearingHorizontal(t_packet.BearingHorizontal), Id(t_packet.Id) {
         ::memcpy(Data, &t_packet.Data, sizeof(TRangeAndBearingData));
         ::memcpy(RawValues, &t_packet.RawValues, sizeof(TRawValues));
      }

      TEPuckRangeAndBearingReceivedPacket& operator=(const TEPuckRangeAndBearingReceivedPacket& t_packet) {
         if (&t_packet != this) {
        	Range = t_packet.Range;
            BearingHorizontal = t_packet.BearingHorizontal;
            Id = t_packet.Id;
            ::memcpy(Data, &t_packet.Data, sizeof(TRangeAndBearingData));
            ::memcpy(RawValues, &t_packet.RawValues, sizeof(TRawValues));
         }
         return *this;
      }

      friend std::ostream& operator<<(std::ostream& os,
                                      const TEPuckRangeAndBearingReceivedPacket& t_packet) {
         os << "RANGE_AND_BEARING_RECEIVED_DATA < range = " << t_packet.Range
            << ", bearing horizontal = " << t_packet.BearingHorizontal
            << ", data = " << t_packet.Data
	    << ", id = " << t_packet.Id << " >";

         return os;
      }
   };

   class CCI_EPuckRangeAndBearingSensor : public CCI_Sensor {

   public:

      /* Type for the map that holds the latest received packet for each robot. */
      typedef std::vector<TEPuckRangeAndBearingReceivedPacket> TLastReceivedPackets;

      CCI_EPuckRangeAndBearingSensor() :
         m_unLatestPacketId(0) {
      }

      virtual ~CCI_EPuckRangeAndBearingSensor() {
      }

      /* Clears the messages received from the range and bearing. Call this at the end of your
       * time-step to be sure that at each time-step you only have the most recently received packets*/
      inline virtual void ClearRABReceivedPackets() {
         m_tLastReceivedPackets.clear();
      }

      /* Get the latest packet for all robots. Might contain empty packets. */
      inline virtual const TLastReceivedPackets& GetLastReceivedPackets() const {
         return m_tLastReceivedPackets;
      }

      /* Get the id of the packet received most recently. */
      inline virtual UInt16 GetLatestPacketId() const {
         return m_unLatestPacketId;
      }

      inline virtual UInt16 GetNumberMessagesReceived() {
         return m_tLastReceivedPackets.size();
      }

      inline virtual TEPuckRangeAndBearingReceivedPacket GetPacket(UInt16 un_i){
         return m_tLastReceivedPackets.at(un_i);
      }

      virtual UInt16 PacketToInt(const TEPuckRangeAndBearingReceivedPacket& t_packet) = 0;

   protected:

      /* Stores the last received packet from each robot. */
      TLastReceivedPackets m_tLastReceivedPackets;

      /* Id of the latest received packet. Can be used to get the freshly arrived packages only. */
      UInt16 m_unLatestPacketId;

   };

}

#endif

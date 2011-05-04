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
 * @file <common/control_interface/ci_wifi_actuator.h>
 *
 * @brief This file provides the definition of the wifi actuator.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_WIFI_ACTUATOR_H
#define CCI_WIFI_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_WiFiActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

   class CCI_WiFiActuator : virtual public CCI_Actuator {

   public:

      class SMessage {
         std::string Sender;
         std::string Recipient;
         std::string Payload;

         SMessage() {}
         SMessage(const std::string& str_sender,
                  const std::string& str_recipient,
                  const std::string& str_payload) :
            Sender(str_sender),
            Recipient(str_recipient),
            Payload(str_payload) {}
      };

      typedef std::vector<SMessage> TMessageList;

   public:

      CCI_WiFiActuator() {}
      virtual ~CCI_WiFiActuator() {}

      /**
       * Sends a message to a specific robot.
       * @param str_recipient The id of the recipient robot
       * @param str_payload The message payload
       * @param f_delay The sending delay (in seconds? milliseconds?)
       */
      virtual void SendMessageTo(const std::string& str_recipient,
                                 const std::string& str_payload,
                                 Real f_delay = 0) = 0;

      /**
       * Broadcasts a message.
       * @param str_payload The message payload
       * @param f_delay The sending delay (in seconds? milliseconds?)
       */
      virtual void BroadcastMessage(const std::string& str_payload,
                                    Real f_delay = 0) = 0;

   };

}

#endif

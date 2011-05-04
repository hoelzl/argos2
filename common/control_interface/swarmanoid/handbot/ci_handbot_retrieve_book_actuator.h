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
 * @file <common/control_interface/handbot/ci_handbot_retrieve_book_actuator.h>
 *
 * @brief This file provides the common interface definition of handbot retrieve book actuator.
 *
 * The actuator is meant to wrap the script that climbs the shelf and retrieves the book.
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#ifndef CCI_HANDBOT_RETRIEVE_BOOK_ACTUATOR_H
#define CCI_HANDBOT_RETRIEVE_BOOK_ACTUATOR_H

namespace argos {
   class CCI_HandBotRetrieveBookActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

   class CCI_HandBotRetrieveBookActuator : public CCI_Actuator {

   public:

       /** Climb status */
       /* Robot ready to start the routine */
       static const UInt32 RETRIEVE_BOOK_READY;
       /* Magnet is being loaded + shot */
       static const UInt32 RETRIEVE_BOOK_SHOOTING_MAGNET;
       /* Magnet did not attach */
       static const UInt32 RETRIEVE_BOOK_SHOOTING_FAILED;
       /* Magnet attached, the robot is climbing */
       static const UInt32 RETRIEVE_BOOK_CLIMBING;
       /* Climbing finished, but the book was not retrieved for some reason */
       static const UInt32 RETRIEVE_BOOK_FINISHED_FAILURE;
       /* Climbing finished, book retrieved */
       static const UInt32 RETRIEVE_BOOK_FINISHED_SUCCESS;
       /* Detach magnet failed, cannot do anything */
       static const UInt32 RETRIEVE_BOOK_DETACH_MAGNET_FAILED;

       /**
        *
        * Constructor.
        *
        */
       CCI_HandBotRetrieveBookActuator() {
           m_unRetrieveBookStatus = RETRIEVE_BOOK_READY;
       }

      /**
       *
       * Destructor.
       *
       */
      virtual ~CCI_HandBotRetrieveBookActuator() {
      }

      /**
       *
       * @brief Destroys the actuator.
       *
       */
      inline virtual void  Destroy() {}

      /**
       *
       * @brief Triggers the retrieve book routine
       * Thee routine needs to know the target shelf + the gripper
       * initially attached to the shelf.
       *
       * @param un_target_shelf shelf to climb to
       * @param un_starting_gripper gripper initially attached to the shelf
       *
       */
      virtual void RetrieveBook(UInt8 un_target_shelf, UInt32 un_starting_gripper) = 0;

      /**
       *
       * @brief Returns the status of the retrieve book procedure
       *
       * @return integer representing the status of the retrieve book routine
       *
       */
      inline UInt32 GetRetrieveBookStatus() {
          return m_unRetrieveBookStatus;
      }

   protected:

      /** Current status of the retrieve book procedure */
      UInt32 m_unRetrieveBookStatus;

   };

}

#endif

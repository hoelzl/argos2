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
 * @file <common/control_interface/handbot/ci_handbot_retrieve_book_actuator.cpp>
 *
 * @brief This file provides the common interface implementation of handbot retrieve book actuator.
 *
 * The actuator is meant to wrap the script that climbs the shelf and retrieves the book.
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#include "ci_handbot_retrieve_book_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/

    const UInt32 CCI_HandBotRetrieveBookActuator::RETRIEVE_BOOK_READY                = 0;
    const UInt32 CCI_HandBotRetrieveBookActuator::RETRIEVE_BOOK_SHOOTING_MAGNET      = 1;
    const UInt32 CCI_HandBotRetrieveBookActuator::RETRIEVE_BOOK_SHOOTING_FAILED      = 2;
    const UInt32 CCI_HandBotRetrieveBookActuator::RETRIEVE_BOOK_CLIMBING             = 3;
    const UInt32 CCI_HandBotRetrieveBookActuator::RETRIEVE_BOOK_FINISHED_FAILURE     = 4;
    const UInt32 CCI_HandBotRetrieveBookActuator::RETRIEVE_BOOK_FINISHED_SUCCESS     = 5;
    const UInt32 CCI_HandBotRetrieveBookActuator::RETRIEVE_BOOK_DETACH_MAGNET_FAILED = 6;

   /****************************************/
   /****************************************/

}

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
 * @file <common/logging/argos_log.cpp>
 *
 * @brief This file provides the implementation of class CARGoSLog.
 *
 * This file provides the implementation of class CARGoSLog.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "argos_log.h"

namespace argos {

   CARGoSLog LOG(std::cout, SLogColor(ARGOS_LOG_ATTRIBUTE_DIM, ARGOS_LOG_COLOR_GREEN, ARGOS_LOG_COLOR_BLACK));
   CARGoSLog LOGERR(std::cerr, SLogColor(ARGOS_LOG_ATTRIBUTE_DIM, ARGOS_LOG_COLOR_RED, ARGOS_LOG_COLOR_BLACK));

}

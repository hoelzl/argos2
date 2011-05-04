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
 * @file <common/control_interface/ci_wifi_sensor.h>
 *
 * @brief This file provides the definition of the  wifi sensor.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_WIFI_SENSOR_H
#define CCI_WIFI_SENSOR_H

/* To avoid dependency problems when including */
namespace argos {
    class CCI_WiFiSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/control_interface/ci_wifi_actuator.h>

namespace argos {

    class CCI_WiFiSensor : virtual public CCI_Sensor {

    public:

       CCI_WiFiSensor() {}
       virtual ~CCI_WiFiSensor() {}

       virtual void GetReceivedMessages(CCI_WiFiActuator::TMessageList& t_messages) = 0;

    };

}

#endif

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
 * @file <common/control_interface/ci_sensor.h>
 *
 * @brief This file provides the control interface for all sensors
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_SENSOR_H
#define CCI_SENSOR_H

#include <map>

#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/common/utility/configuration/memento.h>

namespace argos {
   class CCI_Sensor;
}

namespace argos {

   typedef std::map<std::string, CCI_Sensor*, std::less<std::string> > TSensorMap;

   class CCI_Sensor : public CBaseConfigurableResource,
                      public CMemento {

   public:

      inline virtual void Init(TConfigurationNode& t_node) {}
      inline virtual void Destroy() {}

      inline virtual void SaveState(CByteArray& c_buffer) {}
      inline virtual void LoadState(CByteArray& c_buffer) {}

   };

}

#endif

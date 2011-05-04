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
 * @file <common/configuration/base_configurable_resource.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CBASE_CONFIGURABLE_RESOURCE_H
#define CBASE_CONFIGURABLE_RESOURCE_H

namespace argos {
   class CBaseConfigurableResource;
}

#include <argos2/common/utility/configuration/argos_configuration.h>

namespace argos {

   class CBaseConfigurableResource {

   public:

      virtual ~CBaseConfigurableResource() {}

      virtual void Init(TConfigurationNode& t_tree) = 0;

      virtual void Destroy() = 0;

   };

}

#endif

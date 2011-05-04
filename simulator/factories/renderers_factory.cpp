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
 * @file <simulator/factories/renderers_factory.cpp>
 *
 * @brief This file contains the implementation of
 *
 * This file contains the implementation of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "renderers_factory.h"
#include <memory>

namespace argos {

   /****************************************/
   /****************************************/

   SRendererPlugin* GetRendererPlugin() {
      static std::auto_ptr<SRendererPlugin> psRendererPlugin(new SRendererPlugin());
      return psRendererPlugin.get();
   }

   /****************************************/
   /****************************************/

   CRender* CRenderersFactory::NewRenderer(const std::string& str_renderer_type) {
      if(GetRendererPlugin()->FactoryMap.find(str_renderer_type) == GetRendererPlugin()->FactoryMap.end()) {
         THROW_ARGOSEXCEPTION("Renderer \"" << str_renderer_type << "\" not found.");
      }
      return GetRendererPlugin()->FactoryMap[str_renderer_type]();
   }

   /****************************************/
   /****************************************/

}

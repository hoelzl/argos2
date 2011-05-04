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
 * @file <simulator/factories/renderers_factory.h>
 *
 * @brief This file contains the definition of
 *
 * This file contains the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef RENDERERS_FACTORY_H
#define RENDERERS_FACTORY_H

namespace argos {
   class CRenderersFactory;
}

#include <visualizations/render.h>
#include <string>
#include <map>

namespace argos {

   class CRenderersFactory {

   public:

      static CRender* NewRenderer(const std::string& str_renderer_type);

   };

}

#endif

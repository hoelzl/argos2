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
 * @file <simulator/visualisations/render.h>
 *
 * @brief This file contains the definition of the CRender interface.
 *
 * This file contains the definition of the CRender interface. Such interface
 * is the base for all the visualisations (OpenGL, OGRE, gnuplot, blender,
 * etc.) in ARGOS.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef RENDER_H
#define RENDER_H

namespace argos {
   class CRender;
}

#include <string>
#include <map>
#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/simulator/simulator.h>

namespace argos {

   class CRender : public CBaseConfigurableResource {

   protected:

      /** A reference to the simulator */
      CSimulator& m_cSimulator;

      /** A reference to the space */
      CSpace& m_cSpace;

      /** The id of the renderer */
      std::string m_strId;

   public:

      CRender() :
         m_cSimulator(CSimulator::GetInstance()),
         m_cSpace(m_cSimulator.GetSpace()) {}

      virtual ~CRender() {}

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Execute();
      
      virtual void Destroy() {}

      inline const std::string& GetId() const {
         return m_strId;
      }

      inline void SetId(const std::string str_id) {
         m_strId = str_id;
      }
   };

}

/* Render factory */

namespace argos {

   /* Typedef to make it easier to set up the render factory */
   typedef CRender *CRender_Maker();

   /* The renderer object map */
   struct SRendererPlugin {
      std::map < std::string, CRender_Maker *, std::less<std::string> > FactoryMap;
      std::map < std::string,     std::string, std::less<std::string> > ShortDescriptionMap;
      std::map < std::string,     std::string, std::less<std::string> > AuthorMap;
      std::map < std::string,     std::string, std::less<std::string> > LongDescriptionMap;
      std::map < std::string,     std::string, std::less<std::string> > StatusMap;
   };

   SRendererPlugin* GetRendererPlugin();

/* To add the controller to the factory */
#define REGISTER_RENDER(class_name, label, short_description, author, long_description, status) \
   extern "C" {                                                         \
      argos::CRender* class_name ## _maker(){                           \
         return new class_name;                                         \
      }                                                                 \
                                                                        \
      class class_name ## _proxy {                                      \
      public:                                                           \
      class_name ## _proxy(){                                           \
         argos::GetRendererPlugin()->FactoryMap[label] = class_name ## _maker; \
         argos::GetRendererPlugin()->ShortDescriptionMap[label] = short_description; \
         argos::GetRendererPlugin()->AuthorMap[label] = author; \
         argos::GetRendererPlugin()->LongDescriptionMap[label] = long_description; \
         argos::GetRendererPlugin()->StatusMap[label] = status; \
      }                                                                 \
      };                                                                \
      class_name ## _proxy class_name ## _p;                            \
   }

}

#endif

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
 * @file <simulator/visualisations/text/text_render.h>
 *
 * @brief This file contains the definition of a simple text renderer.
 *
 * This file contains the definition of a simple text renderer that
 * displays the status of the entities in the swarmanoid space.
 * The output is a table with the following format:
 *
 * current clock | robot type | robot id | x | y | z | alpha | beta | gamma
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef TEXT_RENDER_H
#define TEXT_RENDER_H

/* To avoid dependency problems when including */
namespace argos {
   class CTextRender;
   class CSpace;
   class CSceneGraph;
   class CTextRenderVisitorDraw;
};

#include <argos2/simulator/visualizations/render.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>

#include <iostream>
#include <fstream>

namespace argos {

   class CTextRender : public CRender {

   protected:

      /** Actual stream the renderer should write to: file or screen. */
      static std::ostream m_cOutputStream;

      /** File stream the renderer should write to if the selected output is file. */
      std::ofstream m_cOutputFileStream;

      /** How many decimal figures should be displayed. */
      UInt8 m_unPrecision;

      /** Reference to the text render visitor that draws an entity */
      CTextRenderVisitorDraw* m_pcVisitor;

   public:

      CTextRender() :
         m_unPrecision(2),
         m_pcVisitor(NULL) {}


      virtual ~CTextRender() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Execute();
      virtual void Destroy();

   private:

      void Draw();
  
   };

}

#endif

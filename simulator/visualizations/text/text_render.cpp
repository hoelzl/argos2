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
 * @file <simulator/visualisations/text/text_render.cpp>
 *
 * @brief This file contains the implementation of a simple text renderer.
 *
 * This file contains the implementation of a simple text renderer that
 * displays the status of the entities in the swarmanoid space.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include <iomanip>

#include "text_render.h"
#include <argos2/common/utility/math/ray.h>
#include <argos2/common/utility/logging/argos_log.h>
#include <argos2/common/utility/string_utilities.h>
#include "simulator.h"
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/space/entities/entity.h>
#include <argos2/simulator/visitors/text_render_visitor_draw.h>

/****************************************/
/****************************************/

namespace argos {

   /* Initialize the output stream to write to cout. */
   std::ostream CTextRender::m_cOutputStream(std::cout.rdbuf());

   /****************************************/
   /****************************************/

   void CTextRender::Init(TConfigurationNode& t_tree)
   {
      try {
         /* Call parent init */
         CRender::Init(t_tree);

         /* Get precision */
         GetNodeAttribute(t_tree, "precision", m_unPrecision);
         ++m_unPrecision;

         /* Get the file name, if any */
         std::string strFileName, strDefault;
         GetNodeAttributeOrDefault(t_tree, "file", strFileName, strDefault);

         /* Decide what to do with output: stdout or file? */
         if(strFileName != "") {
            /* Output to file */
            m_cOutputFileStream.open(strFileName.c_str(), std::ios::out);
            if ( m_cOutputFileStream.bad( ) ) {
               THROW_ARGOSEXCEPTION("Error opening file \"" <<
                                    strFileName << "\" for text rendering.");
            }
            m_cOutputStream.rdbuf(m_cOutputFileStream.rdbuf());
         }
         else {
            /* Output to stdout */
            m_cOutputStream.rdbuf(std::cout.rdbuf( ));
         }

         /* Display a column header */
         m_cOutputStream << std::setw(8)  << setiosflags(std::ios::left) << "# clock"    << " "
                         << std::setw(16) << setiosflags(std::ios::left) << "Robot type" << " "
                         << std::setw(16) << setiosflags(std::ios::left) << "Robot id"   << " "
                         << std::setw(8)  << setiosflags(std::ios::left) << "X"          << " "
                         << std::setw(8)  << setiosflags(std::ios::left) << "Y"          << " "
                         << std::setw(8)  << setiosflags(std::ios::left) << "Z"          << " "
                         << std::setw(8)  << setiosflags(std::ios::left) << "rotZ"       << " "
                         << std::setw(8)  << setiosflags(std::ios::left) << "rotY"       << " "
                         << std::setw(8)  << setiosflags(std::ios::left) << "rotX"
                         << std::endl     << std::flush;

         /* Create the visitor */
         m_pcVisitor = new CTextRenderVisitorDraw(m_cOutputStream, m_unPrecision);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize the text renderer", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CTextRender::Execute() {
      /* Main cycle */
      Draw();
      while(!m_cSimulator.IsExperimentFinished()) {
         m_cSimulator.UpdateSpace();
         Draw();
      }
   }

   /****************************************/
   /****************************************/

   void CTextRender::Draw( )
   {
      /* call visitor to draw the entities */
      TEntityMap& entitiesMap = m_cSpace.GetAllEntities();
      for(TEntityMap::iterator it_entities = entitiesMap.begin();
          it_entities != entitiesMap.end();
          ++it_entities) {
         m_cOutputStream << std::setw (8) << setiosflags(std::ios::left) << m_cSpace.GetSimulationClock() << " ";
         (it_entities->second)->Accept(*m_pcVisitor);
      }

   }

   /****************************************/
   /****************************************/

   void CTextRender::Destroy( )
   {
      if(m_cOutputFileStream.is_open())
         m_cOutputFileStream.close( );
      delete m_pcVisitor;
   }

   /****************************************/
   /****************************************/

   REGISTER_RENDER(CTextRender,
                   "text_render",
                   "A simple, tabular plain-text renderer",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "The text renderer is a simple textual renderer that outputs the position and\n"
                   "orientation of each positional entity at each time step into a textual table.\n"
                   "This visualization can be useful for debugging, to allow for simple data\n"
                   "analysis on the entity position and a basic example of a visualization plugin.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <visualizations>\n"
                   "    <text_render precision=\"2\" />\n"
                   "  </visualizations>\n\n"
                   "The 'precision' attribute specifies the number of decimal digits to display.\n"
                   "This attribute does not affect the precision of the internal calculations of\n"
                   "the simulator.\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "  <visualizations>\n"
                   "    <text_render id=\"txt\"\n"
                   "                 precision=\"2\"\n"
                   "                 file=\"output.txt\" />\n"
                   "  </visualizations>\n\n"
                   "The <text_render> tag has two optional attributes: 'id' and 'file'.\n"
                   "The attribute 'id' is ignored. It is there for compatibility with the plugin\n"
                   "system, but it's never used.\n"
                   "The attribute 'file', when specified, causes the text renderer to write to the\n"
                   "passed name. The file, if non-existent, is created. If already existent,\n"
                   "it is truncated and overwritten. No warning message is displayed in either\n"
                   "case.\n"
                   "If the 'file' attribute is omitted, the text renderer writes to standard\n"
                   "output.\n",
                   "Under development"
      );
}

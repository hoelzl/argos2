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
 * @file <simulator/swarmanoid_space/visitors/text_render_visitor_draw.h>
 *
 * @brief This file contains the definition of the
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 *
 */

#ifndef TEXT_RENDER_VISITOR_DRAW_H
#define TEXT_RENDER_VISITOR_DRAW_H

#include <argos2/simulator/visitors/entity_visitor.h>
#include <argos2/simulator/space/entities/box_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>
#include <argos2/simulator/space/entities/light_entity.h>
#include <argos2/simulator/space/entities/epuck_entity.h>

#include <iostream>
#include <iomanip>

namespace argos
{
   class CTextRenderVisitorDraw : public CEntityVisitor {

   private:
      /** a reference to the output stream */
      std::ostream& m_cOutputStream;

      /** the number of decimal digits to print */
      UInt16 m_unPrecision;

      template<class E> void DrawElement(E& c_entity) {
         const CVector3& cPosition = c_entity.GetPosition();
         const CQuaternion& cOrientation = c_entity.GetOrientation();
         CRadians cZAngle, cYAngle, cXAngle;
         cOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
         m_cOutputStream << std::setw(16)<< setiosflags(std::ios::left) << c_entity.GetTypeDescription() << " "
                         << std::setw(16)<< setiosflags(std::ios::left) << c_entity.GetId()              << " "
                         << std::setw(8) << std::setprecision(m_unPrecision) << setiosflags(std::ios::left)<< cPosition.GetX() << " "
                         << std::setw(8) << std::setprecision(m_unPrecision) << setiosflags(std::ios::left)<< cPosition.GetY() << " "
                         << std::setw(8) << std::setprecision(m_unPrecision) << setiosflags(std::ios::left)<< cPosition.GetZ() << " "
                         << std::setw(8) << std::setprecision(m_unPrecision) << setiosflags(std::ios::left)<< ToDegrees(cZAngle).GetValue() << " "
                         << std::setw(8) << std::setprecision(m_unPrecision) << setiosflags(std::ios::left)<< ToDegrees(cYAngle).GetValue() << " "
                         << std::setw(8) << std::setprecision(m_unPrecision) << setiosflags(std::ios::left)<< ToDegrees(cXAngle).GetValue()
                         << std::endl    << std::flush;

      }

   public:

      /**
       * @brief Create a visitor with the necessary references
       *
       * @param c_output_stream a reference to the output stream
       * @param un_precision the number of decimal digits to print
       */
      CTextRenderVisitorDraw(std::ostream& c_output_stream,
                             UInt8 un_precision) :
         m_cOutputStream(c_output_stream),
         m_unPrecision(un_precision) {}

      virtual void Visit(CBoxEntity& c_entity) {
         DrawElement(c_entity.GetEmbodiedEntity());
      }

      virtual void Visit(CCylinderEntity& c_entity) {
         DrawElement(c_entity.GetEmbodiedEntity());
      }

      virtual void Visit(CFloorEntity& c_entity) {
         // not displayed
      }

      virtual void Visit(CFootBotEntity& c_entity) {
         DrawElement(c_entity.GetEmbodiedEntity());
      }

      virtual void Visit(CEyeBotEntity& c_entity) {
         DrawElement(c_entity.GetEmbodiedEntity());
      }

      virtual void Visit(CLightEntity& c_entity) {
         DrawElement(c_entity);
      }

      virtual void Visit(CEPuckEntity& c_entity) {
         DrawElement(c_entity.GetEmbodiedEntity());
      }

      virtual void Visit(CWiFiMediumEntity& c_entity) {
         // not displayed
      }

   };

}

#endif

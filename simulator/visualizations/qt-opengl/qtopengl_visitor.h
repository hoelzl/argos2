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
 * @file <simulator/visualizations/qt-opengl/qtopengl_visitor.h>
 *
 * @brief This file contains the definition of the
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 *
 */

#ifndef QTOPENGL_VISITOR_H
#define QTOPENGL_VISITOR_H

namespace argos {
   class CQTOpenGLVisitor;
   class CQTOpenGLWidget;
   class CPositionalEntity;
   class CBoxEntity;
   class CCylinderEntity;
   class CFootBotEntity;
   class CEPuckEntity;
   class CQTOpenGLUserFunctions;
}

#include <argos2/simulator/visitors/entity_visitor.h>
#include <argos2/simulator/visualizations/qt-opengl/models/qtopengl_box.h>
#include <argos2/simulator/visualizations/qt-opengl/models/qtopengl_cylinder.h>
#include <argos2/simulator/visualizations/qt-opengl/models/qtopengl_footbot.h>
#include <argos2/simulator/visualizations/qt-opengl/models/qtopengl_eyebot.h>
#include <argos2/simulator/visualizations/qt-opengl/models/qtopengl_light.h>
#include <argos2/simulator/visualizations/qt-opengl/models/qtopengl_epuck.h>

namespace argos {

   class CQTOpenGLVisitor : public CEntityVisitor {

   public:

      CQTOpenGLVisitor(CQTOpenGLWidget& c_widget,
                       CQTOpenGLUserFunctions& c_user_functions);
      virtual ~CQTOpenGLVisitor() {}

      virtual void Visit(CBoxEntity& c_entity);
      virtual void Visit(CCylinderEntity& c_entity);
      virtual void Visit(CFloorEntity& c_entity);
      virtual void Visit(CFootBotEntity& c_entity);
      virtual void Visit(CEyeBotEntity& c_entity);
      virtual void Visit(CLightEntity& c_entity);
      virtual void Visit(CEPuckEntity& c_entity);
      virtual void Visit(CWiFiMediumEntity& c_entity) {}

   protected:

      virtual void DrawElement(CBoxEntity& c_entity);
      virtual void DrawElement(CCylinderEntity& c_entity);
      virtual void DrawElement(CFloorEntity& c_entity);
      virtual void DrawElement(CFootBotEntity& c_entity);
      virtual void DrawElement(CEyeBotEntity& c_entity);
      virtual void DrawElement(CLightEntity& c_entity);
      virtual void DrawElement(CEPuckEntity& c_entity);

   protected:

      CQTOpenGLWidget& m_cWidget;
      CQTOpenGLUserFunctions& m_cUserFunctions;
      CQTOpenGLBox m_cBoxModel;
      CQTOpenGLCylinder m_cCylinderModel;
      CQTOpenGLEPuck m_cEPuckModel;
      CQTOpenGLFootBot m_cFootBotModel;
      CQTOpenGLEyeBot m_cEyeBotModel;
      CQTOpenGLLight m_cLightModel;

   };

}

#endif

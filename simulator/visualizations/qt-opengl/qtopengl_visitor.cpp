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

#include "qtopengl_visitor.h"
#include "qtopengl_widget.h"

#include <argos2/simulator/space/entities/box_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>
#include <argos2/simulator/space/entities/light_entity.h>
#include <argos2/simulator/space/entities/controllable_entity.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <GL/gl.h>

namespace argos {

   /****************************************/
   /****************************************/
   
   CQTOpenGLVisitor::CQTOpenGLVisitor(CQTOpenGLWidget& c_widget,
                                      CQTOpenGLUserFunctions& c_user_functions) :
      m_cWidget(c_widget),
      m_cUserFunctions(c_user_functions) {}

   /****************************************/
   /****************************************/

   static void DrawPositionalEntity(CPositionalEntity& c_entity) {
      /* Get the position of the entity */
      const CVector3& cPosition = c_entity.GetPosition();
      /* Get the orientation of the entity */
      const CQuaternion& cOrientation = c_entity.GetOrientation();
      CRadians cZAngle, cYAngle, cXAngle;
      cOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      /* First, translate the entity */
      glTranslatef(cPosition.GetX(), cPosition.GetY(), cPosition.GetZ());
      /* Second, rotate the entity */
      glRotatef(ToDegrees(cXAngle).GetValue(), 1.0f, 0.0f, 0.0f);
      glRotatef(ToDegrees(cYAngle).GetValue(), 0.0f, 1.0f, 0.0f);
      glRotatef(ToDegrees(cZAngle).GetValue(), 0.0f, 0.0f, 1.0f);
   }

   /****************************************/
   /****************************************/

   static void DrawRays(CControllableEntity& c_entity) {
      if(! c_entity.GetCheckedRays().empty()) {
         glDisable(GL_LIGHTING);
         glBegin(GL_LINES);
         for(UInt32 i = 0; i < c_entity.GetCheckedRays().size(); ++i) {
            if(c_entity.GetCheckedRays()[i].first) {
               glColor3f(1.0, 0.0, 1.0);
            }
            else {
               glColor3f(0.0, 1.0, 1.0);
            }
            const CVector3& cStart = c_entity.GetCheckedRays()[i].second.GetStart();
            const CVector3& cEnd = c_entity.GetCheckedRays()[i].second.GetEnd();
            glVertex3f(cStart.GetX(), cStart.GetY(), cStart.GetZ());
            glVertex3f(cEnd.GetX(), cEnd.GetY(), cEnd.GetZ());
         }
         glEnd();
         glPointSize(5.0);
         glColor3f(0.0, 0.0, 0.0);
         glBegin(GL_POINTS);
         for(UInt32 i = 0; i < c_entity.GetIntersectionPoints().size(); ++i) {
            const CVector3& cPoint = c_entity.GetIntersectionPoints()[i];
            glVertex3f(cPoint.GetX(), cPoint.GetY(), cPoint.GetZ());
         }
         glEnd();
         glPointSize(1.0);
         glEnable(GL_LIGHTING);
      }
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::Visit(CBoxEntity& c_entity) {
      if(c_entity.IsVisible()) {
         DrawElement(c_entity);
      }
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::Visit(CCylinderEntity& c_entity) {
      if(c_entity.IsVisible()) {
         DrawElement(c_entity);
         m_cUserFunctions.Draw(c_entity);
      }
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::Visit(CFloorEntity& c_entity) {
      DrawElement(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::Visit(CFootBotEntity& c_entity) {
      DrawElement(c_entity);
      m_cUserFunctions.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::Visit(CEyeBotEntity& c_entity) {
      DrawElement(c_entity);
      m_cUserFunctions.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::Visit(CLightEntity& c_entity) {
      DrawElement(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::Visit(CEPuckEntity& c_entity) {
      DrawElement(c_entity);
      m_cUserFunctions.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::DrawElement(CBoxEntity& c_entity) {
	  /* Render the LEDs */
	  m_cBoxModel.DrawLEDs(c_entity);
	  /* Perform standard rotation and translation */
	  DrawPositionalEntity(c_entity.GetEmbodiedEntity());
	  /* Render the body */
	  m_cBoxModel.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::DrawElement(CCylinderEntity& c_entity) {
      /* Render the LEDs */
      m_cCylinderModel.DrawLEDs(c_entity);
      /* Perform standard rotation and translation */
      DrawPositionalEntity(c_entity.GetEmbodiedEntity());
      /* Render the body */
      m_cCylinderModel.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::DrawElement(CFloorEntity& c_entity) {
      // TODO
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::DrawElement(CFootBotEntity& c_entity) {
      /* Draw rays */
      DrawRays(c_entity.GetControllableEntity());
      /* Perform standard rotation and translation */
      DrawPositionalEntity(c_entity.GetEmbodiedEntity());
      /* Render the object */
      m_cFootBotModel.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::DrawElement(CEyeBotEntity& c_entity) {
      /* Draw rays */
      DrawRays(c_entity.GetControllableEntity());
      /* Perform standard rotation and translation */
      DrawPositionalEntity(c_entity.GetEmbodiedEntity());
      /* Render the object */
      m_cEyeBotModel.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::DrawElement(CLightEntity& c_entity) {
      /* Perform standard rotation and translation */
      DrawPositionalEntity(c_entity);
      /* Render the object */
      m_cLightModel.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLVisitor::DrawElement(CEPuckEntity& c_entity) {
      /* Draw rays */
      DrawRays(c_entity.GetControllableEntity());
      /* Perform standard rotation and translation */
      DrawPositionalEntity(c_entity.GetEmbodiedEntity());
      /* Render the object */
      m_cEPuckModel.Draw(c_entity);
   }

   /****************************************/
   /****************************************/

}

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
 * @file <simulator/visualizations/models/qtopengl_light.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "qtopengl_light.h"
#include <argos2/common/utility/math/vector3.h>
#include <argos2/simulator/space/entities/light_entity.h>

#include <argos2/common/utility/logging/argos_log.h>

namespace argos {

   /****************************************/
   /****************************************/

   CQTOpenGLLight::CQTOpenGLLight() :
      m_unVertexes(20),
      m_fRadius(0.1f) {
      /* Reserve a display list */
      m_unList = glGenLists(1);

      /* Start the display list */
      glNewList(m_unList, GL_COMPILE);

      /* Let's start the actual shape, a sphere */
      CVector3 cNormal, cPoint;
      CRadians cSlice(CRadians::TWO_PI / m_unVertexes);

      glBegin(GL_TRIANGLE_STRIP);
      for(CRadians cInclination; cInclination <= CRadians::PI; cInclination += cSlice) {
         for(CRadians cAzimuth; cAzimuth <= CRadians::TWO_PI; cAzimuth += cSlice) {

            cNormal.FromSphericalCoords(1.0f, cInclination, cAzimuth);
            cPoint = m_fRadius * cNormal;
            glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
            glVertex3f(cPoint.GetX(), cPoint.GetY(), cPoint.GetZ());

            cNormal.FromSphericalCoords(1.0f, cInclination + cSlice, cAzimuth);
            cPoint = m_fRadius * cNormal;
            glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
            glVertex3f(cPoint.GetX(), cPoint.GetY(), cPoint.GetZ());

            cNormal.FromSphericalCoords(1.0f, cInclination, cAzimuth + cSlice);
            cPoint = m_fRadius * cNormal;
            glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
            glVertex3f(cPoint.GetX(), cPoint.GetY(), cPoint.GetZ());

            cNormal.FromSphericalCoords(1.0f, cInclination + cSlice, cAzimuth + cSlice);
            cPoint = m_fRadius * cNormal;
            glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
            glVertex3f(cPoint.GetX(), cPoint.GetY(), cPoint.GetZ());

         }
      }
      glEnd();

      /* End of the display list */
      glEndList();
   }

   /****************************************/
   /****************************************/

   CQTOpenGLLight::~CQTOpenGLLight() {
      glDeleteLists(m_unList, 1);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLLight::Draw(CLightEntity& c_entity) {
      /* Set the material */
      const CColor& cColor = c_entity.GetLEDEntity().GetColor();
      const GLfloat pfColor[]     = {   cColor.GetRed(), cColor.GetGreen(), cColor.GetBlue(), 1.0f };
      const GLfloat pfSpecular[]  = {              0.0f,              0.0f,             0.0f, 1.0f };
      const GLfloat pfShininess[] = {             100.0f                                           };
      const GLfloat pfEmission[]  = {               0.0f,             0.0f,             0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, pfEmission);

      glCallList(m_unList);
   }

   /****************************************/
   /****************************************/

}

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

#ifndef QTOPENGL_LIGHT_H
#define QTOPENGL_LIGHT_H

namespace argos {
   class CQTOpenGLLight;
   class CLightEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos {

   class CQTOpenGLLight {

   public:

      CQTOpenGLLight();

      virtual ~CQTOpenGLLight();

      virtual void Draw(CLightEntity& c_entity);

   private:

      GLuint m_unList;
      GLuint m_unVertexes;
      GLfloat m_fRadius;

   };

}

#endif

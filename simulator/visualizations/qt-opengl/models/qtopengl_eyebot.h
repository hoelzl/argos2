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
 * @file <simulator/visualizations/models/qtopengl_eyebot.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef QTOPENGL_EYEBOT_H
#define QTOPENGL_EYEBOT_H

namespace argos {
   class CQTOpenGLEyeBot;
   class CEyeBotEntity;
}


#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos {

   class CQTOpenGLEyeBot {

   public:

      CQTOpenGLEyeBot();

      virtual ~CQTOpenGLEyeBot();

      virtual void Draw(CEyeBotEntity& c_entity);

   protected:

      /** Sets a colored LED material */
      void SetLEDMaterial(GLfloat f_red, GLfloat f_green, GLfloat f_blue);

      /** Sets a shiny gray material */
      void SetBodyMaterial();

      /** An eye-bot leg */
      void MakeLeg();

      /** A single LED of the side ring */
      void DrawSideLED();

      /** A single LED of the bottom ring */
      void DrawBottomLED();

      /** The eye-bot body */
      void DrawBody();

   private:

      /** Start of the display list index */
      GLuint m_unLists;

      /** Leg display list */
      GLuint m_unLegList;

      /** Body display list */
      GLuint m_unBodyList;

      /** Side LED display list */
      GLuint m_unSideLEDList;

      /** Bottom LED display list */
      GLuint m_unBottomLEDList;

      /** Number of vertices to display the round parts */
      GLuint m_unVertices;

      /* Angle gap between two leds */
      GLfloat m_fLEDAngleSlice;

   };

}

#endif

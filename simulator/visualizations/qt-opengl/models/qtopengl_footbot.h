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
 * @file <simulator/visualizations/models/qtopengl_footbot.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef QTOPENGL_FOOTBOT_H
#define QTOPENGL_FOOTBOT_H

namespace argos {
   class CQTOpenGLFootBot;
   class CFootBotEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos {

   class CQTOpenGLFootBot {

   public:

      CQTOpenGLFootBot();

      virtual ~CQTOpenGLFootBot();

      virtual void Draw(CFootBotEntity& c_entity);

   protected:

      /** Renders a materialless wheel
          - centered in 0,0,0
          - rotation axis: Y
       */
      void MakeWheel();

      /** Sets a white plastic material */
      void SetWhitePlasticMaterial();
      /** Sets a black tire material */
      void SetBlackTireMaterial();
      /** Sets a circuit board material */
      void SetCircuitBoardMaterial();
      /** Sets a colored LED material */
      void SetLEDMaterial(GLfloat f_red, GLfloat f_green, GLfloat f_blue);

      /** Renders the wheels */
      void RenderWheel();
      /** Renders the tracks */
      void RenderTrack();
      /** Renders the base (apart from the wheels) */
      void RenderBase();
      /** Renders a slice of the gripper module (LEDs) */
      void RenderGrippableSlice();
      /** Renders the gripper */
      void RenderGripperMechanics();
      /** Renders the gripper */
      void RenderGripperClaw();
      /** Renders the RAB module */
      void RenderRAB();
      /** Renders a single sensor of the distance scanner */
      void RenderDistanceScannerSensor();
      /** Renders the distance scanner */
      void RenderDistanceScanner();
      /** Renders the iMX module */
      void RenderIMX();
      /** Renders the beacon */
      void RenderBeacon();
      /** Renders the camera */
      void RenderCamera();

   private:

      /** Start of the display list index */
      GLuint m_unLists;

      /** List corresponding to the materialless wheel */
      GLuint m_unBasicWheelList;

      /** Foot-bot wheel */
      GLuint m_unWheelList;
      /** Foot-bot track */
      GLuint m_unTrackList;
      /** Foot-bot base module */
      GLuint m_unBaseList;
      /** Foot-bot grippable slice */
      GLuint m_unGrippableSliceList;
      /** Foot-bot gripper mechanics */
      GLuint m_unGripperMechanicsList;
      /** Foot-bot gripper claw */
      GLuint m_unGripperClawList;
      /** Foot-bot RAB module */
      GLuint m_unRABList;
      /** Foot-bot single distance scanner sensor */
      GLuint m_unDistanceScannerSensorList;
      /** Foot-bot distance scanner */
      GLuint m_unDistanceScannerList;
      /** Foot-bot iMX module */
      GLuint m_unIMXList;
      /** Foot-bot beacon */
      GLuint m_unBeaconList;
      /** Foot-bot camera module */
      GLuint m_unCameraList;

      /** Number of vertices to display the round parts
          (wheels, chassis, etc.) */
      GLuint m_unVertices;

      /* Angle gap between two leds */
      GLfloat m_fLEDAngleSlice;

   };

}

#endif

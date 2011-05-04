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
 * @file <common/control_interface/handbot/ci_handbot_gripper_cameras.h>
 *
 * @brief This file provides the definition of the handbot cameras in the grippers
 * The cameras in the hand-bot's gripper are RGB cameras, that can capture an image of
 * 640X480 pixels (we refer to it as Camera-Image).
 * The camera can work in 4 modalities: black and white, RGB, black ad white with edge
 * detection, RGB with edge detection. At the moment of writing the 2 black and white modalities
 * do not work (ASEBA complains at compile time).
 *
 * Given the limited amount of memory on the PIC, only a portion of the Camera-Image can
 * be copied from the sensor to the micro controller. ASEBA's native camera functions
 * allow to define a sampling interval in terms of pixels (vertical and horizontal). By doing this a subset of
 * the Camera-Image is copied on the PIC (we refer to it as PIC-Image).
 *
 * In addition, the PIC-Image cannot be sent on the bus, as it would
 * saturate it and ASEBA would crash. Therefore only a line of the PIC-IMage is
 * sent through an ASEBA event so that it can be used in the robot's controller.
 * This information is not sent every control step, but only at fixed intervals.
 *
 * The PIC-Image line that is sent on the bus can be selected by the user.
 *
 * The parameters of the camera (sempling intervals, camera mode) cannot be selected
 * by the user, as the robot could crash if the setup is wrong. We decided to embed
 * the camera tuning inside the aseba backend, and leave to the user only the choice
 * on which line is sent on the bus.
 *
 * Resuming:
 *
 * 640X480 image is sampled before being stored on the PIC.
 * Only a line of the image on the PIC is sent on the bus.
 * This line is sent at fixed intervals, skipping some control cycles.
 * The line sent on the bus can be selected by the user.
 * Other camera parameters are pre-selected in the aseba backend.
 * 
 *
 * Currently the camera samples 80 pixels on the horizontal direction (1 every 8)
 * and 15 lines on the vertical direction (1 every 32). The camera mode is set
 * to RGB ith edge detection. Therefore the user receives 80 pixels from the selected
 * line (1 of the possible 15).
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 *
 */

#ifndef CCI_HANDBOT_GRIPPER_CAMERAS_H
#define CCI_HANDBOT_GRIPPER_CAMERAS_H

namespace argos
{
  class CCI_HandBotGripperCameras;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/datatypes/color.h>

namespace argos {

   class CCI_HandBotGripperCameras : public CCI_Sensor {

   public:

       /* Possible color codings, the user can choose */
       static const UInt8 COLOR_MODE_RGB;
       static const UInt8 COLOR_MODE_HSV;
       /* The camera sends back a line this long (num pixels) */
       static const UInt8 CAMERA_LINE_LENGTH;

       struct ColorHSV{
           Real H;
           Real S;
           Real V;

           ColorHSV(Real h, Real s, Real v) {
               H = h;
               S = s;
               V = v;
           }

       };

      typedef std::vector<CColor> RGBVector;
      typedef std::vector<ColorHSV> HSVVector;

      struct THandReadings {
          RGBVector RGB;
          HSVVector HSV;
      };

      struct TReadings {
          THandReadings Left;
          THandReadings Right;
      };

      /** Structure to store the lines to be sent on the bus for the left-gripper and the right-gripper camera*/
      struct SGripperCamerasLinesToFetch {
          UInt32 m_unLineLeft;
          UInt32 m_unLineRight;
      };

      /**
       *
       * Destructor.
       *
       **/
      virtual ~CCI_HandBotGripperCameras() {
      }


      /**
       *
       * @brief Returns the readings of both the cameras
       *
       * @return the cameras readings
       *
       **/
      inline virtual const TReadings& GetAllReadings() const {
    	  return m_tReadings;
      }

      /**
       *
       * @brief Returns the readings of the left-gripper camera
       *
       * @return the left-gripper's camera readings
       *
       **/
      inline virtual const THandReadings GetReadingsLeft() const {
    	  return m_tReadings.Left;
      }

      /**
       *
       * @brief Returns the readings of the right-gripper camera
       *
       * @return the right-gripper's camera readings
       *
       **/
      inline virtual const THandReadings GetReadingsRight() const {
          return m_tReadings.Right;
      }

      /**
       *
       * @brief Sets the line that will be sent on the bus by the left-gripper camera
       * Line must be in 0-14, or the method will have no effect
       *
       * @param un_line_to_fetch line to fetch on the left-gripper camera
       *
       **/
      virtual void SetLineToFetchLeft (UInt32 un_line_to_fetch) = 0;

      /**
       *
       * @brief Sets the line that will be sent on the bus by the right-gripper camera
       * Line must be in 0-14, or the method will have no effect
       *
       * @param un_line_to_fetch line to fetch on the right-gripper camera
       *
       **/
      virtual void SetLineToFetchRight (UInt32 un_line_to_fetch) = 0;

      /**
       *
       * @brief Sets the color encoding to RGB
       *
       *
       **/
      virtual void SetRGBColorMode () = 0;

      /**
       *
       * @brief Sets the color encoding to HSV
       *
       *
       **/
      virtual void SetHSVColorMode () = 0;

      /**
       *
       * @brief Gets the color encoding mode
       *
       * @return current color encoding scheme
       *
       **/
      inline virtual UInt8 GetColorMode () {
          return m_unColorMode;
      }

      /**
       *
       * @brief Disables data sending on the bus
       *
       **/
      virtual void DisableDataSending() = 0;

      /**
       *
       * @brief Enables data sending on the bus
       *
       **/
      virtual void EnableDataSending() = 0;

      /**
       *
       * @brief Checks is data sending is enabled
       *
       * @return true if data sending is enabled
       *
       **/
       inline virtual bool IsDataSendingEnabled() {
           return m_bIsDataSendingEnabled;
       }


       /**
        *
        * @brief Convert the given RGB color in HSV
        *
        * @param c_rgb_color reg color to convert in hsv
        * @return HSV enconding of the given color
        *
        **/
       static ColorHSV RGBToHSV( CColor c_rgb_color);

   protected:

      TReadings m_tReadings;
      SGripperCamerasLinesToFetch m_sCameraLinesToFetch;
      UInt8 m_unColorMode;
      bool m_bIsDataSendingEnabled;

   };

}

#endif

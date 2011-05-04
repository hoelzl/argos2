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
 * @file <common/control_interface/handbot/ci_handbot_gripper_cameras.cpp>
 *
 * @brief This file provides the implementation of the handbot gripper cameras.
 *
 * @author Giovanni Pini - <gpini@iridia.ulb.ac.be>
 */

#include "ci_handbot_gripper_cameras.h"

/****************************************/
/****************************************/

namespace argos {

   /****************************************/
   /****************************************/

   const UInt8 CCI_HandBotGripperCameras::COLOR_MODE_RGB = 0;
   const UInt8 CCI_HandBotGripperCameras::COLOR_MODE_HSV = 1;
   const UInt8 CCI_HandBotGripperCameras::CAMERA_LINE_LENGTH = 160;

   /****************************************/
   /****************************************/

   CCI_HandBotGripperCameras::ColorHSV CCI_HandBotGripperCameras::RGBToHSV( CColor c_rgb_color) {

       Real fH,fS,fV;

       UInt8 unMin;
       if( c_rgb_color.GetRed() <= c_rgb_color.GetBlue() && c_rgb_color.GetRed() <= c_rgb_color.GetGreen()) {
           unMin = c_rgb_color.GetRed();
       }
       else if( c_rgb_color.GetBlue() <= c_rgb_color.GetRed() && c_rgb_color.GetBlue() <= c_rgb_color.GetGreen()) {
           unMin = c_rgb_color.GetBlue();
       }
       else {
           unMin = c_rgb_color.GetGreen();
       }

       UInt8 unMax;
       if( c_rgb_color.GetRed() >= c_rgb_color.GetBlue() && c_rgb_color.GetRed() >= c_rgb_color.GetGreen()) {
           unMax = c_rgb_color.GetRed();
       }
       else if( c_rgb_color.GetBlue() >= c_rgb_color.GetRed() && c_rgb_color.GetBlue() >= c_rgb_color.GetGreen()) {
           unMax = c_rgb_color.GetBlue();
       }
       else {
           unMax = c_rgb_color.GetGreen();
       }

       UInt8 unDelta = unMax - unMin;

       fV = unMax;

       if(unMax == 0)
           fS = 0.0;
       else
           fS = Real(unDelta * 255) / Real(unMax);


       if(fS == 0) {
           fH = 0.0; // Undefined, 0 for now
       } else {

           if(c_rgb_color.GetRed() == unMax) {
               fH = (60 * ((Real)c_rgb_color.GetGreen() - (Real)c_rgb_color.GetBlue())) / (Real)unDelta;
           } else {
               if(c_rgb_color.GetGreen() == unMax)
                   fH = 120 + (60 * ((Real)c_rgb_color.GetBlue() - (Real)c_rgb_color.GetRed())) / (Real)unDelta;
               else
                   fH = 240 + (60 * ((Real)c_rgb_color.GetRed() - (Real)c_rgb_color.GetGreen())) / (Real)unDelta;
           }

           if(fH < 0) {
               fH += 360.0;
           }
       }

       return CCI_HandBotGripperCameras::ColorHSV(fH,fS,fV);

   }

   /****************************************/
   /****************************************/

}


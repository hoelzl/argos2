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
 * @file <argos2/common/control_interface/eyebot/ci_eyebot_pan_and_tilt_camera_actuator.h>
 *
 * @brief This file provides the definition of the eyebot pan and tilt actuator.
 *
 * @author Frederick Ducatelle - <frederick@idsia.ch>
 */

#ifndef CI_EYEBOT_PAN_AND_TILT_CAMERA_ACTUATOR_H
#define CI_EYEBOT_PAN_AND_TILT_CAMERA_ACTUATOR_H


/* To avoid dependency problems when including */
namespace argos
{
   class CCI_EyeBotPanAndTiltCameraActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>
#include <argos2/common/utility/math/angles.h>

namespace argos
{

   class CCI_EyeBotPanAndTiltActuator: public CCI_Actuator {

   public:

      virtual void SetPan(const CRadians& c_pan) = 0;
      virtual void SetTilt(const CRadians& c_tilt) = 0;
      virtual void ActivateLaser(const bool b_activate) = 0;

   };

}

#endif

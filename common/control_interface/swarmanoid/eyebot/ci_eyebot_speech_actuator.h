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
 * @file <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_speech_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef CI_EYEBOT_SPEECH_ACTUATOR_H
#define CI_EYEBOT_SPEECH_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_EyeBotSpeechActuator;
}

#include <argos2/common/control_interface/ci_actuator.h>

namespace argos {

   class CCI_EyeBotSpeechActuator: public CCI_Actuator {

   public:

      static const UInt32 MESSAGE_LENGTH;

      /**
       * Set the text of the speech actuator.
       * Works only properly for english.
       */
      virtual void SetText(const std::string& str_text) = 0;

      /**
       * The speech actuator volume (0-255).
       */
      virtual void SetVolume(const UInt8 un_volume) = 0;

      /*
       * Mutes the speech actuator.
       * Note: you have to mute the speech after one timestep otherwise it
       * goes on speaking forever. If you mute it earlier than this
       * (i.e., immidiatly after setting a text) no sound is emitted.
       */
      virtual void Mute() = 0;

   };

}

#endif

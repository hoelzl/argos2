/* -*- Mode: C++ -*-
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
 * @file <argos2/simulator/sensors/foot-bot/footbot_base_ground_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "footbot_base_ground_sensor.h"
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/floor_entity.h>
#include <argos2/simulator/space/space.h>

namespace argos {

   /****************************************/
   /****************************************/

   CFootBotBaseGroundSensor::CFootBotBaseGroundSensor() :
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_bCalibrated(true),
      m_pcRNG(NULL),
      m_fNoiseLevel(0.0f) {
   }


   /****************************************/
   /****************************************/

   void CFootBotBaseGroundSensor::Init(TConfigurationNode& t_tree) {
      try {
         /* Parse noise level */
         GetNodeAttributeOrDefault(t_tree, "noise_level", m_fNoiseLevel, m_fNoiseLevel);
	 m_fNoiseLevel *= FOOTBOT_BASE_GROUND_SENSOR_READING_RANGE.GetSpan();

	 /* Parse calibration flag */
         GetNodeAttributeOrDefault(t_tree, "calibrate", m_bCalibrated, m_bCalibrated);
	 if( !m_bCalibrated ) LOGERR << "[WARNING] Using base ground sensors without calibration" << std::endl;
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in foot-bot base ground sensor", ex);
      }
      
      /* Random number generator*/
      m_pcRNG = CARGoSRandom::CreateRNG("argos");
   }

   /****************************************/
   /****************************************/

   void CFootBotBaseGroundSensor::Update() {
      /* We make the assumption that the foot-bot is rotated only wrt to Z */
      CFloorEntity& cFloorEntity = m_cSpace.GetFloorEntity();
      const CVector3& cEntityPos = GetEntity().GetEmbodiedEntity().GetPosition();
      const CQuaternion& cEntityRot = GetEntity().GetEmbodiedEntity().GetOrientation();
      CRadians cRotZ, cRotY, cRotX;
      cEntityRot.ToEulerAngles( cRotZ, cRotY, cRotX );
      CVector2 cCenterPos(cEntityPos.GetX(), cEntityPos.GetY());
      
      CVector2 cSensorPos;
      for(UInt32 i = 0; i < CCI_FootBotBaseGroundSensor::NUM_READINGS; ++i) {
         cSensorPos  = m_tReadings[i].Offset;
         cSensorPos.Rotate(cRotZ);
	 cSensorPos *= 0.01;
	 cSensorPos += cCenterPos;
         const CColor& cColor = cFloorEntity.GetColorAtPoint(cSensorPos.GetX(),cSensorPos.GetY());
         m_tReadings[i].Value = cColor.ToGrayScale()/255*FOOTBOT_BASE_GROUND_SENSOR_READING_RANGE.GetSpan();

	 if( m_fNoiseLevel > 0.0 ) {
	    AddNoise(i);
	 }

	 /* Normalize reading between 0 and 1, only if calibration has been performed */
         if( m_bCalibrated ) {
	    m_tReadings[i].Value = FOOTBOT_BASE_GROUND_SENSOR_READING_RANGE.NormalizeValue(m_tReadings[i].Value);
	 }
      }
   }

   /****************************************/
   /****************************************/

   void CFootBotBaseGroundSensor::Reset() {
      for(UInt32 i = 0; i < CCI_FootBotBaseGroundSensor::NUM_READINGS; ++i) {
         m_tReadings[i].Value = 0.0f;
      }
   }


   /****************************************/
   /****************************************/

   void CFootBotBaseGroundSensor::AddNoise(UInt32 un_sensor_index) {
      m_tReadings[un_sensor_index].Value += m_pcRNG->Uniform(CRange<Real>(-m_fNoiseLevel, m_fNoiseLevel));
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CFootBotBaseGroundSensor,
                   "footbot_base_ground", "rot_z_only",
                   "The foot-bot base ground sensor (optimized for 2D)",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "This sensor accesses the foot-bot base ground sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n"
                   "In this implementation, the readings are calculated under the assumption that\n"
                   "the foot-bot is always parallel to the XY plane, i.e., it rotates only around\n"
                   "the Z axis. This implementation is faster than a 3D one and should be used\n"
                   "only when the assumption about the foot-bot rotation holds.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_base_ground implementation=\"rot_z_only\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "It is possible to specify noisy sensors in order to match the characteristics\n"
                   "of the real robot. This can be done with two xml parameters: 'noise_level'\n"
                   "indicates a percentage of the sensor range that is added to the actual sensor\n"
                   "reading. The added noise value is uniformly random on this range." 
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_motor_ground implementation=\"rot_z_only\"\n"
                   "                                  noise_level=\"0.05\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n"
		   "Use the flag 'calibrate' to specify that the readings must be scaled in [0:1]."
                   "  <controllers>\n"
                   "    ...\n"		 
		   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <footbot_motor_ground implementation=\"rot_z_only\"\n"
                   "                                  calibrate=\"true\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Under development"
		   );

}

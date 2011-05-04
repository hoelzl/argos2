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
 * @file <argos2/simulator/sensors/e-puck/epuck_camera_sensor.h>
 *
 * @brief This file provides the definition of the camera sensor of the e-puck.
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef EPUCK_CAMERA_SENSOR_H
#define EPUCK_CAMERA_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckCameraSensor;
   class CSpace;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_camera_sensor.h>
#include <argos2/simulator/sensors/e-puck/epuck_sensor.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>

namespace argos {

   class CEPuckCameraSensor : public CEPuckSensor,
                              public CCI_EPuckCameraSensor {

   public:

      CEPuckCameraSensor();
      virtual ~CEPuckCameraSensor() {}

      inline virtual void SetEntity(CEntity& c_entity) {
         CEPuckSensor::SetEntity(c_entity);
         m_pcLEDEntity = &(GetEntity().GetLEDEquippedEntity());
      }

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();
      virtual void Reset();

      virtual void Destroy();

      virtual void Enable() {
         m_bEnabled = true;
      }

      virtual void Disable() {
         m_bEnabled = false;
      }

      virtual void ChangeResolution(UInt16 un_width, UInt16 un_height);
      virtual UInt16 GetWidth();
      virtual UInt16 GetHeight();

   private:

      void InitCamera();
      void CalculateCellsToAnalyze();
      void ComputeCameraReadings();
      void ComputeView(Real f_distance, CRadians * pc_angle, CColor c_color);

   private:

      UInt8 m_unPixels;
      bool m_bEnabled;
      UInt16 m_unWidth;
      UInt16 m_unHeight;
      CSpace& m_cSpace;
      CSpaceHash<CEmbodiedEntity, CEmbodiedEntitySpaceHashUpdater>& m_cEmbodiedSpaceHash;
      CSpaceHash<CLedEntity, CLEDEntitySpaceHashUpdater>& m_cLEDSpaceHash;
      CLedEquippedEntity* m_pcLEDEntity;
      UInt16 m_unCameraElevation;      

      bool m_bShowRays;

      struct SCellCoords {
         SInt16 I, J, K;

         SCellCoords(SInt16 n_i, SInt16 n_j, SInt16 n_k) :
            I(n_i), J(n_j), K(n_k) {}
      };
      std::vector<SCellCoords> m_sCellsToVisit;

   };

}

#endif

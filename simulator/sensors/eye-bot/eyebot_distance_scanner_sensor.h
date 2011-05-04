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
 * @file <argos2/simulator/sensors/eye-bot/eyebot_distance_scanner_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef EYEBOT_DISTANCE_SCANNER_SENSOR_H
#define EYEBOT_DISTANCE_SCANNER_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEyeBotDistanceScannerSensor;
}

#include <argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_distance_scanner_sensor.h>
#include <argos2/simulator/sensors/eye-bot/eyebot_sensor.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>
#include <argos2/simulator/space/entities/distance_scanner_equipped_entity.h>
#include <argos2/simulator/space/space.h>

namespace argos {

   class CEyeBotDistanceScannerSensor : public CEyeBotSensor,
                                        public CCI_EyeBotDistanceScannerSensor {

   public:

      CEyeBotDistanceScannerSensor();
      virtual ~CEyeBotDistanceScannerSensor() {}

      virtual void Init(TConfigurationNode& t_tree);

      inline virtual void SetEntity(CEntity& c_entity) {
         CEyeBotSensor::SetEntity(c_entity);
         m_pcDistScanEntity = &(GetEntity().GetDistanceScannerEquippedEntity());
         m_pcEmbodiedEntity = &(GetEntity().GetEmbodiedEntity());
      }

      virtual void Update();
      virtual void Reset();

   private:

      Real CalculateReadingForRay(const CRay& c_ray);
   private:

      CSpace& m_cSpace;
      CSpaceHash<CEmbodiedEntity, CEmbodiedEntitySpaceHashUpdater>& m_cEmbodiedSpaceHash;
      CDistanceScannerEquippedEntity* m_pcDistScanEntity;
      CEmbodiedEntity* m_pcEmbodiedEntity;

      bool m_bShowRays;
      CRadians m_cAngleSlice;

      /* Internally used to speed up ray calculations */
      CVector3 m_cRayStart;
      CVector3 m_cRayEnd;
   };

}

#endif

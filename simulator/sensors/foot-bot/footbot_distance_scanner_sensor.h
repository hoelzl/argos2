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
 * @file <argos2/simulator/sensors/foot-bot/footbot_distance_scanner_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_DISTANCE_SENSOR_H
#define FOOTBOT_DISTANCE_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CFootBotDistanceScannerSensor;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_distance_scanner_sensor.h>
#include <argos2/simulator/sensors/foot-bot/footbot_sensor.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/distance_scanner_equipped_entity.h>
#include <argos2/simulator/space/space.h>

namespace argos {
   
   class CFootBotDistanceScannerSensor : public CFootBotSensor,
                                         public CCI_FootBotDistanceScannerSensor {

   public:

      CFootBotDistanceScannerSensor();
      virtual ~CFootBotDistanceScannerSensor() {}

      virtual void Init(TConfigurationNode& t_tree);

      inline virtual void SetEntity(CEntity& c_entity) {
         CFootBotSensor::SetEntity(c_entity);
         m_pcDistScanEntity = &(GetEntity().GetDistanceScannerEquippedEntity());
         m_pcEmbodiedEntity = &(GetEntity().GetEmbodiedEntity());
      }

      virtual void Update();
      virtual void Reset();

   private:

      void UpdateNotRotating();
      void UpdateRotating();

      Real CalculateReadingForRay(const CRay& c_ray,
                                  Real f_min_distance);

      void CalculateRaysNotRotating();
      void CalculateRaysRotating();

   private:

      CSpace& m_cSpace;
      CDistanceScannerEquippedEntity* m_pcDistScanEntity;
      CEmbodiedEntity* m_pcEmbodiedEntity;
      CRadians m_cLastDistScanRotation;

      bool m_bShowRays;

      CRay m_cShortRangeRays0[6];
      CRay m_cShortRangeRays2[6];
      CRay m_cLongRangeRays1[6];
      CRay m_cLongRangeRays3[6];

      /* Internally used to speed up ray calculations */
      CVector3 m_cDirection;
      CVector3 m_cOriginRayStart;
      CVector3 m_cOriginRayEnd;
      CVector3 m_cRayStart;
      CVector3 m_cRayEnd;
   };

}

#endif

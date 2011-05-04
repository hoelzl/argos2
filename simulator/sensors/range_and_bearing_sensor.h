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
 * @file <argos2/simulator/sensors/foot-bot/footbot_range_and_bearing_sensor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef FOOTBOT_RANGE_AND_BEARING_SENSOR_H
#define FOOTBOT_RANGE_AND_BEARING_SENSOR_H

namespace argos {
   class CRangeAndBearingSensor;
   class CControllableEntity;
}

#include <argos2/simulator/sensors/simulated_sensor.h>
#include <argos2/common/control_interface/swarmanoid/ci_range_and_bearing_sensor.h>
#include <argos2/simulator/space/entities/rab_equipped_entity.h>
#include <argos2/simulator/space/space.h>

namespace argos {

   class CRangeAndBearingSensor : public CSimulatedSensor,
                                  public CCI_RangeAndBearingSensor {

   public:

      CRangeAndBearingSensor();
      virtual ~CRangeAndBearingSensor() {}

      virtual void Init(TConfigurationNode& t_tree);

      inline virtual CEntity& GetEntity() {
         return *m_pcEntity;
      }
      inline virtual void SetEntity(CEntity& c_entity);
      
      virtual void Update();
      virtual void Reset();

      virtual UInt16 GetRabIdFromRobotId(const std::string& str_robot_id) {
         return m_pcRABEquippedEntity->GetNumericId();
      }

      virtual const std::string& GetRobotIdFromRabId(UInt16 un_rab_id) {
         return m_pcRABEquippedEntity->GetId();
      }

   private:

      CSpace& m_cSpace;
      CSpaceHash<CEmbodiedEntity, CEmbodiedEntitySpaceHashUpdater>& m_cEmbodiedSpaceHash;
      CEntity* m_pcEntity;
      CRABEquippedEntity<10>* m_pcRABEquippedEntity;
      CEmbodiedEntity* m_pcEmbodiedEntity;
      CControllableEntity* m_pcControllableEntity;

      bool m_bShowRays;
      bool m_bCheckOcclusions;
   };

}

#endif

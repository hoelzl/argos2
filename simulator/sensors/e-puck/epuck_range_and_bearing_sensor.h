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
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef EPUCK_RANGE_AND_BEARING_SENSOR_H
#define EPUCK_RANGE_AND_BEARING_SENSOR_H

namespace argos {
   class CEPuckRangeAndBearingSensor;
   class CControllableEntity;
}

#include <argos2/simulator/sensors/e-puck/epuck_sensor.h>
#include <argos2/common/control_interface/e-puck/ci_epuck_range_and_bearing_sensor.h>
#include <argos2/simulator/space/entities/rab_equipped_entity.h>
#include <argos2/simulator/space/space.h>

namespace argos {

   class CEPuckRangeAndBearingSensor : public CSimulatedSensor,
                                  public CCI_EPuckRangeAndBearingSensor {

   public:

      CEPuckRangeAndBearingSensor();
      virtual ~CEPuckRangeAndBearingSensor() {}

      virtual void Init(TConfigurationNode& t_tree);

      inline virtual CEntity& GetEntity() {
         return *m_pcEntity;
      }
      inline virtual void SetEntity(CEntity& c_entity);
      
      virtual void Update();
      virtual void Reset();

      inline virtual UInt16 PacketToInt(const TEPuckRangeAndBearingReceivedPacket& t_packet){
          const UInt8 * unData = t_packet.Data;
          return 256*unData[0] + unData[1];
      }


   private:

      CSpace& m_cSpace;
      CSpaceHash<CEmbodiedEntity, CEmbodiedEntitySpaceHashUpdater>& m_cEmbodiedSpaceHash;
      CEntity* m_pcEntity;
      CRABEquippedEntity<2>* m_pcRABEquippedEntity;
      CEmbodiedEntity* m_pcEmbodiedEntity;
      CControllableEntity* m_pcControllableEntity;

      bool m_bShowRays;
      bool m_bCheckOcclusions;
   };

}

#endif

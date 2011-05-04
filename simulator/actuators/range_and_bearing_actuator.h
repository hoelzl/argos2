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
 * @file <argos2/simulator/actuators/range_and_bearing_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef RANGE_AND_BEARING_ACTUATOR_H
#define RANGE_AND_BEARING_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CRangeAndBearingActuator;
   class CCI_RangeAndBearingActuator;
}

#include <argos2/common/control_interface/swarmanoid/ci_range_and_bearing_actuator.h>
#include <argos2/simulator/actuators/simulated_actuator.h>
#include <argos2/simulator/space/entities/rab_equipped_entity.h>

namespace argos {

   class CRangeAndBearingActuator : public CSimulatedActuator,
                                    public CCI_RangeAndBearingActuator {

   public:

      CRangeAndBearingActuator();
      virtual ~CRangeAndBearingActuator() {}

      virtual void Init(TConfigurationNode& t_node);

      inline virtual CRABEquippedEntity<10>& GetEntity() {
         return *m_pcRABEquippedEntity;
      }
      virtual void SetEntity(CEntity& c_entity);

      virtual void SetData(const TRangeAndBearingReceivedPacket::TRangeAndBearingData& t_data);

      virtual void Update();
      virtual void Reset();

   private:

      CRABEquippedEntity<10>* m_pcRABEquippedEntity;
      TRangeAndBearingReceivedPacket::TRangeAndBearingData m_tData;
      Real m_fRange;

   };

}

#endif

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
 * @file <argos2/simulator/actuators/e-puck/epuck_range_and_bearing_actuator.h>
 *
 * @brief This file provides the definition of
 *
 * @author Laurent Compere - <lcompere@ulb.ac.be>
 */

#ifndef EPUCK_RANGE_AND_BEARING_ACTUATOR_H
#define EPUCK_RANGE_AND_BEARING_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEPuckRangeAndBearingActuator;
   class CCI_EPuckRangeAndBearingActuator;
}

#include <argos2/common/control_interface/e-puck/ci_epuck_range_and_bearing_actuator.h>
#include <argos2/simulator/actuators/e-puck/epuck_actuator.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/space/entities/rab_equipped_entity.h>

namespace argos {

   class CEPuckRangeAndBearingActuator : public CSimulatedActuator,
                                    public CCI_EPuckRangeAndBearingActuator {

   public:

      CEPuckRangeAndBearingActuator();
      virtual ~CEPuckRangeAndBearingActuator() {}

      virtual void Init(TConfigurationNode& t_node);

      inline virtual CRABEquippedEntity<2>& GetEntity() {
         return *m_pcRABEquippedEntity;
      }
      virtual void SetEntity(CEntity& c_entity);

      virtual void SetData(const TEPuckRangeAndBearingReceivedPacket::TRangeAndBearingData& t_data);

      virtual void SetDataInt(const UInt16& un_data);

      virtual void Update();
      virtual void Reset();


   private:

      CRABEquippedEntity<2>* m_pcRABEquippedEntity;
      TEPuckRangeAndBearingReceivedPacket::TRangeAndBearingData m_tData;
      Real m_fRange;

   };

}

#endif

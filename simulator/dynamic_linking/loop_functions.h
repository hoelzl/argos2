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
 * @file <argos2/simulator/dynamic_linking/loop_functions.h>
 *
 * @brief This file provides the definition of the loop functions.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef LOOP_FUNCTIONS_H
#define LOOP_FUNCTIONS_H

namespace argos {
   class CLoopFunctions;
   class CFloorEntity;
}

#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <argos2/common/utility/datatypes/color.h>
#include <argos2/common/utility/math/vector2.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/common/utility/math/quaternion.h>
#include <argos2/simulator/physics_engines/physics_engine.h>
#include <argos2/simulator/dynamic_linking/dynamic_linking_manager.h>

namespace argos {

   class CLoopFunctions : public CBaseConfigurableResource {

   protected:

      CSimulator& m_cSimulator;
      CSpace& m_cSpace;

   public:

      struct SAdditionalLED {
         CVector3 Position;
         CColor Color;

         SAdditionalLED() {}
         
         SAdditionalLED(const CVector3& c_position,
                        const CColor& c_color) :
            Position(c_position),
            Color(c_color) {}
      };

   public:

      CLoopFunctions() :
         m_cSimulator(CSimulator::GetInstance()),
         m_cSpace(m_cSimulator.GetSpace()) {
      }
      virtual ~CLoopFunctions() {}

      inline virtual void Init(TConfigurationNode& t_tree) {}
      inline virtual void Reset() {}
      inline virtual void Destroy() {}

      inline virtual void PrePhysicsEngineStep() {}
      inline virtual void PostPhysicsEngineStep() {}

      inline virtual bool IsExperimentFinished() {
         return false;
      }

      inline virtual CColor GetFloorColor(const CVector2& c_position_on_plane) {
         return CColor::BLACK;
      }

      virtual void SetOnlineControlParameters(UInt32 un_num_values,
                                              const Real* pf_values );

      inline virtual Real ComputePerformanceInExperiment(UInt32* un_num_components,
                                                         Real** pf_components ) {
         return 0;
      }

   protected:

      inline virtual bool MoveEntity(CPositionalEntity& c_entity,
                                     const CVector3& c_position,
                                     const CQuaternion& c_orientation,
                                     bool b_check_only) {
         return c_entity.MoveTo(c_position, c_orientation, b_check_only);
      }

      CBoxEntity& AddBox(const std::string& str_id,
                         const CVector3& c_position,
                         const CQuaternion& c_orientation,
                         const CVector3& c_size,
                         bool b_movable,
                         Real f_mass,
                         const std::vector<std::string>& str_physics_ids,
                         const std::vector<SAdditionalLED>& vec_additional_leds = std::vector<SAdditionalLED>(),
                         bool b_visible = true);

      CCylinderEntity& AddCylinder(const std::string& str_id,
                                   const CVector3& c_position,
                                   const CQuaternion& c_orientation,
                                   Real f_radius,
                                   Real f_height,
                                   bool b_movable,
                                   Real f_mass,
                                   const std::vector<std::string>& str_physics_ids,
                                   const std::vector<SAdditionalLED>& vec_additional_leds = std::vector<SAdditionalLED>(),
                                   bool b_visible = true);

      CLightEntity& AddLight(const std::string& str_id,
                             const CVector3& c_position,
                             Real f_intensity,
                             const CColor& c_color);

      CFootBotEntity& AddFootBot(const std::string& str_id,
                                 const CVector3& c_position,
                                 const CQuaternion& c_orientation,
                                 const std::string& str_controller_id,
                                 const std::string& str_physics_id);
      
      CEPuckEntity& AddEPuck(const std::string& str_id,
                             const CVector3& c_position,
                             const CQuaternion& c_orientation,
                             const std::string& str_controller_id,
                             const std::string& str_physics_id);
      
      inline virtual void RemoveEntity(const std::string& str_entity_id) {
         CEntity& entity = m_cSpace.GetEntity(str_entity_id);
         RemoveEntity(entity);
      }

      virtual void RemoveEntity(CEntity& c_entity);

   };
}

#endif

#include <argos2/simulator/dynamic_linking/loop_functions_registration.h>

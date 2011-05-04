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
 * @file <simulator/swarmanoid_space/entities/controllable_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CONTROLLABLE_ENTITY_H
#define CONTROLLABLE_ENTITY_H

namespace argos {
   class CControllableEntity;
   class CSimulatedActuator;
   class CSimulatedSensor;
}

#include <argos2/simulator/space/entities/entity.h>
#include <argos2/common/control_interface/ci_controller.h>
#include <argos2/common/utility/math/ray.h>

namespace argos {

   class CControllableEntity : public CEntity {

   public:
      CControllableEntity(CEntity* pc_parent) :
         CEntity(pc_parent),
         m_pcController(NULL) {}
      virtual ~CControllableEntity();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      inline const std::string& GetControllerId() const {
         return m_strControllerId;
      }

      inline CCI_Controller& GetController() {
         return *m_pcController;
      }
      void SetController(CCI_Controller& pc_controller);

      virtual void Sense();

      inline void ControlStep() {
         if(m_pcController != NULL) {
            m_pcController->ControlStep();
         }
         else {
            THROW_ARGOSEXCEPTION("Entity " << GetId() << " does not have any controller associated. Did you add it to the <arena_physics> section?");
         }
      }

      virtual void Act();

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "controllable_entity";
      }

      inline void AddCheckedRay(bool b_obstructed,
                                const CRay& c_ray) {
         m_vecCheckedRays.push_back(std::make_pair(b_obstructed, c_ray));
      }

      inline void AddIntersectionPoint(const CRay& c_ray,
                                       Real f_t_on_ray) {
         CVector3 cPoint;
         c_ray.GetPoint(cPoint, f_t_on_ray);
         m_vecIntersectionPoints.push_back(cPoint);
      }

      inline std::vector< std::pair<bool, CRay> >& GetCheckedRays() {
         return m_vecCheckedRays;
      }

      inline std::vector< CVector3 >& GetIntersectionPoints() {
         return m_vecIntersectionPoints;
      }

   protected:

      std::string m_strControllerId;
      CCI_Controller* m_pcController;

      std::map<std::string, CSimulatedActuator*> m_mapActuators;
      std::map<std::string, CSimulatedSensor*> m_mapSensors;

      std::vector< std::pair<bool, CRay> > m_vecCheckedRays;
      std::vector< CVector3 > m_vecIntersectionPoints;

   };

   typedef std::vector<CControllableEntity*> TControllableEntityVector;
   typedef std::map<std::string, CControllableEntity*> TControllableEntityMap;

}

#endif

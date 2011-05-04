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
 * @file <simulator/swarmanoid_space/swarmanoid_space.h>
 *
 * @brief This file provides the definition of the Swarmanoid 3D Space.
 *
 * This file provides the definition of the Swarmanoid 3D Space.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef SPACE_H
#define SPACE_H

namespace argos {
   class CSpace;
   class CDynamicLinkingManager;
   class CRay;
   class CFloorEntity;
}

#include <argos2/simulator/space/entities/controllable_entity.h>
#include <argos2/simulator/space/entities/medium_entity.h>
#include <argos2/common/utility/configuration/base_configurable_resource.h>
#include <argos2/common/utility/datatypes/any.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/simulator/space/space_hash.h>
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/space/entities/led_entity.h>

namespace argos {

   /**
    * @class CSpace
    *
    * @brief The simulated 3D Space.
    *
    * The simulated 3D Space, the place where all entities live.
    *
    * @see CEntity
    */
   class CSpace : public CBaseConfigurableResource {

   public:

      /** Maps for quick access to physical entities (robots, objects) */
      typedef std::map <std::string, any, std::less <std::string> > TAnyEntityMap;
      typedef std::map <std::string, TAnyEntityMap, std::less <std::string> > TMapOfAnyEntityMaps;

      /****************************************/
      /****************************************/

      template <class E> struct SEntityIntersectionItem {
         E* IntersectedEntity;
         Real TOnRay;

         SEntityIntersectionItem() :
            IntersectedEntity(NULL),
            TOnRay(0.0f) {}

         SEntityIntersectionItem(E* pc_entity, Real f_t_on_ray) :
            IntersectedEntity(pc_entity),
            TOnRay(f_t_on_ray) {}

         inline bool operator<(const SEntityIntersectionItem& s_item) {
            return TOnRay < s_item.TOnRay;
         }
      };

      template <class E> struct SEntityIntersectionData {
         bool Intersection;
         std::vector<SEntityIntersectionItem<E>*> IntersectedEntities;

         SEntityIntersectionData() :
            Intersection(false) {}

         SEntityIntersectionData(std::vector<SEntityIntersectionItem<E>*>& c_entities) :
            Intersection(c_entities.size() > 0),
            IntersectedEntities(c_entities) {}
      };

   protected:

      class CRayEmbodiedEntityIntersectionMethod;
      class CRayEmbodiedEntityIntersectionSpaceHash;
      class CRayEmbodiedEntityIntersectionEntitySweep;

      /****************************************/
      /****************************************/

   protected:

      /** Reference to the controller manager */
      CDynamicLinkingManager* m_pcDynamicLinkingManager;

      /** The current simulation clock */
      UInt32 m_unSimulationClock;

      /** Arena size */
      CVector3 m_cArenaSize;

      /** A vector of entities. */
      TEntityVector m_vecEntities;

      /** A map of entities. */
      TEntityMap m_mapEntities;

      /** A map of maps of all the simulated entities.
          The map stores several submaps with the key equals to the
          type description of an entity. The submaps store the entities
          according to their id */
      TMapOfAnyEntityMaps m_mapOfMapsEntities;

      /** The space hash of embodied entities */
      CSpaceHash<CEmbodiedEntity, CEmbodiedEntitySpaceHashUpdater>* m_pcEmbodiedEntitiesSpaceHash;

      /** The space hash of LED entities */
      CSpaceHash<CLedEntity, CLEDEntitySpaceHashUpdater>* m_pcLEDEntitiesSpaceHash;

      /** A vector of controllable entities */
      TControllableEntityVector m_vecControllableEntities;

      /** A vector of medium entities */
      TMediumEntityVector m_vecMediumEntities;

      /** The floor entity */
      CFloorEntity* m_pcFloorEntity;

      /** True if the space hash should be used */
      bool m_bUseSpaceHash;

      /** Method to calculate the ray-embodied entity intersection */
      CRayEmbodiedEntityIntersectionMethod* m_pcRayEmbodiedEntityIntersectionMethod;

      /** A reference to the list of physics engines */
      TPhysicsEngineList* m_ptPhysicsEngines;

   public:

      CSpace();
      virtual ~CSpace() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      inline UInt32 GetNumberEntities() const {
         return m_vecEntities.size();
      }

      inline TEntityVector& GetEntityVector() {
         return m_vecEntities;
      }

      inline CEntity& GetEntity(const std::string& str_id) {
         TEntityMap::const_iterator it = m_mapEntities.find(str_id);
         if ( it != m_mapEntities.end()) {
            return *(it->second);
         }
         THROW_ARGOSEXCEPTION("Unknown entity id \"" << str_id <<
                              "\" when requesting entity from space.");
      }

      void GetEntitiesMatching(TEntityVector& t_buffer,
                               const std::string& str_pattern);

      bool GetClosestEmbodiedEntityIntersectedByRay(SEntityIntersectionItem<CEmbodiedEntity>& s_data,
                                                    const CRay& c_ray,
                                                    const TEmbodiedEntitySet& set_ignored_entities = TEmbodiedEntitySet());

      inline TEntityMap& GetAllEntities() {
         return m_mapEntities;
      }

      inline TMapOfAnyEntityMaps& GetEntitiesMapOfMaps() {
         return m_mapOfMapsEntities;
      }

      inline TAnyEntityMap& GetEntitiesByType(const std::string str_type) {
         TMapOfAnyEntityMaps::iterator itEntities = m_mapOfMapsEntities.find(str_type);
         if (itEntities != m_mapOfMapsEntities.end()){
            return itEntities->second;
         }
         THROW_ARGOSEXCEPTION("Entity map for type \"" << str_type << "\" not found.");
      }

      inline CFloorEntity& GetFloorEntity() {
         if(m_pcFloorEntity == NULL) {
            THROW_ARGOSEXCEPTION("No floor entity has been added to the space.");
         }
         return *m_pcFloorEntity;
      }

      inline void SetFloorEntity(CFloorEntity& c_floor_entity) {
         m_pcFloorEntity = &c_floor_entity;
      }

      inline bool IsUsingSpaceHash() const {
         return m_bUseSpaceHash;
      }

      inline virtual void SetPhysicsEngines(TPhysicsEngineList& t_engines) {
         m_ptPhysicsEngines = &t_engines;
      }

      virtual void Update();

      virtual void AddEntity(CEntity& c_entity);
      virtual void AddControllableEntity(CControllableEntity& c_entity);
      virtual void AddMediumEntity(CMediumEntity& c_entity);

      virtual void RemoveEntity(CEntity& c_entity);
      virtual void RemoveControllableEntity(CControllableEntity& c_entity);
      virtual void RemoveMediumEntity(CMediumEntity& c_entity);

      inline UInt32 GetSimulationClock() const {
         return m_unSimulationClock;
      }

      inline void SetSimulationClock(UInt32 un_simulation_clock) {
         m_unSimulationClock = un_simulation_clock;
      }

      inline void IncreaseSimulationClock(UInt32 un_increase = 1) {
         m_unSimulationClock += un_increase;
      }

      inline void SetDynamicLinkingManager(CDynamicLinkingManager& c_dynamic_linking_manager) {
         m_pcDynamicLinkingManager = &c_dynamic_linking_manager;
      }

      inline const CVector3& GetArenaSize() const {
         return m_cArenaSize;
      }

      inline void SetArenaSize(const CVector3& c_size) {
         m_cArenaSize = c_size;
      }

      inline CSpaceHash<CEmbodiedEntity, CEmbodiedEntitySpaceHashUpdater>& GetEmbodiedEntitiesSpaceHash() {
         if(IsUsingSpaceHash()) {
            return *m_pcEmbodiedEntitiesSpaceHash;
         }
         else {
            THROW_ARGOSEXCEPTION("Attempted to access the space hash of embodied entities, but in the XML the user chose not to use it. Maybe you use a sensor or an actuator that references it directly?");
         }
      }

      inline CSpaceHash<CLedEntity, CLEDEntitySpaceHashUpdater>& GetLEDEntitiesSpaceHash() {
         if(IsUsingSpaceHash()) {
            return *m_pcLEDEntitiesSpaceHash;
         }
         else {
            THROW_ARGOSEXCEPTION("Attempted to access the space hash of LED entities, but in the XML the user chose not to use it. Maybe you use a sensor or an actuator that references it directly?");
         }
      }

   protected:
      
      inline void UpdateSpaceData() {
         if(IsUsingSpaceHash()) {
            m_pcEmbodiedEntitiesSpaceHash->Update();
            m_pcLEDEntitiesSpaceHash->Update();
         }
      }
      
      virtual void UpdateControllableEntities() = 0;
      virtual void UpdatePhysics() = 0;
      
      void UpdateMediumEntities();

      void Distribute(TConfigurationNode& t_tree);

      void AddBoxStrip(TConfigurationNode& t_tree);

      bool GetClosestEmbodiedEntityIntersectedByRaySpaceHash(SEntityIntersectionItem<CEmbodiedEntity>& s_data,
                                                             const CRay& c_ray,
                                                             const TEmbodiedEntitySet& set_ignored_entities);

      bool GetClosestEmbodiedEntityIntersectedByRayEntitySweep(SEntityIntersectionItem<CEmbodiedEntity>& s_data,
                                                               const CRay& c_ray,
                                                               const TEmbodiedEntitySet& set_ignored_entities);

   };

}

#endif

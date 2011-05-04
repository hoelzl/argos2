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
 * @file <simulator/visitors/space_visitor_remove.h>
 *
 * @brief This file provides the definition of
 *
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef SPACE_VISITOR_REMOVE_H
#define SPACE_VISITOR_REMOVE_H

#include <argos2/simulator/visitors/entity_visitor.h>
#include <argos2/simulator/space/entities/box_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>
#include <argos2/simulator/space/entities/floor_entity.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>
#include <argos2/simulator/space/entities/light_entity.h>
#include <argos2/simulator/space/space.h>

#include <map>

namespace argos {

   class CSpaceVisitorRemove : public CEntityVisitor {

   public:

      CSpaceVisitorRemove(CSpace& c_space) :
         m_cSpace(c_space),
         m_tMapAllEntities(c_space.GetEntitiesMapOfMaps()) {}

      inline virtual void Visit(CBoxEntity& c_entity) {
         RemoveElement(c_entity.GetEmbodiedEntity());
         RemoveElement(c_entity.GetLEDEquippedEntity());
         RemoveElement(c_entity);
         if(m_cSpace.IsUsingSpaceHash()) {
             m_cSpace.GetEmbodiedEntitiesSpaceHash().RemoveElement(c_entity.GetEmbodiedEntity());
             CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
             for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
                m_cSpace.GetLEDEntitiesSpaceHash().RemoveElement(cLEDEntity.GetLED(i));
             }
         }
         for(UInt32 i = 0; i < c_entity.GetEmbodiedEntity().GetPhysicsEngineNum(); ++i ) {
            c_entity.GetEmbodiedEntity().GetPhysicsEngine(i).RemoveEntity(c_entity);
         }
      }

      inline virtual void Visit(CCylinderEntity& c_entity) {
         RemoveElement(c_entity.GetEmbodiedEntity());
         RemoveElement(c_entity.GetLEDEquippedEntity());
         RemoveElement(c_entity);
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().RemoveElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().RemoveElement(cLEDEntity.GetLED(i));
            }
         }
         for(UInt32 i = 0; i < c_entity.GetEmbodiedEntity().GetPhysicsEngineNum(); ++i ) {
            c_entity.GetEmbodiedEntity().GetPhysicsEngine(i).RemoveEntity(c_entity);
         }
      }

      inline virtual void Visit(CFloorEntity& c_entity) {
         RemoveElement(c_entity);
      }

      inline virtual void Visit(CFootBotEntity& c_entity) {
         RemoveElement(c_entity.GetEmbodiedEntity());
         RemoveElement(c_entity.GetControllableEntity());
         RemoveElement(c_entity.GetWheeledEntity());
         RemoveElement(c_entity.GetLEDEquippedEntity());
         RemoveElement(c_entity.GetGripperEquippedEntity());
         RemoveElement(c_entity.GetDistanceScannerEquippedEntity());
         RemoveElement(c_entity.GetRABEquippedEntity());
         RemoveElement(c_entity);
         m_cSpace.RemoveControllableEntity(c_entity.GetControllableEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().RemoveElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().RemoveElement(cLEDEntity.GetLED(i));
            }
         }
         for(UInt32 i = 0; i < c_entity.GetEmbodiedEntity().GetPhysicsEngineNum(); ++i ) {
            c_entity.GetEmbodiedEntity().GetPhysicsEngine(i).RemoveEntity(c_entity);
         }
      }

      inline virtual void Visit(CEyeBotEntity& c_entity) {
         RemoveElement(c_entity.GetEmbodiedEntity());
         RemoveElement(c_entity.GetControllableEntity());
         RemoveElement(c_entity.GetLEDEquippedEntity());
         RemoveElement(c_entity.GetDistanceScannerEquippedEntity());
         RemoveElement(c_entity.GetRABEquippedEntity());
         RemoveElement(c_entity);
         m_cSpace.RemoveControllableEntity(c_entity.GetControllableEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().RemoveElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().RemoveElement(cLEDEntity.GetLED(i));
            }
         }
         for(UInt32 i = 0; i < c_entity.GetEmbodiedEntity().GetPhysicsEngineNum(); ++i ) {
            c_entity.GetEmbodiedEntity().GetPhysicsEngine(i).RemoveEntity(c_entity);
         }
      }

      inline virtual void Visit(CLightEntity& c_entity) {
         RemoveElement(c_entity);
         RemoveElement(c_entity.GetLEDEquippedEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetLEDEntitiesSpaceHash().RemoveElement(c_entity.GetLEDEntity());
         }
      }

      inline virtual void Visit(CEPuckEntity& c_entity) {
         RemoveElement(c_entity.GetEmbodiedEntity());
         RemoveElement(c_entity.GetControllableEntity());
         RemoveElement(c_entity.GetWheeledEntity());
         RemoveElement(c_entity.GetLEDEquippedEntity());
         RemoveElement(c_entity.GetRABEquippedEntity());
         RemoveElement(c_entity);
         m_cSpace.RemoveControllableEntity(c_entity.GetControllableEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().RemoveElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().RemoveElement(cLEDEntity.GetLED(i));
            }
         }
         for(UInt32 i = 0; i < c_entity.GetEmbodiedEntity().GetPhysicsEngineNum(); ++i ) {
            c_entity.GetEmbodiedEntity().GetPhysicsEngine(i).RemoveEntity(c_entity);
         }
      }

      inline virtual void Visit(CWiFiMediumEntity& c_entity) {
         RemoveElement(c_entity);
         m_cSpace.RemoveMediumEntity(c_entity);
      }

   private:

      template <class E> void RemoveElement(E& c_entity) {
         CSpace::TMapOfAnyEntityMaps::iterator itEntitiesMap;
         itEntitiesMap = m_tMapAllEntities.find(c_entity.GetTypeDescription());
         if (itEntitiesMap != m_tMapAllEntities.end()) {
            UInt32 unErased = itEntitiesMap->second.erase(c_entity.GetId());
            if(unErased == 0) {
               THROW_ARGOSEXCEPTION("Entity <type=\"" << c_entity.GetTypeDescription() << "\",id=\"" << c_entity.GetId() << "\"> not found.");
            }
         }
         else {
            THROW_ARGOSEXCEPTION("Entity type \"" << c_entity.GetTypeDescription() << "\" not found.");
         }
      }

   private:

      CSpace& m_cSpace;
      CSpace::TMapOfAnyEntityMaps& m_tMapAllEntities;

   };

}

#endif

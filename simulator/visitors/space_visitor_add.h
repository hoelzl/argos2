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
 * @file <simulator/swarmanoid_space/visitors/space_visitor.h>
 *
 * @brief This file contains the definition of the space visitor
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 *
 */

#ifndef SPACE_VISITOR_ADD_H
#define SPACE_VISITOR_ADD_H

namespace argos {
   class CSpaceVisitorAdd;
}

#include <argos2/simulator/visitors/entity_visitor.h>
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/space/entities/controllable_entity.h>
#include <argos2/simulator/space/entities/wifi_medium_entity.h>
#include <argos2/simulator/space/entities/box_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>
#include <argos2/simulator/space/entities/floor_entity.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>
#include <argos2/simulator/space/entities/light_entity.h>
#include <argos2/simulator/space/entities/epuck_entity.h>
#include <argos2/simulator/space/space.h>

#include <map>

namespace argos {

   class CSpaceVisitorAdd : public CEntityVisitor {

   public:

      CSpaceVisitorAdd(CSpace& c_space) :
         m_cSpace(c_space),
         m_tMapAllEntities(c_space.GetEntitiesMapOfMaps()) {}

      inline virtual void Visit(CBoxEntity& c_entity) {
         AddElement(c_entity.GetEmbodiedEntity());
         AddElement(c_entity.GetLEDEquippedEntity());
         AddElement(c_entity);
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().AddElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().AddElement(cLEDEntity.GetLED(i));
            }
         }
      }

      inline virtual void Visit(CCylinderEntity& c_entity) {
         AddElement(c_entity.GetEmbodiedEntity());
         AddElement(c_entity.GetLEDEquippedEntity());
         AddElement(c_entity);
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().AddElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().AddElement(cLEDEntity.GetLED(i));
            }
         }
      }

      inline virtual void Visit(CFloorEntity& c_entity) {
         AddElement(c_entity);
         m_cSpace.SetFloorEntity(c_entity);
      }

      inline virtual void Visit(CFootBotEntity& c_entity) {
         AddElement(c_entity.GetEmbodiedEntity());
         AddElement(c_entity.GetControllableEntity());
         AddElement(c_entity.GetWheeledEntity());
         AddElement(c_entity.GetLEDEquippedEntity());
         AddElement(c_entity.GetGripperEquippedEntity());
         AddElement(c_entity.GetDistanceScannerEquippedEntity());
         AddElement(c_entity.GetRABEquippedEntity());
         AddElement(c_entity);
         m_cSpace.AddControllableEntity(c_entity.GetControllableEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().AddElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().AddElement(cLEDEntity.GetLED(i));
            }
         }
      }

      inline virtual void Visit(CEyeBotEntity& c_entity) {
         AddElement(c_entity.GetEmbodiedEntity());
         AddElement(c_entity.GetControllableEntity());
         AddElement(c_entity.GetLEDEquippedEntity());
         AddElement(c_entity.GetDistanceScannerEquippedEntity());
         AddElement(c_entity.GetRABEquippedEntity());
         AddElement(c_entity);
         m_cSpace.AddControllableEntity(c_entity.GetControllableEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().AddElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < 33; ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().AddElement(cLEDEntity.GetLED(i));
            }
         }
      }

      inline virtual void Visit(CEPuckEntity& c_entity) {
         AddElement(c_entity.GetEmbodiedEntity());
         AddElement(c_entity.GetControllableEntity());
         AddElement(c_entity.GetWheeledEntity());
         AddElement(c_entity.GetLEDEquippedEntity());
         AddElement(c_entity.GetRABEquippedEntity());
         AddElement(c_entity);
         m_cSpace.AddControllableEntity(c_entity.GetControllableEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetEmbodiedEntitiesSpaceHash().AddElement(c_entity.GetEmbodiedEntity());
            CLedEquippedEntity& cLEDEntity = c_entity.GetLEDEquippedEntity();
            for(UInt32 i = 0; i < cLEDEntity.GetAllLeds().size(); ++i) {
               m_cSpace.GetLEDEntitiesSpaceHash().AddElement(cLEDEntity.GetLED(i));
            }
         }
      }

      inline virtual void Visit(CLightEntity& c_entity) {
         AddElement(c_entity);
         AddElement(c_entity.GetLEDEquippedEntity());
         if(m_cSpace.IsUsingSpaceHash()) {
            m_cSpace.GetLEDEntitiesSpaceHash().AddElement(c_entity.GetLEDEntity());
         }
      }

      inline virtual void Visit(CWiFiMediumEntity& c_entity) {
         AddElement(c_entity);
         m_cSpace.AddMediumEntity(c_entity);
      }

   private:

      template <class E> void AddElement(E& c_entity) {
         LOG << "[INFO] Added entity <type=\""
             << c_entity.GetTypeDescription()
             << "\", id=\""
             << c_entity.GetId()
             << "\"> to space."
             << std::endl;
         m_tMapAllEntities[c_entity.GetTypeDescription()][c_entity.GetId()] = &c_entity;
      }

   private:

      CSpace& m_cSpace;
      CSpace::TMapOfAnyEntityMaps& m_tMapAllEntities;

   };

}

#endif

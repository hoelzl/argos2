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
 * @file <argos2/simulator/physics_engines/dynamics2d/dynamics2d_remove_visitor.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS2D_REMOVE_VISITOR_H
#define DYNAMICS2D_REMOVE_VISITOR_H

namespace argos {
   class CEntity;
   class CDynamics2DEngine;
}

#include <argos2/simulator/visitors/entity_visitor.h>

namespace argos {

   class CDynamics2DRemoveVisitor : public CEntityVisitor {

   public:

      CDynamics2DRemoveVisitor(CDynamics2DEngine& c_engine) :
         m_cEngine(c_engine) {}
      virtual ~CDynamics2DRemoveVisitor() {}

      virtual void Visit(CBoxEntity& c_entity);
      virtual void Visit(CCylinderEntity& c_entity);
      virtual void Visit(CFloorEntity& c_entity) {}
      virtual void Visit(CFootBotEntity& c_entity);
      virtual void Visit(CEyeBotEntity& c_entity);
      virtual void Visit(CLightEntity& c_entity) {}
      virtual void Visit(CEPuckEntity& c_entity);
      virtual void Visit(CWiFiMediumEntity& c_entity) {}

   private:

      CDynamics2DEngine& m_cEngine;
       
   };
}

#endif

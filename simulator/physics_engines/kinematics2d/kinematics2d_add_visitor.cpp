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
 * @file <argos2/simulator/physics_engines/kinematics2d/kinematics2d_add_visitor.cpp>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "kinematics2d_add_visitor.h"
#include "kinematics2d_box.h"
#include "kinematics2d_footbot.h"
#include "kinematics2d_eyebot.h"
#include "kinematics2d_engine.h"
#include <argos2/simulator/space/entities/embodied_entity.h>

namespace argos {

  /****************************************/
  /****************************************/
  
  void CKinematics2DAddVisitor::Visit(CBoxEntity& c_entity) {
    CKinematics2DBox* pcEntity = new CKinematics2DBox(m_cEngine, c_entity);
    m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
    c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
    c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
  }

  /****************************************/
  /****************************************/

  void CKinematics2DAddVisitor::Visit(CFootBotEntity& c_entity) {
    CKinematics2DFootBot* pcEntity = new CKinematics2DFootBot(m_cEngine, c_entity);
    m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
    m_cEngine.AddControllableEntity(c_entity.GetControllableEntity());
    c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
    c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
  }

  /****************************************/
  /****************************************/

  void CKinematics2DAddVisitor::Visit(CEyeBotEntity& c_entity) {
    CKinematics2DEyeBot* pcEntity = new CKinematics2DEyeBot(m_cEngine, c_entity);
    m_cEngine.AddPhysicsEntity(c_entity.GetId(), *pcEntity);
    m_cEngine.AddControllableEntity(c_entity.GetControllableEntity());
    c_entity.GetEmbodiedEntity().AddPhysicsEngine(m_cEngine);
    c_entity.GetEmbodiedEntity().AddPhysicsEngineEntity(m_cEngine.GetId(), *pcEntity);
  }

  /****************************************/
  /****************************************/

}

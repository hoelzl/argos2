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
 * @file <argos2/simulator/physics_engines/kinematics2d_box.cpp>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "kinematics2d_box.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/physics_engines/kinematics2d/kinematics2d_engine.h>

namespace argos {

  /****************************************/
  /****************************************/

  CKinematics2DBox::CKinematics2DBox(CKinematics2DEngine& c_engine, CBoxEntity& c_box) :
    CKinematics2DCollisionRectangle(c_engine, c_box.GetEmbodiedEntity(), c_box.GetSize()),
    m_cBoxEntity(c_box) {
    
    if( c_box.IsMovable() ) {
      THROW_ARGOSEXCEPTION("[ERROR] Kineamtics2D engine cannot handle movable boxes");
    }
  }
}

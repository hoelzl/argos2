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
 * @file <argos2/simulator/physics_engines/dynamics3d_cylinder.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS3D_CYLINDER_H
#define DYNAMICS3D_CYLINDER_H

namespace argos {
   class CDynamics3DEngine;
   class CDynamics3DCylinder;
}

#include <argos2/simulator/physics_engines/dynamics3d/dynamics3d_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>

namespace argos {

   class CDynamics3DCylinder : public CDynamics3DEntity {

   public:
      
      CDynamics3DCylinder(CDynamics3DEngine& c_engine,
                          CCylinderEntity& c_cylinder);
      virtual ~CDynamics3DCylinder() {}
      
      virtual void Reset();
      virtual void UpdateEntityStatus();

   private:

      CCylinderEntity& m_cCylinderEntity;
      dGeomID          m_tGeom;
   };

}

#endif

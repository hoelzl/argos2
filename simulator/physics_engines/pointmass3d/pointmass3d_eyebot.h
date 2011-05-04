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
 * @file <argos2/simulator/physics_engines/pointmass3d_eyebot.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef POINTMASS3D_EYEBOT_H
#define POINTMASS3D_EYEBOT_H

namespace argos {
   class CPointMass3DEngine;
   class CPointMass3DEyeBot;
}

#include <argos2/simulator/physics_engines/pointmass3d/pointmass3d_entity.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>

namespace argos {

   class CPointMass3DEyeBot : public CPointMass3DEntity {

   public:
      
      CPointMass3DEyeBot(CPointMass3DEngine& c_engine,
                         CEyeBotEntity& c_eyebot);
      virtual ~CPointMass3DEyeBot() {}
      
      inline virtual bool CheckIntersectionWithRay(Real& f_distance,
                                                   const CRay& c_ray) const {
         return false;
      }
      
      virtual bool MoveTo(const CVector3& c_position,
                          const CQuaternion& c_orientation,
                          bool b_check_only = false);

      virtual void Reset() {}

      virtual void UpdateEntityStatus();
      virtual void UpdateFromEntityStatus() {}

   private:

      CEyeBotEntity& m_cEyeBotEntity;
      Real           m_fArenaHeight;
      CVector3       m_cForce;
      CVector3       m_cSpeed;

   };

}

#endif

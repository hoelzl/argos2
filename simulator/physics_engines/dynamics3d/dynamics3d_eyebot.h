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
 * @file <argos2/simulator/physics_engines/dynamics3d_eyebot.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef DYNAMICS3D_EYEBOT_H
#define DYNAMICS3D_EYEBOT_H

namespace argos {
   class CDynamics3DEngine;
   class CDynamics3DEyeBot;
}

#include <argos2/simulator/physics_engines/dynamics3d/dynamics3d_entity.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>

namespace argos {

   class CDynamics3DEyeBot : public CDynamics3DEntity {

   public:
      
      CDynamics3DEyeBot(CDynamics3DEngine& c_engine,
                        CEyeBotEntity& c_eyebot);
      virtual ~CDynamics3DEyeBot() {}
      
      virtual void Reset();

      virtual void UpdateEntityStatus();
      virtual void UpdateFromEntityStatus();

   private:

      void EnableMotors();
      void DisableMotors();

   private:

      CEyeBotEntity& m_cEyeBotEntity;
      bool           m_bIsDetachedFromCeiling;
      CVector3       m_cCenterOfMass;

      dGeomID        m_tLegGeom[4];
      dGeomID        m_tRingGeom;
      dGeomID        m_tRodGeom;

      Real           m_fPreviousAltitudeError;
      Real           m_fCumulativeAltitudeError;
      CVector2       m_cPreviousOrientationError;
      CVector2       m_cCumulativeOrientationError;

      bool           m_bUsingMotors;
      dJointID       m_tLinearMotor;
      dJointID       m_tAngularMotor;
   };

}

#endif

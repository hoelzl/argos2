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
 * @file <argos2/simulator/physics_engines/dynamics3d_eyebot.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "dynamics3d_eyebot.h"
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/physics_engines/dynamics3d/dynamics3d_engine.h>

namespace argos {

   /* Values taken from Tim's 3D dynamics model in ARGoS1 */
   static const Real SURFACE_AREA     = 0.2f;
   static const Real DRAG_COEFFICIENT = 16.6f; // Drag coefficient
   static const Real AIR_DENSITY      = 1.205f; // Room Temperature

   static const Real LEG_MASS         = 0.0125f;
   static const Real RING_MASS        = 0.2f;
   static const Real ROD_MASS         = 0.25f;

   static const Real EYEBOT_HEIGHT    = 0.566;
   static const Real EYEBOT_RADIUS    = 0.25f;
   static const Real LEG_HEIGHT       = 0.166f;
   static const Real LEG_WIDTH        = 0.02f;
   static const Real LEG_DEPTH        = 0.005f;
   static const Real RING_HEIGHT      = 0.015f;
   static const Real RING_ELEVATION   = LEG_HEIGHT + RING_HEIGHT * 0.5f;
   static const Real ROD_SIDE         = 0.07f;
   static const Real ROD_HEIGHT       = 0.4f;
   static const Real ROD_ELEVATION    = RING_ELEVATION + ROD_HEIGHT * 0.5f;

   static const Real ALTITUDE_CONTROL_FORCE_PERIOD         = 5.0f;
   static const Real ALTITUDE_CONTROL_FORCE_ULTIMATE_GAIN  = 0.8f;
   static const Real ALTITUDE_CONTROL_FORCE_P              = 0.33f * ALTITUDE_CONTROL_FORCE_ULTIMATE_GAIN;
   static const Real ALTITUDE_CONTROL_FORCE_I              = 0.1f * ALTITUDE_CONTROL_FORCE_P / ALTITUDE_CONTROL_FORCE_PERIOD;
   static const Real ALTITUDE_CONTROL_FORCE_D              = ALTITUDE_CONTROL_FORCE_P * ALTITUDE_CONTROL_FORCE_PERIOD / 3.0f;
   static const Real ALTITUDE_CONTROL_FORCE_FORGET_FACTOR  = 0.75f;

   static const Real ALTITUDE_CONTROL_TORQUE_PERIOD        = 10.0f;
   static const Real ALTITUDE_CONTROL_TORQUE_ULTIMATE_GAIN = 0.01f;
   static const Real ALTITUDE_CONTROL_TORQUE_P             = 0.33f * ALTITUDE_CONTROL_TORQUE_ULTIMATE_GAIN;
   static const Real ALTITUDE_CONTROL_TORQUE_I             = 2.0f * ALTITUDE_CONTROL_TORQUE_P / ALTITUDE_CONTROL_TORQUE_PERIOD;
   static const Real ALTITUDE_CONTROL_TORQUE_D             = ALTITUDE_CONTROL_TORQUE_P * ALTITUDE_CONTROL_TORQUE_PERIOD / 3.0f;

   static const Real LINEAR_MOTOR_MAX_FORCE = 0.1f;
   static const Real ANGULAR_MOTOR_MAX_TORQUE = 0.1f;

   /****************************************/
   /****************************************/

   CDynamics3DEyeBot::CDynamics3DEyeBot(CDynamics3DEngine& c_engine,
                                        CEyeBotEntity& c_eyebot) :
      CDynamics3DEntity(c_engine, c_eyebot.GetEmbodiedEntity()),
      m_cEyeBotEntity(c_eyebot),
      m_bIsDetachedFromCeiling(true),
      m_fPreviousAltitudeError(0.0f),
      m_fCumulativeAltitudeError(0.0f),
      m_bUsingMotors(false) {
      /*
       * Set the body to its initial position and orientation
       */
      const CQuaternion& cOrient = GetEmbodiedEntity().GetOrientation();
      dQuaternion tQuat = { cOrient.GetW(), cOrient.GetX(), cOrient.GetY(), cOrient.GetZ() };
      dBodySetQuaternion(m_tBody, tQuat);
      const CVector3& cPos = GetEmbodiedEntity().GetPosition();
      dBodySetPosition(m_tBody, cPos.GetX(), cPos.GetY(), cPos.GetZ());
      /*
       * Create the component geometries and masses
       */
      /* LEGS */
      dMass tLegMass;
      dMatrix3 tLegRotation[4];
      dVector3 tLegOffset = { EYEBOT_RADIUS, 0.0f, LEG_HEIGHT * 0.5f, 1.0f };
      dVector3 tLegOffsetRot[4];
      for(UInt32 i = 0; i < 4; ++i) {
         /* Create the leg geometry */
         m_tLegGeom[i] = dCreateBox(m_tEntitySpace, LEG_WIDTH, LEG_DEPTH, LEG_HEIGHT);
         /* Create its mass */
         dMassSetBoxTotal(&tLegMass, LEG_MASS, LEG_WIDTH, LEG_DEPTH, LEG_HEIGHT);
         /* Rototranslate leg mass */
         dRFromAxisAndAngle(tLegRotation[i], 0.0f, 0.0f, 1.0f, CRadians::PI_OVER_FOUR.GetValue() + i * CRadians::PI_OVER_TWO.GetValue());
         dMULTIPLY0_331(tLegOffsetRot[i], tLegRotation[i], tLegOffset);
         dMassRotate(&tLegMass, tLegRotation[i]);
         dMassTranslate(&tLegMass, tLegOffsetRot[i][0], tLegOffsetRot[i][1], tLegOffsetRot[i][2]);
         /* Add this leg's mass to the total eye-bot mass */
         dMassAdd(&m_tMass, &tLegMass);
      }
      /* RING */
      dMass tRingMass;
      /* Create ring geometry */
      m_tRingGeom = dCreateCylinder(m_tEntitySpace, EYEBOT_RADIUS, RING_HEIGHT);
      /* Create its mass */
      dMassSetCylinderTotal(&tRingMass, RING_MASS, 3, EYEBOT_RADIUS, RING_HEIGHT);
      /* Translate the ring mass */
      dMassTranslate(&tRingMass, 0.0f, 0.0f, RING_ELEVATION);
      /* Add the ring's mass to the total eye-bot mass */
      dMassAdd(&m_tMass, &tRingMass);
      /* ROD */
      dMass tRodMass;
      /* Create rod geometry */
      m_tRodGeom = dCreateBox(m_tEntitySpace, ROD_SIDE, ROD_SIDE, ROD_HEIGHT);
      /* Create its mass */
      dMassSetBoxTotal(&tRodMass, ROD_MASS, ROD_SIDE, ROD_SIDE, ROD_HEIGHT);
      /* Translate the rod mass */
      dMassTranslate(&tRodMass, 0.0f, 0.0f, ROD_ELEVATION);
      /* Add the rod's mass to the total eye-bot mass */
      dMassAdd(&m_tMass, &tRodMass);
      /*
       * Set the component geometry offsets
       * ODE requires that the position of the rigid body corresponds to the center of mass
       * In ARGoS, the position of the eye-bot corresponds to its base (not the center of mass)
       */
      /* LEGS */
      for(UInt32 i = 0; i < 4; ++i) {
         /* Associate the leg body to the leg geom */
         dGeomSetBody(m_tLegGeom[i], m_tBody);
         /* Rototranslate leg geometry */
         dGeomSetOffsetRotation(m_tLegGeom[i], tLegRotation[i]);
         dGeomSetOffsetPosition(m_tLegGeom[i],
                                tLegOffsetRot[i][0] - m_tMass.c[0],
                                tLegOffsetRot[i][1] - m_tMass.c[1],
                                tLegOffsetRot[i][2] - m_tMass.c[2]);
      }
      /* RING */
      /* Associate the ring body to the ring geom */
      dGeomSetBody(m_tRingGeom, m_tBody);
      /* Translate the ring geometry */
      dGeomSetOffsetPosition(m_tRingGeom,
                             -m_tMass.c[0],
                             -m_tMass.c[1],
                             RING_ELEVATION - m_tMass.c[2]);
      /* ROD */
      /* Associate the rod body to the rod geom */
      dGeomSetBody(m_tRodGeom, m_tBody);
      /* Translate the rod geometry */
      dGeomSetOffsetPosition(m_tRodGeom, 0.0f, 0.0f, ROD_ELEVATION);
      /*
       * Translate the mass so that its center of mass corresponds to the local origin
       * Save the position of the center of mass to tranform the position into ARGoS
       */
      m_cCenterOfMass.Set(-m_tMass.c[0], -m_tMass.c[1], -m_tMass.c[2]);
      dMassTranslate(&m_tMass, -m_tMass.c[0], -m_tMass.c[1], -m_tMass.c[2]);
      /*
       * Set the parent body total mass
       */
      dBodySetMass(m_tBody, &m_tMass);
      /*
       * Create motors for control in speed
       * The motors connect the eye-bot body with the world
       */
      /*
       * Linear motion
       * A motor to translate the eye-bot along the local X-axis
       */
      m_tLinearMotor = dJointCreateLMotor(m_cEngine.GetWorldID(), 0);
      dJointAttach(m_tLinearMotor, m_tBody, 0);
      dJointSetLMotorNumAxes(m_tLinearMotor, 1);
      dVector3 tXAxis;
      dBodyVectorToWorld(m_tBody, 1.0f, 0.0f, 0.0f, tXAxis);
      dJointSetLMotorAxis(m_tLinearMotor, 0, 1, tXAxis[0], tXAxis[1], tXAxis[2]);
      dJointSetLMotorParam(m_tLinearMotor, dParamFMax, LINEAR_MOTOR_MAX_FORCE);
      /*
       * Angular motion
       * A motor to rotate the eye-bot around the local Z-axis
       */
      m_tAngularMotor = dJointCreateAMotor(m_cEngine.GetWorldID(), 0);
      dJointAttach(m_tAngularMotor, m_tBody, 0);
      dJointSetAMotorNumAxes(m_tAngularMotor, 1);
      dVector3 tZAxis;
      dBodyVectorToWorld(m_tBody, 0.0f, 0.0f, 1.0f, tZAxis);
      dJointSetAMotorAxis(m_tAngularMotor, 0, 1, tZAxis[0], tZAxis[1], tZAxis[2]);
      dJointSetAMotorParam(m_tAngularMotor, dParamFMax, ANGULAR_MOTOR_MAX_TORQUE);
      /* By default, the eye-bot is controlled in force */
      DisableMotors();
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEyeBot::Reset() {
      /* Reset body, forces, position, speed */
      CDynamics3DEntity::Reset();
      /* Reset eye-bot specific stuff */
      m_bIsDetachedFromCeiling = true;
      m_fPreviousAltitudeError = 0.0f;
      m_fCumulativeAltitudeError = 0.0f;
      m_cPreviousOrientationError.Set(0.0f, 0.0f);
      m_cCumulativeOrientationError.Set(0.0f, 0.0f);
      dBodyEnable(m_tBody);
      DisableMotors();
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEyeBot::UpdateFromEntityStatus() {
      /* Check whether in the last time step the eye-bot attached or detached from the ceiling */
      if(m_bIsDetachedFromCeiling != m_cEyeBotEntity.IsDetachedFromCeiling()) {
         if(m_bIsDetachedFromCeiling) {
            /* The eye-bot just detached from the ceiling, enable its body */
            m_fPreviousAltitudeError = 0.0f;
            m_fCumulativeAltitudeError = 0.0f;
            m_cPreviousOrientationError.Set(0.0f, 0.0f);
            m_cCumulativeOrientationError.Set(0.0f, 0.0f);
            dBodySetTorque(m_tBody, 0.0f, 0.0f, 0.0f);
            dBodySetForce(m_tBody, 0.0f, 0.0f, 0.0f);
            dBodyEnable(m_tBody);
            DisableMotors();
         }
         else {
            /* The eye-bot just attached to the ceiling, disable its body */
            m_fPreviousAltitudeError = 0.0f;
            m_fCumulativeAltitudeError = 0.0f;
            m_cPreviousOrientationError.Set(0.0f, 0.0f);
            m_cCumulativeOrientationError.Set(0.0f, 0.0f);
            dBodySetTorque(m_tBody, 0.0f, 0.0f, 0.0f);
            dBodySetForce(m_tBody, 0.0f, 0.0f, 0.0f);
            dBodyDisable(m_tBody);
            DisableMotors();
         }
         m_bIsDetachedFromCeiling = m_cEyeBotEntity.IsDetachedFromCeiling();
      }

      /* The eye-bot can move only when it's detached from the ceiling */
      if(m_bIsDetachedFromCeiling) {
         /* Target altitude control, if necessary */
         if(m_cEyeBotEntity.GetTargetAltitude() > 0.0f) {
            dBodyAddForce(m_tBody,
                          -m_cEngine.GetGravity().GetX() * m_tMass.mass,
                          -m_cEngine.GetGravity().GetY() * m_tMass.mass,
                          -m_cEngine.GetGravity().GetZ() * m_tMass.mass);
            /* Calculate the altitude error */
            Real fAltitudeError = m_cEyeBotEntity.GetTargetAltitude() - GetEmbodiedEntity().GetPosition().GetZ();
            m_fCumulativeAltitudeError =
               ALTITUDE_CONTROL_FORCE_FORGET_FACTOR * m_fCumulativeAltitudeError +
               fAltitudeError * m_cEngine.GetSimulationClockTick();
            /* Use a PD controller to control the altitude */
            dBodyAddForce(m_tBody, 0.0f, 0.0f,
                          ALTITUDE_CONTROL_FORCE_P * fAltitudeError +
                          ALTITUDE_CONTROL_FORCE_I * m_fCumulativeAltitudeError +
                          ALTITUDE_CONTROL_FORCE_D * (fAltitudeError-m_fPreviousAltitudeError) * m_cEngine.GetInverseSimulationClockTick());
            m_fPreviousAltitudeError = fAltitudeError;
            /*
             * Calculate the angle error
             * Here the idea is that the eye-bot's axis should be directed as the global Z axis
             * First, we find the orientation of the eye-bot axis A. If A=Z, the (x,y) coordinates
             * of A would be zero. Therefore, we take as error measures x and y.
             */
            CVector3 cEyeBotAxis = CVector3::Z;
            cEyeBotAxis.Rotate(GetEmbodiedEntity().GetOrientation());
            /*
             * The definition of torque is (where x is the cross product):
             *
             * T = R x fD
             *
             * with R = displacement vector
             *      f = force to be applied to rotate the object
             *      D = direction of the force
             *
             * for simplicity, here we express everything in the robot's local coordinates.
             * Therefore, R = Z * EYEBOT_HEIGHT. We define the coordinates of D as
             *
             * D = (force on x, force on y, 0)
             *
             * with: force on x = PD(-A.x)
             *       force on y = PD(-A.y)
             *
             * PD(error) is a PD controller that takes as input the error on one axis and
             * returns the force to be exerted on that axis.
             */
            /* Calculate the force */
            m_cCumulativeOrientationError += CVector2(cEyeBotAxis.GetX(), cEyeBotAxis.GetY());
            CVector3 cOrientationForce(
               - ALTITUDE_CONTROL_TORQUE_P * cEyeBotAxis.GetX()
               - ALTITUDE_CONTROL_TORQUE_I * m_cCumulativeOrientationError.GetX() * m_cEngine.GetSimulationClockTick()
               - ALTITUDE_CONTROL_TORQUE_D * (cEyeBotAxis.GetX() - m_cPreviousOrientationError.GetX()) * m_cEngine.GetInverseSimulationClockTick(),
               - ALTITUDE_CONTROL_TORQUE_P * cEyeBotAxis.GetY()
               - ALTITUDE_CONTROL_TORQUE_I * m_cCumulativeOrientationError.GetY() * m_cEngine.GetSimulationClockTick()
               - ALTITUDE_CONTROL_TORQUE_D * (cEyeBotAxis.GetY()-m_cPreviousOrientationError.GetY()) * m_cEngine.GetInverseSimulationClockTick(),
               0.0f);
            m_cPreviousOrientationError.Set(cEyeBotAxis.GetX(), cEyeBotAxis.GetY());
            CVector3 cOrientationTorque(CVector3::Z * EYEBOT_HEIGHT);
            cOrientationTorque.CrossProduct(cOrientationForce);
            /* Apply the torque */
            dBodyAddRelTorque(m_tBody,
                              cOrientationTorque.GetX(),
                              cOrientationTorque.GetY(),
                              cOrientationTorque.GetZ());
         }
         /* Move the eye-bot */
         if(m_cEyeBotEntity.GetMotionData().Source == CEyeBotEntity::SMotionData::MOTION_FROM_FORCES) {
            /*
             * Control the robot with forces
             */
            /* Get rid of the motors if they were previously used */
            if(m_bUsingMotors) {
               DisableMotors();
            }
            /* Zero the total force due to movement */
            CVector3 cTotalForce;
            /* Apply wanted forces */
            /* Calculate a simple air-friction model */
            dVector3 tVelocity;
            dBodyGetRelPointVel(m_tBody, 0.0f, 0.0f, 0.0f, tVelocity);
            CVector3 cVelocity(tVelocity[0], tVelocity[1], tVelocity[2]);
            if(cVelocity != CVector3::ZERO) {
               CVector3 cFriction(cVelocity);
               cFriction.Normalize().Negate();
               Real fFrictionMag =
                  cVelocity.SquareLength() *
                  SURFACE_AREA *
                  AIR_DENSITY *
                  DRAG_COEFFICIENT *
                  m_tMass.mass;
               Real fMaxFrictionMag = cVelocity.Length() * m_tMass.mass / m_cEngine.GetSimulationClockTick();
               if(fFrictionMag > fMaxFrictionMag) {
                  fFrictionMag = fMaxFrictionMag;
               }
               cFriction *= fFrictionMag;
               /* Add friction to the total forces */
               cTotalForce += cFriction;
            }
            /* Add to the force the wanted forces */
            CVector3 cEyebotForce(m_cEyeBotEntity.GetMotionData().ForceX,
                                  - m_cEyeBotEntity.GetMotionData().ForceY,
                                  m_cEyeBotEntity.GetMotionData().ForceZ);
            cEyebotForce.Rotate(m_cEyeBotEntity.GetEmbodiedEntity().GetOrientation());
            cTotalForce += cEyebotForce;
            /* Add the total force to the ODE body */
            dBodyAddRelForce(m_tBody, cTotalForce.GetX(), cTotalForce.GetY(), cTotalForce.GetZ());
         }
         else {
            /*
             * Control the robot with speeds
             */
            /* Enable the motors if they weren't previously used */
            if(! m_bUsingMotors) {
               EnableMotors();
            }
            /* Linear speed along local X */
            dJointSetLMotorParam(m_tLinearMotor, dParamVel, m_cEyeBotEntity.GetMotionData().LinearSpeed);
            /* Angular speed along local Z */
            dJointSetAMotorParam(m_tAngularMotor, dParamVel, m_cEyeBotEntity.GetMotionData().AngularSpeed);
         }
      }
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEyeBot::UpdateEntityStatus() {
      /* Update eye-bot position and orientation */
      dVector3 ptPosition;
      dBodyGetRelPointPos(m_tBody,
                          m_cCenterOfMass.GetX(),
                          m_cCenterOfMass.GetY(),
                          m_cCenterOfMass.GetZ(),
                          ptPosition);
      GetEmbodiedEntity().SetPosition(
         CVector3(ptPosition[0],
                  ptPosition[1],
                  ptPosition[2]));
      const dReal* ptOrientation = dBodyGetQuaternion(m_tBody);
      GetEmbodiedEntity().SetOrientation(
         CQuaternion(ptOrientation[0],
                     ptOrientation[1],
                     ptOrientation[2],
                     ptOrientation[3]));
      /* Update the components */
      m_cEyeBotEntity.UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEyeBot::EnableMotors() {
      dJointEnable(m_tLinearMotor);
      dJointEnable(m_tAngularMotor);
      m_bUsingMotors = true;
   }

   /****************************************/
   /****************************************/

   void CDynamics3DEyeBot::DisableMotors() {
      dJointDisable(m_tLinearMotor);
      dJointDisable(m_tAngularMotor);
      m_bUsingMotors = false;
   }

   /****************************************/
   /****************************************/

}

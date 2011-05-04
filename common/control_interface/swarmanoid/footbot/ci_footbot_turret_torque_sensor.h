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
 * @file <common/control_interface/footbot/ci_footbot_turret_torque_sensor.h>
 *
 * @brief This file provides the common interface definition of the footbot turret torque
 * sensor. The sensor provides measures of the torque and traction applied to the turret.
 *
 * The traction can be retrieved in XY form (a vector containing X and Y components)
 * or in polar form (force and angle).
 *
 * When expressed in X-Y form the convention is the following:
 *
 *
 *        front
 *
 *          ^ X
 *          |
 *          |
 * Y <------|
 *
 *        back
 *
 * Values of the X and Y components are in [-1,1].
 *
 * When expressed in the polar form, the force has to be considered as a traction (pulling) force.
 * The point at which it is applied is determined by its angle: counter-clockwise positive when looking from
 * above, values are expressed in radians and are in the interval [-pi,pi].
 * The magnitude of the force is in [0,1]
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_FOOTBOT_TURRET_TORQUE_SENSOR_H
#define CCI_FOOTBOT_TURRET_TORQUE_SENSOR_H

namespace argos {
   class CCI_FootBotTurretTorqueSensor;
}

#include <argos2/common/control_interface/ci_sensor.h>
#include <argos2/common/utility/math/vector2.h>

namespace argos {

   class CCI_FootBotTurretTorqueSensor : public CCI_Sensor {

   public:

      struct SReading {
         Real EngineTorque;
         CVector2 TractionXY;

         struct STractionPolar {
            Real Force;
            CRadians Angle;

            STractionPolar() :
               Force(0.0) {
            }

            STractionPolar(Real f_force, const CRadians& c_angle) :
               Force(f_force), Angle(c_angle) {
            }

         } TractionPolar;

         SReading() :
            EngineTorque(0.0) {
         }

         SReading(Real f_engine_torque,
                  const CVector2& c_traction_xy,
                  Real f_force,
                  const CRadians& c_angle) :
            EngineTorque(f_engine_torque), TractionXY(c_traction_xy),
            TractionPolar(f_force, c_angle) {
         }
      };

      virtual ~CCI_FootBotTurretTorqueSensor() {
      }

      inline virtual const SReading& GetReading() const {
         return m_sReading;
      }

   protected:

      SReading m_sReading;

      /** Define ranges for forces, torques, angles and normalized ranges */
      static const CRange<Real>     FOOTBOT_TURRET_RAW_FORCEXY_RANGE;
      static const CRange<Real>     FOOTBOT_TURRET_NORMALIZED_FORCEXY_RANGE;
      static const CRange<Real>     FOOTBOT_TURRET_RAW_POLAR_RANGE;
      static const CRange<Real>     FOOTBOT_TURRET_NORMALIZED_POLAR_RANGE;
      static const CRange<Real>     FOOTBOT_TURRET_RAW_FORCE_TORQUE_RANGE;
      static const CRange<Real>     FOOTBOT_TURRET_NORMALIZED_TORQUE_RANGE;
      static const CRange<CRadians> FOOTBOT_TURRET_ANGULAR_RANGE;

   };

}

#endif

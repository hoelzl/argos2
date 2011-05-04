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
 * @file <argos2/common/utility/math/matrix3x3.cpp>
 *
 * The matrix goes like this:
 *
 * | 0 1 2 |
 * | 3 4 5 |
 * | 6 7 8 |
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "matrix3x3.h"
#include "vector3.h"
#include "quaternion.h"

namespace argos {

   /****************************************/
   /****************************************/

   CMatrix3x3 CMatrix3x3::IDENTITY;

   /****************************************/
   /****************************************/

   CVector3 CMatrix3x3::operator[](UInt32 un_row) const {
      ARGOS_ASSERT(un_row < 3,
                   "Matrix index out of bounds: un_row = " <<
                   un_row);
      UInt32 unRowBase = un_row * 3;
      return CVector3(m_fValues[unRowBase    ],
                      m_fValues[unRowBase + 1],
                      m_fValues[unRowBase + 2]);
   }

   /****************************************/
   /****************************************/

   CMatrix3x3& CMatrix3x3::FromQuaternion(const CQuaternion& c_quaternion) {
      /* This code is adapted from the Bullet source code */
      Real d = c_quaternion.SquareLength();
      Real s = 2.0f / d;
      Real xs = c_quaternion.GetX() * s,   ys = c_quaternion.GetY() * s,   zs = c_quaternion.GetZ() * s;
      Real wx = c_quaternion.GetW() * xs,  wy = c_quaternion.GetW() * ys,  wz = c_quaternion.GetW() * zs;
      Real xx = c_quaternion.GetX() * xs,  xy = c_quaternion.GetX() * ys,  xz = c_quaternion.GetX() * zs;
      Real yy = c_quaternion.GetY() * ys,  yz = c_quaternion.GetY() * zs,  zz = c_quaternion.GetZ() * zs;
      /* Set values */
      m_fValues[0] = 1.0f - (yy + zz);
      m_fValues[1] = xy - wz;
      m_fValues[2] = xz + wy;
      m_fValues[3] = xy + wz;
      m_fValues[4] = 1.0f - (xx + zz);
      m_fValues[5] = yz - wx;
      m_fValues[6] = xz - wy;
      m_fValues[7] = yz + wx;
      m_fValues[8] = 1.0f - (xx + yy);
      return *this;
   }

   /****************************************/
   /****************************************/

}

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
 * @file <argos2/common/utility/math/matrix3x3.h>
 *
 * The matrix goes like this:
 *
 * | 0 1 2 |
 * | 3 4 5 |
 * | 6 7 8 |
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef MATRIX3X3_H
#define MATRIX3X3_H

namespace argos {
   class CMatrix3x3;
   class CQuaternion;
   class CVector3;
}

#include <argos2/common/utility/math/general.h>
#include <argos2/common/utility/math/angles.h>
#include <cmath>

namespace argos {

   class CMatrix3x3 {

   public:

      static CMatrix3x3 IDENTITY;

   public:

      CMatrix3x3() {
         m_fValues[0] = 1.0f; m_fValues[1] = 0.0f; m_fValues[2] = 0.0f;
         m_fValues[3] = 0.0f; m_fValues[4] = 1.0f; m_fValues[5] = 0.0f;
         m_fValues[6] = 0.0f; m_fValues[7] = 0.0f; m_fValues[8] = 1.0f;
      }

      CMatrix3x3(const Real* f_values) {
         Set(f_values);
      }

      CMatrix3x3(const Real& f_value0, const Real& f_value1, const Real& f_value2,
                 const Real& f_value3, const Real& f_value4, const Real& f_value5,
                 const Real& f_value6, const Real& f_value7, const Real& f_value8) {
         Set(f_value0, f_value1, f_value2,
             f_value3, f_value4, f_value5,
             f_value6, f_value7, f_value8);
      }

      CMatrix3x3(const CQuaternion& c_quaternion) {
         FromQuaternion(c_quaternion);
      }

      CMatrix3x3(const CMatrix3x3& c_matrix) {
         Set(c_matrix.m_fValues);
      }

      CMatrix3x3& operator=(const CMatrix3x3& c_matrix) {
         if(this != &c_matrix) {
            Set(c_matrix.m_fValues);
         }
         return *this;
      }

      inline void Set(const Real* f_values) {
         m_fValues[0] = f_values[0]; m_fValues[1] = f_values[1]; m_fValues[2] = f_values[2];
         m_fValues[3] = f_values[3]; m_fValues[4] = f_values[4]; m_fValues[5] = f_values[5];
         m_fValues[6] = f_values[6]; m_fValues[7] = f_values[7]; m_fValues[8] = f_values[8];
      }

      inline void Set(const Real& f_value0, const Real& f_value1, const Real& f_value2,
                      const Real& f_value3, const Real& f_value4, const Real& f_value5,
                      const Real& f_value6, const Real& f_value7, const Real& f_value8) {
         m_fValues[0] = f_value0; m_fValues[1] = f_value1; m_fValues[2] = f_value2;
         m_fValues[3] = f_value3; m_fValues[4] = f_value4; m_fValues[5] = f_value5;
         m_fValues[6] = f_value6; m_fValues[7] = f_value7; m_fValues[8] = f_value8;
      }

      inline Real operator()(UInt32 un_row,
                             UInt32 un_col) const {
         ARGOS_ASSERT(un_row < 3 && un_col < 3,
                      "Matrix index out of bounds: un_row = " <<
                      un_row <<
                      ", un_col = " <<
                      un_col);
         return m_fValues[un_row * 3 + un_col];
      }

      inline Real& operator()(UInt32 un_row,
                              UInt32 un_col) {
         ARGOS_ASSERT(un_row < 3 && un_col < 3,
                      "Matrix index out of bounds: un_row = " <<
                      un_row <<
                      ", un_col = " <<
                      un_col);
         return m_fValues[un_row * 3 + un_col];
      }

      inline Real operator()(UInt32 un_idx) const {
         ARGOS_ASSERT(un_idx < 9,
                      "Matrix index out of bounds: un_idx = " <<
                      un_idx);
         return m_fValues[un_idx];
      }

      inline Real& operator()(UInt32 un_idx) {
         ARGOS_ASSERT(un_idx < 9,
                      "Matrix index out of bounds: un_idx = " <<
                      un_idx);
         return m_fValues[un_idx];
      }

      CVector3 operator[](UInt32 un_row) const;

      CMatrix3x3& FromQuaternion(const CQuaternion& c_quaternion);

      inline bool operator==(const CMatrix3x3& c_matrix) const {
         return
            m_fValues[0] == c_matrix.m_fValues[0] &&
            m_fValues[1] == c_matrix.m_fValues[1] &&
            m_fValues[2] == c_matrix.m_fValues[2] &&
            m_fValues[3] == c_matrix.m_fValues[3] &&
            m_fValues[4] == c_matrix.m_fValues[4] &&
            m_fValues[5] == c_matrix.m_fValues[5] &&
            m_fValues[6] == c_matrix.m_fValues[6] &&
            m_fValues[7] == c_matrix.m_fValues[7] &&
            m_fValues[8] == c_matrix.m_fValues[8];
      }

      inline CMatrix3x3& operator+=(const CMatrix3x3& c_matrix) {
         m_fValues[0] += c_matrix.m_fValues[0];
         m_fValues[1] += c_matrix.m_fValues[1];
         m_fValues[2] += c_matrix.m_fValues[2];
         m_fValues[3] += c_matrix.m_fValues[3];
         m_fValues[4] += c_matrix.m_fValues[4];
         m_fValues[5] += c_matrix.m_fValues[5];
         m_fValues[6] += c_matrix.m_fValues[6];
         m_fValues[7] += c_matrix.m_fValues[7];
         m_fValues[8] += c_matrix.m_fValues[8];
         return *this;
      }

      inline CMatrix3x3& operator-=(const CMatrix3x3& c_matrix) {
         m_fValues[0] -= c_matrix.m_fValues[0];
         m_fValues[1] -= c_matrix.m_fValues[1];
         m_fValues[2] -= c_matrix.m_fValues[2];
         m_fValues[3] -= c_matrix.m_fValues[3];
         m_fValues[4] -= c_matrix.m_fValues[4];
         m_fValues[5] -= c_matrix.m_fValues[5];
         m_fValues[6] -= c_matrix.m_fValues[6];
         m_fValues[7] -= c_matrix.m_fValues[7];
         m_fValues[8] -= c_matrix.m_fValues[8];
         return *this;
      }

      inline CMatrix3x3& operator*=(const CMatrix3x3& c_matrix) {
         Real fNewValues[9];
         /* Calculate new values */
         fNewValues[0] =
            m_fValues[0] * c_matrix.m_fValues[0] + 
            m_fValues[1] * c_matrix.m_fValues[3] + 
            m_fValues[2] * c_matrix.m_fValues[6];
         fNewValues[1] =
            m_fValues[0] * c_matrix.m_fValues[1] + 
            m_fValues[1] * c_matrix.m_fValues[4] + 
            m_fValues[2] * c_matrix.m_fValues[7];
         fNewValues[2] =
            m_fValues[0] * c_matrix.m_fValues[2] + 
            m_fValues[1] * c_matrix.m_fValues[5] + 
            m_fValues[2] * c_matrix.m_fValues[8];
         fNewValues[3] =
            m_fValues[3] * c_matrix.m_fValues[0] + 
            m_fValues[4] * c_matrix.m_fValues[3] + 
            m_fValues[5] * c_matrix.m_fValues[6];
         fNewValues[4] =
            m_fValues[3] * c_matrix.m_fValues[1] + 
            m_fValues[4] * c_matrix.m_fValues[4] + 
            m_fValues[5] * c_matrix.m_fValues[7];
         fNewValues[5] =
            m_fValues[3] * c_matrix.m_fValues[2] + 
            m_fValues[4] * c_matrix.m_fValues[5] + 
            m_fValues[5] * c_matrix.m_fValues[8];
         fNewValues[6] =
            m_fValues[6] * c_matrix.m_fValues[0] + 
            m_fValues[7] * c_matrix.m_fValues[3] + 
            m_fValues[8] * c_matrix.m_fValues[6];
         fNewValues[7] =
            m_fValues[6] * c_matrix.m_fValues[1] + 
            m_fValues[7] * c_matrix.m_fValues[4] + 
            m_fValues[8] * c_matrix.m_fValues[7];
         fNewValues[8] =
            m_fValues[6] * c_matrix.m_fValues[2] + 
            m_fValues[7] * c_matrix.m_fValues[5] + 
            m_fValues[8] * c_matrix.m_fValues[8];
         /* Copy them into m_fValues */
         Set(fNewValues);
         return *this;
      }

      inline CMatrix3x3& operator*=(Real f_scale) {
         m_fValues[0] *= f_scale;
         m_fValues[1] *= f_scale;
         m_fValues[2] *= f_scale;
         m_fValues[3] *= f_scale;
         m_fValues[4] *= f_scale;
         m_fValues[5] *= f_scale;
         m_fValues[6] *= f_scale;
         m_fValues[7] *= f_scale;
         m_fValues[8] *= f_scale;
         return *this;
      }

      inline CMatrix3x3 operator+(const CMatrix3x3& c_matrix) const {
         CMatrix3x3 cResult = (*this);
         cResult += c_matrix;
         return cResult;
      }

      inline CMatrix3x3 operator-(const CMatrix3x3& c_matrix) const {
         CMatrix3x3 cResult = (*this);
         cResult -= c_matrix;
         return cResult;
      }

      inline CMatrix3x3 operator*(const CMatrix3x3& c_matrix) const {
         CMatrix3x3 cResult = (*this);
         cResult *= c_matrix;
         return cResult;
      }

      inline CMatrix3x3 operator*(Real f_scale) const {
         CMatrix3x3 cResult = (*this);
         cResult *= f_scale;
         return cResult;
      }

      friend std::ostream& operator<<(std::ostream& c_os,
                                      const CMatrix3x3& c_matrix) {
         c_os << "| " << c_matrix(0) << " " << c_matrix(1) << " " << c_matrix(2) << " |" << "<br>"
              << "| " << c_matrix(3) << " " << c_matrix(4) << " " << c_matrix(5) << " |" << "<br>"
              << "| " << c_matrix(6) << " " << c_matrix(7) << " " << c_matrix(8) << " |" << "<br>";
         return c_os;
      }

   private:

      Real m_fValues[9];

   };

}

#endif

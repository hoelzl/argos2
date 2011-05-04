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
 * @file <common/utility/math/shapes2/primitive2.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CIRCLE_H
#define CIRCLE_H

namespace argos {
   class CCircle;
}

#include <argos2/common/utility/math/shapes2/primitive2.h>

namespace argos {

   class CCircle : public CPrimitive2 {

   public:

      CCircle(Real f_radius) :
         m_fRadius(f_radius) {}

      CCircle(const CVector2& c_center,
              Real f_radius) :
         CPrimitive2(c_center, CRadians()),
         m_fRadius(f_radius) {}

      virtual ~CCircle() {}

      inline Real GetRadius() const {
         return m_fRadius;
      }

      inline void SetRadius(Real f_radius) {
         m_fRadius = f_radius;
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CRectangle& c_rectangle) {
         ComputeIntersection(s_intersection_data2, c_rectangle, *this);
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCircle& c_circle) {
         ComputeIntersection(s_intersection_data2, *this, c_circle);
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCompound& c_compound) {
         ComputeIntersection(s_intersection_data2, *this, c_compound);
      }

      inline CVector2 Normal(const CVector2& c_point) const {
         return (m_cCenter - c_point) / m_fRadius;
      }

      inline virtual void Gnuplot() {
         std::cout << "set parametric" << std::endl;
         std::cout << "plot "
                   << m_cCenter.GetX() << "+"
                   << m_fRadius << "*sin(t),"
                   << m_cCenter.GetY() << "+"
                   << m_fRadius << "*cos(t)" << std::endl;
         std::cout << "unset parametric" << std::endl;
      }

   protected:

      Real m_fRadius;

   };

}

#endif

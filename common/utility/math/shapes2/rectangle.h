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

#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace argos {
   class CRectangle;
}

#include <argos2/common/utility/math/shapes2/primitive2.h>

namespace argos {

   class CRectangle : public CPrimitive2 {

   public:

      CRectangle(Real f_width,
                 Real f_height) :
         m_fWidth(f_width),
         m_fHeight(f_height),
         m_fHalfWidth(f_width * 0.5),
         m_fHalfHeight(f_height * 0.5),
         m_cBottomLeftCorner(-m_fHalfWidth,-m_fHalfHeight),
         m_cBottomRightCorner(m_fHalfWidth,-m_fHalfHeight),
         m_cTopRightCorner(m_fHalfWidth,m_fHalfHeight),
         m_cTopLeftCorner(-m_fHalfWidth,m_fHalfHeight) {}

      CRectangle(const CVector2& c_center,
                 const CRadians& c_orientation,
                 Real f_width,
                 Real f_height) :
         CPrimitive2(c_center, c_orientation),
         m_fWidth(f_width),
         m_fHeight(f_height),
         m_fHalfWidth(f_width * 0.5),
         m_fHalfHeight(f_height * 0.5) {
         CalculateCorners();
      }

      virtual ~CRectangle() {}

      void SetCenter(const CVector2& c_center) {
    	  m_cCenter = c_center;
          CalculateCorners();
       }

      inline Real GetWidth() const {
         return m_fWidth;
      }

      inline Real GetHalfWidth() const {
         return m_fHalfWidth;
      }

      inline void SetWidth(Real f_width) {
         m_fWidth = f_width;
         m_fHalfWidth = f_width * 0.5;
         CalculateCorners();
      }

      inline Real GetHeight() const {
         return m_fHeight;
      }

      inline Real GetHalfHeight() const {
         return m_fHalfHeight;
      }

      inline void SetHeight(Real f_height) {
         m_fHeight = f_height;
         m_fHalfHeight = f_height * 0.5;
         CalculateCorners();
      }

      inline void SetSize(Real f_width, Real f_height) {
         m_fWidth = f_width;
         m_fHeight = f_height;
         m_fHalfWidth = f_width * 0.5;
         m_fHalfHeight = f_height * 0.5;
         CalculateCorners();
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CRectangle& c_rectangle) {
         ComputeIntersection(s_intersection_data2, *this, c_rectangle);
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCircle& c_circle) {
         ComputeIntersection(s_intersection_data2, *this, c_circle);
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCompound& c_compound) {
         ComputeIntersection(s_intersection_data2, *this, c_compound);
      }

      inline CVector2 Normal(const CVector2& c_point) const {
         // TODO: implement this
         return CVector2();
      }
      
      virtual void Translate(const CVector2& c_translation) {
         CPrimitive2::Translate(c_translation);
         m_cBottomLeftCorner += c_translation;
         m_cBottomRightCorner += c_translation;
         m_cTopRightCorner += c_translation;
         m_cTopLeftCorner += c_translation;
      }

      virtual void Rotate(const CRadians& c_rotation) {
         CPrimitive2::Rotate(c_rotation);
         CalculateCorners();
      }
      
#define GNUPLOT_DRAW_RECTANGLE_SIDE(STARTCORNER,ENDCORNER)              \
      std::cout << "plot [0:1] "                                        \
      << STARTCORNER.GetX() << "+t*"                                    \
      << ENDCORNER.GetX() - STARTCORNER.GetX() << ","                   \
      << STARTCORNER.GetY() << "+t*"                                    \
      << ENDCORNER.GetY() - STARTCORNER.GetY()                          \
      << std::endl;
      
      inline virtual void Gnuplot() {
         std::cout << "set parametric" << std::endl;
         GNUPLOT_DRAW_RECTANGLE_SIDE(m_cBottomLeftCorner,m_cTopLeftCorner);
         GNUPLOT_DRAW_RECTANGLE_SIDE(m_cBottomLeftCorner,m_cBottomRightCorner);
         GNUPLOT_DRAW_RECTANGLE_SIDE(m_cTopRightCorner,m_cTopLeftCorner);
         GNUPLOT_DRAW_RECTANGLE_SIDE(m_cTopRightCorner,m_cBottomRightCorner);
         std::cout << "unset parametric" << std::endl;
      }

   protected:

      inline void CalculateCorners() {
         /* Put the rectangle back in the origin and apply full rotation */
         /* Take the two right corners */
         m_cTopRightCorner.Set(m_fHalfWidth,m_fHalfHeight);
         m_cBottomRightCorner.Set(m_fHalfWidth,-m_fHalfHeight);
         /* Rotate them */
         m_cTopRightCorner.Rotate(m_cOrientation);
         m_cBottomRightCorner.Rotate(m_cOrientation);
         /* Derive the two opposite corners */
         m_cTopLeftCorner = -m_cBottomRightCorner;
         m_cBottomLeftCorner = -m_cTopRightCorner;
         /* Translate the corners back in position */
         m_cBottomLeftCorner += m_cCenter;
         m_cBottomRightCorner += m_cCenter;
         m_cTopRightCorner += m_cCenter;
         m_cTopLeftCorner += m_cCenter;
      }

   protected:

      Real m_fWidth;
      Real m_fHeight;
      Real m_fHalfWidth;
      Real m_fHalfHeight;
      CVector2 m_cBottomLeftCorner;
      CVector2 m_cBottomRightCorner;
      CVector2 m_cTopRightCorner;
      CVector2 m_cTopLeftCorner;

   };

}

#endif

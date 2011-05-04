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

#ifndef PRIMITIVE2_H
#define PRIMITIVE2_H

namespace argos {
   class CPrimitive2;
   class CRectangle;
   class CCircle;
   class CCompound;
   struct SIntersectionData2;
}

#include <argos2/common/utility/math/vector2.h>

namespace argos {

   /****************************************/
   /****************************************/

#define TRACK(theline) { std::cerr << "[DEBUG] " #theline << std::endl; } theline
#define DISPLAY(thevar) std::cerr << "[DEBUG] " #thevar << " = " << (thevar) << std::endl;

   /****************************************/
   /****************************************/

   struct SIntersectionData2 {
      bool Intersection;             // whether or not there is an intersection
      bool ComputePointsAndNormals;  // whether or not to compute points and normals
      std::vector<CVector2> Points;  // the intersection points
      std::vector<CVector2> Normals; // the normals in the intersection points

      SIntersectionData2() :
         Intersection(false),
         ComputePointsAndNormals(false) {}

      SIntersectionData2(const std::vector<CVector2>& vec_points,
                         const std::vector<CVector2>& vec_normals) :
         Intersection(true),
         ComputePointsAndNormals(true),
         Points(vec_points),
         Normals(vec_normals) {}

      void Gnuplot() {}
      
      friend std::ostream& operator<<(std::ostream& c_os,
                                      const SIntersectionData2& s_intersection_data2) {
         c_os << "{" << s_intersection_data2.Intersection << ",[";
         if(!s_intersection_data2.Points.empty()) {
            c_os << s_intersection_data2.Points[0];
            for(UInt32 i = 1; i < s_intersection_data2.Points.size(); i++) {
               c_os << "," << s_intersection_data2.Points[i];
            }
         }
         c_os << "],[";
         if(!s_intersection_data2.Normals.empty()) {
            c_os << s_intersection_data2.Normals[0];
            for(UInt32 i = 1; i < s_intersection_data2.Normals.size(); i++) {
               c_os << "," << s_intersection_data2.Normals[i];
            }
         }
         c_os << "]}";
         return c_os;
      }
   };

   /****************************************/
   /****************************************/

   class CPrimitive2 {

   public:

      CPrimitive2() :
         m_bEnabled(true) {}

      CPrimitive2(const CVector2& c_center,
                  const CRadians& c_orientation) :
         m_bEnabled(true),
         m_cCenter(c_center),
         m_cOrientation(c_orientation) {}

      virtual ~CPrimitive2() {}

      inline bool IsEnabled() const {
         return m_bEnabled;
      }

      inline void SetEnabled(bool b_enabled) {
         m_bEnabled = b_enabled;
      }

      const CVector2& GetCenter() const {
         return m_cCenter;
      }

      virtual void SetCenter(const CVector2& c_center) {
    	 m_cCenter = c_center;
      }

      const CRadians& GetOrientation() const {
         return m_cOrientation;
      }

      void SetOrientation(const CRadians& c_orientation) {
         m_cOrientation = c_orientation;
      }

      virtual void Intersects(SIntersectionData2& s_intersection_data2, const CRectangle& c_rectangle) = 0;
      virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCircle& c_circle) = 0;
      virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCompound& c_compound) = 0;

      virtual void Translate(const CVector2& c_translation) {
         m_cCenter += c_translation;
      }

      virtual void Rotate(const CRadians& c_rotation) {
         m_cOrientation += c_rotation;
      }

      virtual CVector2 Normal(const CVector2& c_point) const = 0;

      virtual void Gnuplot() = 0;
      
   protected:

      bool m_bEnabled;
      CVector2 m_cCenter;
      CRadians m_cOrientation;

   };

   /****************************************/
   /****************************************/

   void ComputeIntersection(SIntersectionData2& s_intersection_data2, const CRectangle& c_rectangle1, const CRectangle& c_rectangle2);
   void ComputeIntersection(SIntersectionData2& s_intersection_data2, const CRectangle& c_rectangle, const CCircle& c_circle);
   void ComputeIntersection(SIntersectionData2& s_intersection_data2, const CRectangle& c_rectangle, const CCompound& c_compound);
   void ComputeIntersection(SIntersectionData2& s_intersection_data2, const CCircle& c_circle1, const CCircle& c_circle2);
   void ComputeIntersection(SIntersectionData2& s_intersection_data2, const CCircle& c_circle, const CCompound& c_compound);
   void ComputeIntersection(SIntersectionData2& s_intersection_data2, const CCompound& c_compound1, const CCompound& c_compound2);

   /****************************************/
   /****************************************/

}

#endif

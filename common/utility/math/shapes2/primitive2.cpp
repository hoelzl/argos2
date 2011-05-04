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

#include "primitive2.h"
#include "rectangle.h"
#include "circle.h"
#include "compound.h"
#include <argos2/common/utility/math/general.h>

namespace argos {

	typedef std::vector<CPrimitive2*> TChildren;
	typedef std::vector<CPrimitive2*>::iterator TIteratorChildren;

   /****************************************/
   /****************************************/

#define RectangleVertexInside( v, xmin, xmax, ymin, ymax ) ( v.GetX() >= (xmin) && v.GetX() <= (xmax) && v.GetY() >= (ymin) && v.GetY() <= (ymax) )

   void ComputeIntersection(SIntersectionData2& s_intersection_data2,
                            const CRectangle& c_rectangle1,
                            const CRectangle& c_rectangle2) {

      CVector2 cRect1Center(c_rectangle1.GetCenter());
      CVector2 cRect2Center(c_rectangle2.GetCenter());
      CRadians cRect1Orientation(c_rectangle1.GetOrientation());

      /* Rotate the plane so that rectangle 2 is axis aligned */
      cRect1Center.Rotate(-c_rectangle2.GetOrientation());
      cRect2Center.Rotate(-c_rectangle2.GetOrientation());
      cRect1Orientation -= c_rectangle2.GetOrientation();


      /* Translate the plane so that rectangle 1 is centered in O */
      cRect2Center -= cRect1Center;

      if(cRect1Orientation == CRadians::ZERO) {
         /* Rectangle 1 is not rotated, avoid useless computation and make the simple check */
         if(c_rectangle1.GetHalfWidth() < ::fabs (cRect2Center.GetX()) - c_rectangle2.GetHalfWidth()) {
            /* Rectangle 1 left, Rectangle 2 right or viceversa */
            s_intersection_data2.Intersection = false;
         }
         else if(c_rectangle1.GetHalfHeight() < ::fabs ( cRect2Center.GetY()) - c_rectangle2.GetHalfHeight()) {
            /* Rectangle 1 top, Rectangle 2 bottom or viceversa */
            s_intersection_data2.Intersection = false;
         }
         else {
            /* Collision! */
            s_intersection_data2.Intersection = true;
         }
      }
      else {
         /* Rectangle 1 is rotated */
         /* Find the vertexes of rectangle 1 */
         CVector2 cRect1TR(c_rectangle1.GetHalfWidth(), c_rectangle1.GetHalfHeight());
         CVector2 cRect1BR(c_rectangle1.GetHalfWidth(), -c_rectangle1.GetHalfHeight());
         cRect1TR.Rotate(cRect1Orientation);
         cRect1BR.Rotate(cRect1Orientation);
         CVector2 cRect1TL(-cRect1BR);
         CVector2 cRect1BL(-cRect1TR);
         
         /* Check if they are inside rectangle 2 */
         Real fDX1  = cRect2Center.GetX() - c_rectangle2.GetHalfWidth();
         Real fDX2  = cRect2Center.GetX() + c_rectangle2.GetHalfWidth();
         Real fDY1  = cRect2Center.GetY() - c_rectangle2.GetHalfHeight();
         Real fDY2  = cRect2Center.GetY() + c_rectangle2.GetHalfHeight();
         Real fXMin = Min(fDX1, fDX2);
         Real fXMax = Max(fDX1, fDX2);
         Real fYMin = Min(fDY1, fDY2);
         Real fYMax = Max(fDY1, fDY2);
         
         s_intersection_data2.Intersection = 
            (RectangleVertexInside(cRect1TR, fXMin, fXMax, fYMin, fYMax) ||
             RectangleVertexInside(cRect1BR, fXMin, fXMax, fYMin, fYMax) ||
             RectangleVertexInside(cRect1TL, fXMin, fXMax, fYMin, fYMax) ||
             RectangleVertexInside(cRect1BL, fXMin, fXMax, fYMin, fYMax));
      }
      
   }

   /****************************************/
   /****************************************/

   void ComputeIntersection(SIntersectionData2& s_intersection_data2,
                            const CRectangle& c_rectangle,
                            const CCircle& c_circle) {
      /* if both objects are enabled, go on checking */
      if(c_rectangle.IsEnabled() && c_circle.IsEnabled()) {
         /* both circles are enabled */
         CVector2 cCircleCenter(c_circle.GetCenter());
         
         /* Rototranslate the plane so that the rectangle is axis aligned and centered in O */
         cCircleCenter -= c_rectangle.GetCenter();
         cCircleCenter.Rotate(-c_rectangle.GetOrientation());
         
         /* Find the Voronoi Region where the circle is, exploiting the symmetries */
         // TODO: unused variable
         //Real fHalfHeight = c_rectangle.GetHeight() * 0.5;
         cCircleCenter.Set(::fabs(cCircleCenter.GetX()), ::fabs(cCircleCenter.GetY()));
         
         if(cCircleCenter.GetX() <= c_rectangle.GetHalfWidth()) {
            /* The circle is in the top or bottom region */
            s_intersection_data2.Intersection = (cCircleCenter.GetY() <= c_rectangle.GetHalfHeight() + c_circle.GetRadius());
         }
         else if(cCircleCenter.GetY() <= c_rectangle.GetHalfHeight()) {
            /* The circle is in the left or right region */
            s_intersection_data2.Intersection = (cCircleCenter.GetX() <= c_rectangle.GetHalfWidth() + c_circle.GetRadius());
         }
         else {
            /* The circle is in one of the four corner regions */
            CVector2 cRectCorner(c_rectangle.GetHalfWidth(),c_rectangle.GetHalfHeight());
            s_intersection_data2.Intersection = (SquareDistance(cRectCorner, cCircleCenter) <= Square(c_circle.GetRadius()));
         }

         // TODO: points and normals
      }
      else {
         /* one or both objects are disabled, no intersection */
         s_intersection_data2.Intersection = false;
      }
   }

   /****************************************/
   /****************************************/

   void ComputeIntersection(SIntersectionData2& s_intersection_data2,
                            const CRectangle& c_rectangle,
                            const CCompound& c_compound) {

	   SIntersectionData2 localIntersection;
	   localIntersection.Intersection = false;

	   if (c_rectangle.IsEnabled() && c_compound.IsEnabled()){
		   // check for each children
		   TChildren tChildren = c_compound.GetChildren();
		   for ( TIteratorChildren it = tChildren.begin(  );
		       			  it != tChildren.end(  );
		       			  ++it) {
			   (*it)->Intersects(localIntersection, c_rectangle );
			   if ( localIntersection.Intersection == true){
				   s_intersection_data2.Intersection = true;
				   return; // we return as soon as we find the first intersecting shape
			   }
			   s_intersection_data2.Intersection = false;
		   }
	   }
	   else {
	            /* one or both circles are disabled, no intersection */
	            s_intersection_data2.Intersection = false;
	   }

   }

   /****************************************/
   /****************************************/

   void ComputeIntersection(SIntersectionData2& s_intersection_data2,
                            const CCircle& c_circle1,
                            const CCircle& c_circle2) {
      /* if both circles are enabled, go on checking */
      if(c_circle1.IsEnabled() && c_circle2.IsEnabled()) {
         /* both circles are enabled */
         /* there is an intersection when the distance between the
            centers is smaller or equal to the sum of the radia */
         Real fSquareCenterDistance = SquareDistance(c_circle1.GetCenter(),
                                                     c_circle2.GetCenter());
         s_intersection_data2.Intersection =
            fSquareCenterDistance
            <=
            Square((c_circle1.GetRadius() + c_circle2.GetRadius()));
         
         // TODO points and normals
      }
      else {
         /* one or both circles are disabled, no intersection */
         s_intersection_data2.Intersection = false;
      }
   }

   /****************************************/
   /****************************************/

   void ComputeIntersection(SIntersectionData2& s_intersection_data2,
                            const CCircle& c_circle,
                            const CCompound& c_compound) {

	   SIntersectionData2 localIntersection;
	   localIntersection.Intersection = false;

	   if (c_circle.IsEnabled() && c_compound.IsEnabled()){
		   // check for each children
		   TChildren tChildren = c_compound.GetChildren();
		   for ( TIteratorChildren it = tChildren.begin(  );
		       			  it != tChildren.end(  );
		       			  ++it) {
			   (*it)->Intersects(localIntersection, c_circle );
			   if ( localIntersection.Intersection == true){
				   s_intersection_data2.Intersection = true;
				   return; // we return as soon as we find the first intersecting shape
			   }
			   s_intersection_data2.Intersection = false;
		   }
	   }
	   else {
	            /* one or both circles are disabled, no intersection */
	            s_intersection_data2.Intersection = false;
	   }

   }

   /****************************************/
   /****************************************/

   void ComputeIntersection(SIntersectionData2& s_intersection_data2,
                            const CCompound& c_compound1,
                            const CCompound& c_compound2) {

	   SIntersectionData2 localIntersection;
	   localIntersection.Intersection = false;

	   if (c_compound1.IsEnabled() && c_compound2.IsEnabled()){
		   // check for each children
		   TChildren tChildren = c_compound1.GetChildren();
		   for ( TIteratorChildren it = tChildren.begin(  );
		       			  it != tChildren.end(  );
		       			  ++it) {
			   (*it)->Intersects(localIntersection, c_compound2 );
			   if ( localIntersection.Intersection == true){
				   s_intersection_data2.Intersection = true;
				   return; // we return as soon as we find the first intersecting shape
			   }
			   s_intersection_data2.Intersection = false;
		   }
	   }
	   else {
	            /* one or both circles are disabled, no intersection */
	            s_intersection_data2.Intersection = false;
	   }
   }

   /****************************************/
   /****************************************/

}

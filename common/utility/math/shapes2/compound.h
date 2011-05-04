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
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef COMPOUND_H
#define COMPOUND_H

namespace argos {
   class CCompound;
}

#include <argos2/common/utility/math/shapes2/primitive2.h>
#include <argos2/common/utility/logging/argos_log.h>
#include <cmath>

namespace argos {

   class CCompound : public CPrimitive2 {

   public:

	  typedef std::vector<CPrimitive2*> TChildren;
	  typedef std::vector<CPrimitive2*>::iterator TIteratorChildren;

      CCompound(const CVector2& c_center) :
    	  CPrimitive2(c_center, CRadians()) {}

      virtual ~CCompound() {
    	  m_tChildren.clear();
      }

      inline TChildren GetChildren() const {
         return m_tChildren;
      }

      inline CPrimitive2* GetChild(UInt32 n_index) const {
         return m_tChildren[n_index];
      }

      inline void AddChild(CPrimitive2* t_shape) {
    	  m_tChildren.push_back(t_shape);
      }

      inline void RemoveChild(CPrimitive2* t_shape){
    	  for ( TIteratorChildren it = m_tChildren.begin(  );
    			  it != m_tChildren.end(  );
    			  it++ ) {
    		  if ( *it == t_shape ) {
    			  m_tChildren.erase( it );
    			  return;
    		  }
    	  }
      }

      virtual void Translate(const CVector2& c_translation) {
    	  for ( TIteratorChildren it = m_tChildren.begin(  );
    			  it != m_tChildren.end(  );
    			  it++ ) {
    		  (*it)->Translate(c_translation);
    	  }
    	  m_cCenter += c_translation;
      }

      virtual void Rotate(const CRadians& c_rotation) {

    	  // first we need to rotate each shape individually, then we move the shape according to its distance from the center of the compound
    	  for ( TIteratorChildren it = m_tChildren.begin(  );
    			  it != m_tChildren.end(  );
    			  it++ ) {

    		  // rotate the single shape in place
    		  (*it)->Rotate(c_rotation);

    		  // translate into origin
    		  (*it)->Translate(CVector2(-m_cCenter.GetX(), -m_cCenter.GetY()));

    		  Real fChildX = (*it)->GetCenter().GetX();
    		  Real fChildY = (*it)->GetCenter().GetY();

    		  //rotate
    		  (*it)->SetCenter(CVector2(fChildX * Cos(c_rotation) - fChildY * Sin(c_rotation), fChildX * Sin(c_rotation) + fChildY * Cos(c_rotation)));

    		  //translate back
    		  (*it)->Translate(CVector2(m_cCenter.GetX(), m_cCenter.GetY()));

    	  }
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CRectangle& c_rectangle) {
         ComputeIntersection(s_intersection_data2, c_rectangle, *this);
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCircle& c_circle) {
         ComputeIntersection(s_intersection_data2, c_circle, *this);
      }

      inline virtual void Intersects(SIntersectionData2& s_intersection_data2, const CCompound& c_compound) {
         ComputeIntersection(s_intersection_data2, *this, c_compound);
      }

      inline CVector2 Normal(const CVector2& c_point) const {
         // TODO: implement this
         return CVector2();
      }

      inline virtual void Gnuplot() {

    	  for ( TIteratorChildren it = m_tChildren.begin(  );
    	      			  it != m_tChildren.end(  );
    	      			  it++ ) {
    		  (*it)->Gnuplot();
    	  }

         std::cout << "plot \"<echo '" << m_cCenter.GetX() << " " << m_cCenter.GetY() << "'\" lc rgb \"blue\"" << std::endl;
      }

   protected:

      std::vector<CPrimitive2*> m_tChildren;

   };

}

#endif

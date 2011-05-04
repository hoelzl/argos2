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
 * @file <common/control_interface/handbot/ci_handbot_head_camera_sensor.h>
 *
 * @brief This file provides the definition of the handbot head camera sensor.
 * @author Giovanni Pini  - <gpini@iridia.ulb.ac.be>
 * @author Alessandro Stranieri - <alessandro.stranieri@ulb.ac.be>
 *
 */

#ifndef CCI_HANDBOT_HEAD_CAMERA_SENSOR_H
#define CCI_HANDBOT_HEAD_CAMERA_SENSOR_H

namespace argos {
   class CCI_HandBotHeadCameraSensor;
}

#include <argos2/common/utility/math/vector2.h>
#include <argos2/common/control_interface/swarmanoid/ci_camera_sensor.h>

namespace argos {

   class CCI_HandBotHeadCameraSensor : public CCI_CameraSensor {

   public:

	   struct SShelfEdge {
		   CVector2 TopLeftXY;
		   CVector2 BottomRightXY;
		   bool m_bLeftEdgeColor; /* Field added to distinguish left and right edge color */

		   SShelfEdge() : TopLeftXY(0, 0), BottomRightXY(0, 0), m_bLeftEdgeColor(false){ }

		   SShelfEdge(const CVector2& c_topleftxy, const CVector2& c_bottomrightxy, bool b_left_edge = false):
		       TopLeftXY(c_topleftxy.GetX(), c_topleftxy.GetY()),
		       BottomRightXY(c_bottomrightxy.GetX(), c_bottomrightxy.GetY()),
               m_bLeftEdgeColor(b_left_edge)
		   {}

           inline SInt32 GetWidth(){
               return BottomRightXY.GetX() - TopLeftXY.GetX();
           }

           /* TODO: why the other way around, which should be the correct one, gives negative values?*/
           inline SInt32 GetHeight(){
               return BottomRightXY.GetY() - TopLeftXY.GetY();
           }

           inline SInt32 GetCentreXCoordinate(){
               return TopLeftXY.GetX() + GetWidth()/2;
           }

           inline bool IsLeftEdge() {
               return m_bLeftEdgeColor;
           }

		   friend std::ostream& operator<<(std::ostream& c_os, const SShelfEdge& s_shelfedge)
		   {
			   c_os << "(ShelfEdge: TopLeftXY " << s_shelfedge.TopLeftXY << " , " << "BottomRightXY " << s_shelfedge.BottomRightXY << ")";
			   return c_os;
		   }
	   };

	  typedef std::vector <SShelfEdge*> TShelfEdgeList;
	  typedef std::vector <SInt32> TCameraSizeVector;

	  CCI_HandBotHeadCameraSensor() : \
		CCI_CameraSensor(),
		m_bIsShelfEdgeDetectionEnabled(false), \
		m_bIsBlobDetectionEnabled(false), \
		m_bIsCameraEnabled(false)
	  {	
          }

      virtual ~CCI_HandBotHeadCameraSensor() {

      }

      inline virtual void EnableShelfEdgeDetection(){ m_bIsShelfEdgeDetectionEnabled = true; }

      inline virtual void DisableShelfEdgeDetection(){ m_bIsShelfEdgeDetectionEnabled = false; }

      inline virtual bool IsShelfEdgeDetectionEnabled(){ return m_bIsShelfEdgeDetectionEnabled; }

      inline virtual void EnableBlobDetection(){ m_bIsBlobDetectionEnabled = true; }

      inline virtual void DisableBlobDetection(){ m_bIsBlobDetectionEnabled = false; }

      inline virtual bool IsBlobDetectionEnabled(){ return m_bIsBlobDetectionEnabled; }	

      virtual const TShelfEdgeList& GetShelfEdgeList() = 0;

      virtual inline bool IsEnabled() const {
          return m_bIsCameraEnabled;
      }

      virtual inline TCameraSizeVector GetImageSize(){
    	  return m_tCameraSizeVector;
      }

      virtual void Enable() = 0;

      virtual void Disable() = 0;

   protected:

      TShelfEdgeList m_tShelfEdgeList;

      /* order: width, height */
      TCameraSizeVector m_tCameraSizeVector;

      bool m_bIsShelfEdgeDetectionEnabled;
      bool m_bIsBlobDetectionEnabled;
      bool m_bIsCameraEnabled;
   };

   inline std::ostream& operator<<(std::ostream& c_os, const CCI_HandBotHeadCameraSensor::TShelfEdgeList& t_shelf_edge_list) {
       if(t_shelf_edge_list.size() != 0){
           for(UInt32 i = 0; i < t_shelf_edge_list.size(); i++) {
               c_os << "ShelfEdge #" << i << ":" << *(t_shelf_edge_list[i]) << std::endl;
           }
       }else{
           c_os << "No edges detected" << std::endl;
       }

       return c_os;
   }

}

#endif

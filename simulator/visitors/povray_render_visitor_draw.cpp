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
 * @file <simulator/swarmanoid_space/visitors/povray_render_visitor_draw.cpp>
 *
 * @brief This file contains the implementation of the visitor for the POVRay visitor class
 *
 * @author Nithin Mathews- <nmathews@ulb.ac.be>
 */

#include "argos2/simulator/visitors/povray_render_visitor_draw.h"

namespace argos
{
	void CPovrayRenderVisitorDraw::Visit(CFloorEntity& c_entity) {

	}


   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::Visit(CBoxEntity& c_entity) {

		if(!IgnoreEntity(ToString(c_entity.GetId()))) {

			const CVector3& cPosition = c_entity.GetEmbodiedEntity().GetPosition();
			const CQuaternion& cOrientation = c_entity.GetEmbodiedEntity().GetOrientation();
			CRadians cZAngle, cYAngle, cXAngle;
			cOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
			const CVector3& cSize =  c_entity.GetSize();

			std::string strColorOrTexture = "pigment { color Red }";
			strColorOrTexture = GetBoxOrCylinderColorOrTexture(c_entity.GetId(), strColorOrTexture);

			m_cOutputFileStream << "//" << c_entity.GetId() << "\n"
			<< "box {" << "\n"
			<< "<" << - cSize.GetX() / 2 << "," << cSize.GetY() / 2 <<  "," << 0 << ">," << "\t\t//CORNER 1 (bottom left) \n"
			<< "<" << + cSize.GetX() / 2 << "," << -  cSize.GetY() / 2  <<  "," << cSize.GetZ()  << ">" << "\t\t//CORNER 2 (top right)\n"
			<< strColorOrTexture << "\t//COLOR\n"
			<< "rotate <" << ToDegrees(cXAngle).GetValue() << "," << ToDegrees(cYAngle).GetValue() <<  "," << ToDegrees(cZAngle).GetValue() << ">" << "\t\t//ROTATION \n"
			<< "translate <" << cPosition.GetX() << "," << cPosition.GetY()  <<  "," << cPosition.GetZ() - cSize.GetZ() / 2 << ">" << "\t\t//TRANSLATION \n"
			<< "}" << "\n"
			<< std::endl    << std::flush;

		}
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::Visit(CCylinderEntity& c_entity) {

		/* TODO: currently missing rendering of LEDs */

		if(!IgnoreEntity(c_entity.GetId())) {
			const CVector3& cPosition = c_entity.GetEmbodiedEntity().GetPosition();
			const CQuaternion& cOrientation = c_entity.GetEmbodiedEntity().GetOrientation();
			CRadians cZAngle, cYAngle, cXAngle;
			cOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);

			std::string strColorOrTexture = "pigment { color Green }";
			strColorOrTexture = GetBoxOrCylinderColorOrTexture(c_entity.GetId(), strColorOrTexture);

			m_cOutputFileStream << "//" << c_entity.GetId() << "\n"
			<< "cylinder {" << "\n"
			<< "<" << 0 << "," << 0  <<  "," << 0 << ">," << "\t\t//BASE POINT \n"
			<< "<" << 0 << "," << 0  <<  "," << c_entity.GetHeight() << ">," << "\t\t//CAP POINT \n"
			<< c_entity.GetRadius() << "\t\t\t//RADIUS\n"
			<< strColorOrTexture << "\t//COLOR\n"
			<< "rotate <" << ToDegrees(cXAngle).GetValue() << "," << ToDegrees(cYAngle).GetValue() <<  "," << ToDegrees(cZAngle).GetValue() << ">" << "\t\t//ROTATION \n"
			<< "translate <" << cPosition.GetX() << "," << cPosition.GetY()  <<  "," << cPosition.GetZ() - c_entity.GetHeight() / 2 << ">" << "\t\t//TRANSLATION \n"
			<< "}" << "\n"
			<< std::endl    << std::flush;
		}
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::Visit(CFootBotEntity& c_entity) {

		if(!IgnoreEntity(c_entity.GetId())) {

			CLedEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();
			const CColor& cBeaconColor = cLEDEquippedEntity.GetLED(12).GetColor();
			const CVector3& cPosition = c_entity.GetEmbodiedEntity().GetPosition();
			const CQuaternion& cOrientation = c_entity.GetEmbodiedEntity().GetOrientation();
			CRadians cZAngle, cYAngle, cXAngle;
			cOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);

			// Output
			m_cOutputFileStream << "//" << c_entity.GetId() << "\n"
			<< "footbot(" << "\n"
			<< "<" << cPosition.GetX() << "," << cPosition.GetY() <<  "," << cPosition.GetZ() << ">," << "\t\t//FOOTBOT_POSITION \n"
			<< "<" << ToDegrees(cXAngle).GetValue() << "," << ToDegrees(cYAngle).GetValue() <<  "," << ToDegrees(cZAngle).GetValue() << ">," << "\t\t//FOOTBOT_ROTATION \n"
			<< "rgb <" << GetPovrayColorValue(cBeaconColor.GetRed()) << "," << GetPovrayColorValue(cBeaconColor.GetGreen()) <<  "," << GetPovrayColorValue(cBeaconColor.GetBlue()) << ">," << "\t\t//FOOTBOT_BEACON_COLOR \n"
			<< "1,"  "\t\t\t//FOOTBOT_BATTERY_INSERTED \n"
			<< "<0,0," << ToDegrees(c_entity.GetDistanceScannerEquippedEntity().GetRotation()).GetValue() << ">," << "\t\t//FOOTBOT_DISTANCE_SCANNER_ROTATION \n"
			<< "<0,0," << ToDegrees(c_entity.GetTurretRotation()).GetValue() << ">," << "\t\t//FOOTBOT_TURRET_ROTATION \n"
			<< (1.0f - c_entity.GetGripperEquippedEntity().GetLogicLockState()) * 90.0f << "," << "\t\t\t//FOOTBOT_GRIPPER_APERTURE \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED1_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(1).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(1).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(1).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED2_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(2).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(2).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(2).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED3_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(3).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(3).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(3).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED4_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(4).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(4).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(4).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED5_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(5).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(5).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(5).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED6_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(6).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(6).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(6).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED7_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(7).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(7).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(7).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED8_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(8).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(8).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(8).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED9_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(9).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(9).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(9).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED10_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(10).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(10).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(10).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED11_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(11).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(11).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(11).GetColor().GetBlue()) << ">," << "\t\t//FOOTBOT_LED12_COLOR \n"
			<< ")" << "\n"
			<< std::endl    << std::flush;

		}
	}


	/****************************************/
	/****************************************/

	void CPovrayRenderVisitorDraw::Visit(CEyeBotEntity& c_entity) {

		if(!IgnoreEntity(c_entity.GetId())) {

			CLedEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();
			const CVector3& cPosition = c_entity.GetEmbodiedEntity().GetPosition();
			const CQuaternion& cOrientation = c_entity.GetEmbodiedEntity().GetOrientation();
			CRadians cZAngle, cYAngle, cXAngle;
			cOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);


			// Output
			m_cOutputFileStream << "//" << c_entity.GetId() << "\n"
			<< "eyebot(" << "\n"
			<< "<" << cPosition.GetX() << "," << cPosition.GetY() <<  "," << cPosition.GetZ() << ">," << "\t\t//EYEBOT_POSITION \n"
			<< "<" << ToDegrees(cXAngle).GetValue() << "," << ToDegrees(cYAngle).GetValue() <<  "," << ToDegrees(cZAngle).GetValue() << ">," << "\t\t//EYEBOT_ROTATION \n"
			<< "<0,0,0>," << "\t\t//EYEBOT_CAMERA_ROTATION \n"
			<< "<0,0,0>," << "\t\t//EYEBOT_PROPELLER_ROTATION \n"
			<< "<0,0,0>," << "\t\t//EYEBOT_DISTANCE_SCANNER_ROTATION \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(30).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(30).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(30).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED1_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(28).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(28).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(28).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED2_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(26).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(26).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(26).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED3_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(24).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(24).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(24).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED4_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(22).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(22).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(22).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED5_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(20).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(20).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(20).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED6_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(18).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(18).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(18).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED7_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(16).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(16).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(16).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED8_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(14).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(14).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(14).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED9_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(12).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(12).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(12).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED10_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(10).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(10).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(10).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED11_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(8).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(8).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(8).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED12_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(6).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(6).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(6).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED13_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(4).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(4).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(4).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED14_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(2).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(2).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(2).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED15_COLOR \n"
			<< "rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetBlue()) << ">," << "\t\t//EYEBOT_LED16_COLOR \n"
			<< ")" << "\n"
			<< std::endl    << std::flush;

		}
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::Visit(CLightEntity& c_entity) {

		if(!IgnoreEntity(c_entity.GetId())) {

			CLedEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();
			const CVector3& cPosition = c_entity.GetPosition();

			// Output
			m_cOutputFileStream << "//" << c_entity.GetId() << "\n"

			// Output light declaration
			<< "#declare light_source_body_" << c_entity.GetId() << " = object { sphere { <0,0,0>, 0.1 } texture { pigment {color rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetBlue()) << ">} finish {ambient .8 diffuse .6}} }"<< "\n"

			// Now write the actual light source
			<< "light_source{ <" << cPosition.GetX() << "," << cPosition.GetY() <<  "," << cPosition.GetZ() << "> color rgb <" << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetRed()) << "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetGreen()) <<  "," << GetPovrayColorValue(cLEDEquippedEntity.GetLED(0).GetColor().GetBlue())<< "> looks_like {light_source_body_" << c_entity.GetId()<< "} }" << "\n\n"

			<< std::endl    << std::flush;
		}

	}

   /****************************************/
   /****************************************/

	Real CPovrayRenderVisitorDraw::GetPovrayColorValue(UInt8 n_value) {
			return (Real) n_value / 255;
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::SetEntityToIgnore(std::string& s_id) {
		m_vIgnoreEntityIDs.push_back(s_id);
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::SetBoxOrCylinderColorRedefinition(std::string& s_key, std::string& s_value) {
		m_mapBoxOrCylinderColorRedefinitionMap[s_key] =  s_value;
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::SetBoxOrCylinderTextureRedefinition(std::string& s_key, std::string& s_value) {
		m_mapBoxOrCylinderTextureRedefinitionMap[s_key] =  s_value;
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::SetLightSource(std::string& strLightSourcePosition, std::string& strLightSourceColor, Real& fLightSourceFadeDistance, Real& fLightSourceFadePower,std::string& strLightSourceShadowless) {

	    std::string strCompleteString =  "  light_source { < " + strLightSourcePosition + "> color " + strLightSourceColor + "  fade_distance " + ToString(fLightSourceFadeDistance) + " fade_power " + ToString(fLightSourceFadePower) +  " " + strLightSourceShadowless + " } ";
	    m_vLightSources.push_back(strCompleteString);
	}

   /****************************************/
   /****************************************/

	void CPovrayRenderVisitorDraw::DrawLightSources() {

        for (UInt32 i=0; i < m_vLightSources.size(); i++) {
            m_cOutputFileStream << m_vLightSources[i] << "\n" << std::endl    << std::flush;
        }
	}

   /****************************************/
   /****************************************/

	bool CPovrayRenderVisitorDraw::IgnoreEntity(const std::string& s_id) {

		bool bResult = false;

		for (UInt32 i=0; i < m_vIgnoreEntityIDs.size(); i++) {

			// Return true, if the id was exactly defined
			if( s_id == m_vIgnoreEntityIDs[i]) bResult = true;

			// or if a matching pattern exists
			if(MatchPattern(s_id, m_vIgnoreEntityIDs[i])) bResult = true;
		}

		return bResult;
	}

   /****************************************/
   /****************************************/

	std::string CPovrayRenderVisitorDraw::GetBoxOrCylinderColorOrTexture(std::string s_entity_id, std::string s_std_value){

		std::string strColorOrTexture = s_std_value;

		// Check if a color was redefined by the user for this entity
		TSceneBoxOrCylinderColorRedefinitionMap::iterator itColor = m_mapBoxOrCylinderColorRedefinitionMap.find(s_entity_id);

		if(itColor == m_mapBoxOrCylinderColorRedefinitionMap.end()) {

			// // If not check if a matching pattern can be found
			TSceneBoxOrCylinderColorRedefinitionMap::iterator itMatchingEntities;
			for( itMatchingEntities = m_mapBoxOrCylinderColorRedefinitionMap.begin(); itMatchingEntities != m_mapBoxOrCylinderColorRedefinitionMap.end(); itMatchingEntities++ ) {

				 if(MatchPattern(s_entity_id, itMatchingEntities->first)) {
					 strColorOrTexture  = (*itMatchingEntities).second;
				 }
			}
		}
		else {
			// If yes, get the color definition
			strColorOrTexture = (*itColor).second;
		}


		// Now check if the redefinition included textures
		TSceneBoxOrCylinderTextureRedefinitionMap::iterator itTexture = m_mapBoxOrCylinderTextureRedefinitionMap.find(s_entity_id);
		if(itTexture == m_mapBoxOrCylinderTextureRedefinitionMap.end()) {

			// If not, check if a matching pattern can be found
			TSceneBoxOrCylinderTextureRedefinitionMap::iterator itMatchingEntities;
			for( itMatchingEntities = m_mapBoxOrCylinderTextureRedefinitionMap.begin(); itMatchingEntities != m_mapBoxOrCylinderTextureRedefinitionMap.end(); itMatchingEntities++ ) {

				 if(MatchPattern(s_entity_id, itMatchingEntities->first)) {
					 strColorOrTexture  = (*itMatchingEntities).second;
				 }
			}
		}
		else {
			// If yes, get the texture definition
			strColorOrTexture = (*itTexture).second;
		}

		return strColorOrTexture;
	}

   /****************************************/
   /****************************************/

}
;

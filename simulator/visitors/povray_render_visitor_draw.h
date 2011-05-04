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
 * @file <simulator/swarmanoid_space/visitors/text_render_visitor_draw.h>
 *
 * @brief This file contains the definition of the
 *
 * @author Manuele Brambilla - <mbrambilla@iridia.ulb.ac.be>
 *
 */

#ifndef POVRAY_RENDER_VISITOR_DRAW_H
#define POVRAY_RENDER_VISITOR_DRAW_H

#include <argos2/simulator/visitors/entity_visitor.h>
#include <argos2/simulator/space/entities/box_entity.h>
#include <argos2/simulator/space/entities/cylinder_entity.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/eyebot_entity.h>
#include <argos2/simulator/space/entities/light_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>
#include <argos2/simulator/space/entities/distance_scanner_equipped_entity.h>
#include <argos2/simulator/space/entities/gripper_equipped_entity.h>

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

namespace argos
{

	typedef std::map<std::string, std::string> TSceneBoxOrCylinderColorRedefinitionMap;
	typedef std::map<std::string, std::string> TSceneBoxOrCylinderTextureRedefinitionMap;

   class CPovrayRenderVisitorDraw : public CEntityVisitor {

   private:
      /** a reference to the output file stream */
      std::ofstream& m_cOutputFileStream;

      std::vector<std::string> m_vIgnoreEntityIDs;

      std::vector<std::string> m_vLightSources;

      Real GetPovrayColorValue(UInt8 n_value);

      TSceneBoxOrCylinderColorRedefinitionMap m_mapBoxOrCylinderColorRedefinitionMap;

      TSceneBoxOrCylinderTextureRedefinitionMap m_mapBoxOrCylinderTextureRedefinitionMap;

      std::string GetBoxOrCylinderColorOrTexture(std::string s_entity_id, std::string s_std_value);

      bool IgnoreEntity(const std::string& s_id);

   public:

      CPovrayRenderVisitorDraw(std::ofstream& c_output_file_stream) :
         m_cOutputFileStream(c_output_file_stream){}

      virtual void Visit(CFloorEntity& c_entity);

      virtual void Visit(CBoxEntity& c_entity);

      virtual void Visit(CCylinderEntity& c_entity);

      virtual void Visit(CFootBotEntity& c_entity);

      virtual void Visit(CEyeBotEntity& c_entity);

      virtual void Visit(CLightEntity& c_entity);

      virtual void Visit(CEPuckEntity& c_entity) {}

      virtual void Visit(CWiFiMediumEntity& c_entity) {}

      virtual void SetBoxOrCylinderColorRedefinition(std::string& s_key, std::string& s_value);

      virtual void SetBoxOrCylinderTextureRedefinition(std::string& s_key, std::string& s_value);

      virtual void SetEntityToIgnore(std::string& s_id);

      virtual void SetLightSource(std::string& strLightSourcePosition, std::string& strLightSourceColor, Real& fLightSourceFadeDistance, Real& fLightSourceFadePower, std::string& strLightSourceShadowless);

      virtual void DrawLightSources();

   };

}

#endif

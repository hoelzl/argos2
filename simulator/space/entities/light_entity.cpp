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
 * @file <argos2/simulator/space/entities/light_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "light_entity.h"

namespace argos {

   /****************************************/
   /****************************************/

   CLightEntity::CLightEntity() :
      CPositionalEntity(NULL),
      m_cLEDEquippedEntity(this),
      m_fIntensity(0.0f),
      m_cColor(CColor::BLACK) {
      m_cLEDEquippedEntity.AddLed(CVector3());
   }

   /****************************************/
   /****************************************/

   void CLightEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* Init parent */
         CPositionalEntity::Init(t_tree);
         /* Init component */
         m_cLEDEquippedEntity.Init(t_tree);
         /* Parse XML */
         GetNodeAttribute(t_tree, "color", m_cColor);
         GetNodeAttribute(t_tree, "intensity", m_fIntensity);
         /* Initialize the LED entity */
         m_cLEDEquippedEntity.SetLedPosition(0, GetPosition());
         m_cLEDEquippedEntity.SetLedColor(0, m_cColor);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error while initializing light entity", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CLightEntity::Reset() {
      CPositionalEntity::Reset();
      m_cLEDEquippedEntity.Reset();
      m_cLEDEquippedEntity.SetLedColor(0, m_cColor);
   }

   /****************************************/
   /****************************************/

   void CLightEntity::Destroy() {
      m_cLEDEquippedEntity.Destroy();
      CPositionalEntity::Reset();
   }

   /****************************************/
   /****************************************/

   REGISTER_ENTITY(CLightEntity,
                   "light",
                   "A colored light.",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "The light entity is an entity that emits a light detectable by a robot camera\n"
                   "(as a normal LED) or by light sensors. A light is bodyless, therefore it must\n"
                   "not be added to physics engines.\n"
                   "A light is characterized by a color and an intensity. The color of the light\n"
                   "is perceived by cameras. The intensity modifies the reading of the light\n"
                   "sensors. The higher the intensity, the closer the light is perceived.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <arena ...>\n"
                   "    ...\n"
                   "    <light id=\"light0\"\n"
                   "           position=\"0.4,2.3,0.25\"\n"
                   "           orientation=\"0,0,0\"\n"
                   "           color=\"yellow\"\n"
                   "           intensity=\"1.0\" />\n"
                   "    ...\n"
                   "  </arena>\n\n"
                   "The 'id' attribute is necessary and must be unique among the entities. If two\n"
                   "entities share the same id, initialization aborts.\n"
                   "The 'position' attribute specifies the position of the center of the light.\n"
                   "The attribute values are in the X,Y,Z order.\n"
                   "The 'orientation' attribute specifies the orientation of the light. At the\n"
                   "moment this attribute is mandatory but its value is ignored. In the future,\n"
                   "it will be used to implement a directional light.\n"
                   "The 'color' attribute specifies the color of the light.\n"
                   "The 'intensity' attribute sets the intensity of the light. When the value is\n"
                   "1.0, the light emits a normal amount of light. When it is 0.5 the amount of\n"
                   "light is half, and when the value is 2.0 the emission is doubled. The\n"
                   "intensity of the light affects the readings of the light sensors but not\n"
                   "those of the cameras.\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None for the time being.\n",
                   "Under development"
      );

   /****************************************/
   /****************************************/

}

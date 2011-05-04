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
 * @file <simulator/space/entities/epuck_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "epuck_entity.h"
#include "embodied_entity.h"
#include "controllable_entity.h"
#include "led_equipped_entity.h"
#include "gripper_equipped_entity.h"
#include "distance_scanner_equipped_entity.h"
#include "rab_equipped_entity.h"
#include <argos2/common/utility/math/matrix3x3.h>

namespace argos {

   /****************************************/
   /****************************************/

   static const Real EPUCK_RADIUS                   = 0.035f;
   static const Real EPUCK_HEIGHT                   = 0.086f;

   static const Real EPUCK_LED_RING_RADIUS          = EPUCK_RADIUS + 0.007;

   static const Real EPUCK_INTERWHEEL_DISTANCE      = 0.053f;
   static const Real EPUCK_HALF_INTERWHEEL_DISTANCE = EPUCK_INTERWHEEL_DISTANCE * 0.5f;

   static const Real EPUCK_LED_RING_ELEVATION       = 0.086f;
   static const Real EPUCK_CAMERA_ELEVATION         = 0.027f;

   /* We can't use CRadians::PI and the likes here because of the 'static initialization order fiasco' */
   static const CRadians EPUCK_LED_ANGLE_SLICE      = CRadians(ARGOS_PI / 4.0);
   static const CRadians EPUCK_HALF_LED_ANGLE_SLICE = EPUCK_LED_ANGLE_SLICE * 0.5f;

   /****************************************/
   /****************************************/

   class CEPuckEmbodiedEntity : public CEmbodiedEntity {

   public:

      CEPuckEmbodiedEntity(CEPuckEntity* pc_parent) :
         CEmbodiedEntity(pc_parent) {
         m_cHalfSize.SetX(EPUCK_RADIUS);
         m_cHalfSize.SetY(EPUCK_RADIUS);
         m_cHalfSize.SetZ(EPUCK_HEIGHT * 0.5f);
      }

   protected:

      virtual void CalculateBoundingBox() {
         m_cCenterPos = GetPosition();
         m_cCenterPos.SetZ(m_cCenterPos.GetZ() + m_cHalfSize.GetZ());
         m_cOrientationMatrix.FromQuaternion(GetOrientation());
         CalculateBoundingBoxFromHalfSize(GetBoundingBox(),
                                          m_cHalfSize,
                                          m_cCenterPos,
                                          m_cOrientationMatrix);
      }

   private:

      CVector3 m_cHalfSize;
      CVector3 m_cCenterPos;
      CMatrix3x3 m_cOrientationMatrix;

   };

   /****************************************/
   /****************************************/

   CEPuckEntity::CEPuckEntity() :
      CComposableEntity(NULL),
      m_pcEmbodiedEntity(new CEPuckEmbodiedEntity(this)),
      m_pcControllableEntity(new CControllableEntity(this)),
      m_pcWheeledEntity(new CWheeledEntity<2>(this)),
      m_pcLEDEquippedEntity(new CLedEquippedEntity(this)),
      m_pcRABEquippedEntity(new CRABEquippedEntity<2>(this)) {
      /* Left wheel position */
      m_pcWheeledEntity->SetWheelPosition(0, CVector3(0.0f,  EPUCK_HALF_INTERWHEEL_DISTANCE, 0.0f));
      /* Right wheel position */
      m_pcWheeledEntity->SetWheelPosition(1, CVector3(0.0f, -EPUCK_HALF_INTERWHEEL_DISTANCE, 0.0f));
      /* Add LEDs [0-7] */
      for(UInt32 i = 0; i < 8; ++i) {
         m_pcLEDEquippedEntity->AddLed(CVector3());
      }
   }

   /****************************************/
   /****************************************/

   CEPuckEntity::~CEPuckEntity() {
      delete m_pcEmbodiedEntity;
      delete m_pcControllableEntity;
      delete m_pcWheeledEntity;
      delete m_pcLEDEquippedEntity;
      delete m_pcRABEquippedEntity;
   }

   /****************************************/
   /****************************************/

   void CEPuckEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* Init parent */
         CEntity::Init(t_tree);
         /* Init components */
         m_pcEmbodiedEntity->Init(t_tree);
         m_pcControllableEntity->Init(t_tree);
         m_pcWheeledEntity->Init(t_tree);
         m_pcLEDEquippedEntity->Init(t_tree);
         m_pcRABEquippedEntity->Init(t_tree);
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CEPuckEntity::Reset() {
      /* Reset all components */
      m_pcEmbodiedEntity->Reset();
      m_pcControllableEntity->Reset();
      m_pcWheeledEntity->Reset();
      m_pcLEDEquippedEntity->Reset();
      m_pcRABEquippedEntity->Reset();
      /* Update components */
      UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CEPuckEntity::Destroy() {
      m_pcEmbodiedEntity->Destroy();
      m_pcControllableEntity->Destroy();
      m_pcWheeledEntity->Destroy();
      m_pcLEDEquippedEntity->Destroy();
      m_pcRABEquippedEntity->Destroy();
   }

   /****************************************/
   /****************************************/

   CEntity& CEPuckEntity::GetComponent(const std::string& str_component) {
      if(str_component == "embodied_entity") {
         return *m_pcEmbodiedEntity;
      }
      else if(str_component == "controllable_entity") {
         return *m_pcControllableEntity;
      }
      else if(str_component == "wheeled_entity<2>") {
         return *m_pcWheeledEntity;
      }
      else if(str_component == "led_equipped_entity") {
         return *m_pcLEDEquippedEntity;
      }
      else if(str_component == "rab_equipped_entity<2>"){
         return *m_pcRABEquippedEntity;
      }
      else {
         THROW_ARGOSEXCEPTION("An e-puck does not have a component of type \"" << str_component << "\"");
      }
   }

   /****************************************/
   /****************************************/

   bool CEPuckEntity::HasComponent(const std::string& str_component) {
      return (str_component == "embodied_entity"       ||
              str_component == "controllable_entity"   ||
              str_component == "wheeled_entity<2>"     ||
              str_component == "led_equipped_entity"   ||
              str_component == "rab_equipped_entity<2>");
   }

   /****************************************/
   /****************************************/

   void CEPuckEntity::UpdateComponents() {
      SetLedPosition();
      m_pcEmbodiedEntity->UpdateBoundingBox();
      m_pcRABEquippedEntity->SetPosition(m_pcEmbodiedEntity->GetPosition());
   }

   /****************************************/
   /****************************************/
   
#define SET_RING_LED_POSITION(IDX)                                          \
   cLEDPosition.Set(EPUCK_LED_RING_RADIUS, 0.0f, EPUCK_LED_RING_ELEVATION); \
   cLEDAngle = -EPUCK_HALF_LED_ANGLE_SLICE;                                 \
   cLEDAngle -= EPUCK_LED_ANGLE_SLICE * IDX;                                \
   cLEDPosition.RotateZ(cLEDAngle);                                         \
   cLEDPosition.Rotate(m_pcEmbodiedEntity->GetOrientation());               \
   cLEDPosition += cEntityPosition;                                         \
   m_pcLEDEquippedEntity->SetLedPosition(IDX, cLEDPosition);
   
   void CEPuckEntity::SetLedPosition() {
      /* Set LED positions */
      const CVector3& cEntityPosition = GetEmbodiedEntity().GetPosition();
      CVector3 cLEDPosition;
      CRadians cLEDAngle;
      SET_RING_LED_POSITION(0);
      SET_RING_LED_POSITION(1);
      SET_RING_LED_POSITION(2);
      SET_RING_LED_POSITION(3);
      SET_RING_LED_POSITION(4);
      SET_RING_LED_POSITION(5);
      SET_RING_LED_POSITION(6);
      SET_RING_LED_POSITION(7);
   }

   /****************************************/
   /****************************************/

   REGISTER_ENTITY(CEPuckEntity,
                   "e-puck",
                   "The e-puck robot.",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "The e-puck is a simple wheeled robot.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <arena ...>\n"
                   "    ...\n"
                   "    <e-puck id=\"fb0\"\n"
                   "              position=\"0.4,2.3,0.25\"\n"
                   "              orientation=\"45,90,0\"\n"
                   "              controller=\"mycntrl\" />\n"
                   "    ...\n"
                   "  </arena>\n\n"
                   "The 'id' attribute is necessary and must be unique among the entities. If two\n"
                   "entities share the same id, initialization aborts.\n"
                   "The 'position' attribute specifies the position of the pucktom point of the\n"
                   "e-puck in the arena. When the robot is untranslated and unrotated, the\n"
                   "pucktom point is in the origin and it is defined as the middle point between\n"
                   "the two wheels on the XY plane and the lowest point of the robot on the Z\n"
                   "axis, that is the point where the wheels touch the floor. The attribute values\n"
                   "are in the X,Y,Z order.\n"
                   "The 'orientation' attribute specifies the orientation of the e-puck. All\n"
                   "rotations are performed with respect to the pucktom point. The order of the\n"
                   "angles is Z,Y,X, which means that the first number corresponds to the rotation\n"
                   "around the Z axis, the second around Y and the last around X. This reflects\n"
                   "the internal convention used in ARGoS, in which rotations are performed in\n"
                   "that order. Angles are expressed in degrees. When the robot is unrotated, it\n"
                   "is oriented along the X axis.\n"
                   "The 'controller' attribute is used to assign a controller to the e-puck. The\n"
                   "value of the attribute must be set to the id of a previously defined\n"
                   "controller. Controllers are defined in the <controllers> XML subtree.\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None for the time being.\n",
                   "Under development"
      );

}

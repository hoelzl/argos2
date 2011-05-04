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
 * @file <simulator/space/entities/eyebot_entity.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "eyebot_entity.h"
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

   static const Real EYEBOT_HEIGHT                   = 0.566f;
   static const Real EYEBOT_RADIUS                   = 0.25f;
   static const Real EYEBOT_LED_UPPER_RING_RADIUS    = EYEBOT_RADIUS + 0.005;
   static const Real EYEBOT_LED_UPPER_RING_ELEVATION = 0.1635f;
   static const Real EYEBOT_LED_LOWER_RING_RADIUS    = EYEBOT_RADIUS + 0.005;
   static const Real EYEBOT_LED_LOWER_RING_ELEVATION = 0.1535f;

   /* We can't use CRadians::PI and the likes here because of the 'static initialization order fiasco' */
   static const CRadians EYEBOT_LED_ANGLE_SLICE      = CRadians(3.14159265358979323846264338327950288 / 8.0);
   static const CRadians EYEBOT_HALF_LED_ANGLE_SLICE = EYEBOT_LED_ANGLE_SLICE * 0.5f;

   /****************************************/
   /****************************************/

   class CEyeBotEmbodiedEntity : public CEmbodiedEntity {

   public:

      CEyeBotEmbodiedEntity(CEyeBotEntity* pc_parent) :
         CEmbodiedEntity(pc_parent) {
         m_cHalfSize.SetX(EYEBOT_RADIUS);
         m_cHalfSize.SetY(EYEBOT_RADIUS);
         m_cHalfSize.SetZ(EYEBOT_HEIGHT * 0.5f);
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

   CEyeBotEntity::CEyeBotEntity() :
      CComposableEntity(NULL),
      m_pcEmbodiedEntity(new CEyeBotEmbodiedEntity(this)),
      m_pcControllableEntity(new CControllableEntity(this)),
      m_pcLEDEquippedEntity(new CLedEquippedEntity(this)),
      m_pcDistanceScannerEquippedEntity(new CDistanceScannerEquippedEntity(this)),
      m_pcRABEquippedEntity(new CRABEquippedEntity<10>(this)),
      m_bAttachedToCeiling(false) {
      /* Add LEDs */
      for(UInt32 i = 0; i < 16; ++i) {
         m_pcLEDEquippedEntity->AddLed(CVector3());
         m_pcLEDEquippedEntity->AddLed(CVector3());
      }
      m_pcLEDEquippedEntity->AddLed(CVector3(),CColor::RED);
   }

   /****************************************/
   /****************************************/

   CEyeBotEntity::~CEyeBotEntity() {
      delete m_pcEmbodiedEntity;
      delete m_pcControllableEntity;
      delete m_pcLEDEquippedEntity;
      delete m_pcDistanceScannerEquippedEntity;
      delete m_pcRABEquippedEntity;
   }

   /****************************************/
   /****************************************/

   void CEyeBotEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* Init parent */
         CEntity::Init(t_tree);
         /* Init components */
         m_pcEmbodiedEntity->Init(t_tree);
         m_pcControllableEntity->Init(t_tree);
         m_pcLEDEquippedEntity->Init(t_tree);
         m_pcDistanceScannerEquippedEntity->Init(t_tree);
         m_pcRABEquippedEntity->Init(t_tree);
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CEyeBotEntity::Reset() {
      /* Reset all components */
      m_pcEmbodiedEntity->Reset();
      m_pcControllableEntity->Reset();
      m_pcLEDEquippedEntity->Reset();
      m_pcDistanceScannerEquippedEntity->Reset();
      m_pcRABEquippedEntity->Reset();
      /* Update components */
      UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CEyeBotEntity::Destroy() {
      m_pcEmbodiedEntity->Destroy();
      m_pcControllableEntity->Destroy();
      m_pcLEDEquippedEntity->Destroy();
      m_pcDistanceScannerEquippedEntity->Destroy();
      m_pcRABEquippedEntity->Destroy();
   }

   /****************************************/
   /****************************************/

   CEntity& CEyeBotEntity::GetComponent(const std::string& str_component) {
      if(str_component == "embodied_entity") {
         return *m_pcEmbodiedEntity;
      }
      else if(str_component == "controllable_entity") {
         return *m_pcControllableEntity;
      }
      else if(str_component == "led_equipped_entity") {
         return *m_pcLEDEquippedEntity;
      }
      else if(str_component == "distance_scanner_equipped_entity") {
         return *m_pcDistanceScannerEquippedEntity;
      }
      else if(str_component == "rab_equipped_entity<10>") {
         return *m_pcRABEquippedEntity;
      }
      else {
         THROW_ARGOSEXCEPTION("An eye-bot does not have a component of type \"" << str_component << "\"");
      }
   }

   /****************************************/
   /****************************************/

   bool CEyeBotEntity::HasComponent(const std::string& str_component) {
      return (str_component == "embodied_entity"                  ||
              str_component == "controllable_entity"              ||
              str_component == "led_equipped_entity"              ||
              str_component == "distance_scanner_equipped_entity" ||
              str_component == "rab_equipped_entity<10>");
   }

   /****************************************/
   /****************************************/

   void CEyeBotEntity::UpdateComponents() {
      SetLedPosition();
      m_pcDistanceScannerEquippedEntity->UpdateRotation();
      m_pcEmbodiedEntity->UpdateBoundingBox();
      m_pcRABEquippedEntity->SetPosition(m_pcEmbodiedEntity->GetPosition());
   }

   /****************************************/
   /****************************************/
   
#define SET_RING_LED_POSITION(IDX)                                                        \
   cLEDAngle = cLEDAnglePhase;                                                            \
   cLEDAngle += EYEBOT_LED_ANGLE_SLICE * IDX;                                             \
   cLEDPosition.Set(EYEBOT_LED_UPPER_RING_RADIUS, 0.0f, EYEBOT_LED_UPPER_RING_ELEVATION); \
   cLEDPosition.RotateZ(cLEDAngle);                                                       \
   cLEDPosition.Rotate(m_pcEmbodiedEntity->GetOrientation());                             \
   cLEDPosition += cEntityPosition;                                                       \
   m_pcLEDEquippedEntity->SetLedPosition(IDX*2, cLEDPosition);                            \
   cLEDPosition.Set(EYEBOT_LED_LOWER_RING_RADIUS, 0.0f, EYEBOT_LED_LOWER_RING_ELEVATION); \
   cLEDPosition.RotateZ(cLEDAngle);                                                       \
   cLEDPosition.Rotate(m_pcEmbodiedEntity->GetOrientation());                             \
   cLEDPosition += cEntityPosition;                                                       \
   m_pcLEDEquippedEntity->SetLedPosition(IDX*2+1, cLEDPosition);
   
   void CEyeBotEntity::SetLedPosition() {
      /* Set LED positions */
      const CVector3& cEntityPosition = GetEmbodiedEntity().GetPosition();
      CVector3 cLEDPosition;
      CRadians cLEDAnglePhase = EYEBOT_HALF_LED_ANGLE_SLICE;
      CRadians cLEDAngle;
      SET_RING_LED_POSITION(0);
      SET_RING_LED_POSITION(1);
      SET_RING_LED_POSITION(2);
      SET_RING_LED_POSITION(3);
      SET_RING_LED_POSITION(4);
      SET_RING_LED_POSITION(5);
      SET_RING_LED_POSITION(6);
      SET_RING_LED_POSITION(7);
      SET_RING_LED_POSITION(8);
      SET_RING_LED_POSITION(9);
      SET_RING_LED_POSITION(10);
      SET_RING_LED_POSITION(11);
      SET_RING_LED_POSITION(12);
      SET_RING_LED_POSITION(13);
      SET_RING_LED_POSITION(14);
      SET_RING_LED_POSITION(15);
      cLEDPosition.Set(EYEBOT_LED_LOWER_RING_RADIUS*0.7, 0.0f, EYEBOT_LED_LOWER_RING_ELEVATION-0.01);
      cLEDPosition.RotateZ(3.0 * CRadians::PI_OVER_FOUR);
      cLEDPosition.Rotate(m_pcEmbodiedEntity->GetOrientation());
      cLEDPosition += cEntityPosition;
      m_pcLEDEquippedEntity->SetLedPosition(32,cLEDPosition);
   }

   /****************************************/
   /****************************************/

   REGISTER_ENTITY(CEyeBotEntity,
                   "eye-bot",
                   "The eye-bot robot, developed in the Swarmanoid project.",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "The eye-bot is a flying robot developed in the Swarmanoid Project. It is a\n"
                   "robot with a rich set of sensors and actuators. For more information,\n"
                   "refer to the dedicated web page\n"
                   "(http://www.swarmanoid.org/swarmanoid_hardware.php).\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <arena ...>\n"
                   "    ...\n"
                   "    <eye-bot id=\"fb0\"\n"
                   "              position=\"0.4,2.3,0.25\"\n"
                   "              orientation=\"45,90,0\"\n"
                   "              controller=\"mycntrl\" />\n"
                   "    ...\n"
                   "  </arena>\n\n"
                   "The 'id' attribute is necessary and must be unique among the entities. If two\n"
                   "entities share the same id, initialization aborts.\n"
                   "The 'position' attribute specifies the position of the center of mass of the\n"
                   "eye-bot in the arena. The attribute values are in the X,Y,Z order.\n"
                   "The 'orientation' attribute specifies the orientation of the eye-bot. All\n"
                   "rotations are performed with respect to the center of mass. The order of the\n"
                   "angles is Z,Y,X, which means that the first number corresponds to the rotation\n"
                   "around the Z axis, the second around Y and the last around X. This reflects\n"
                   "the internal convention used in ARGoS, in which rotations are performed in\n"
                   "that order. Angles are expressed in degrees. When the robot is unrotated, it\n"
                   "is oriented along the X axis.\n"
                   "The 'controller' attribute is used to assign a controller to the eye-bot. The\n"
                   "value of the attribute must be set to the id of a previously defined\n"
                   "controller. Controllers are defined in the <controllers> XML subtree.\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None for the time being.\n",
                   "Under development"
      );

}

/* -*- Mode: C++ -*-
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
 * @file <simulator/space/entities/entity_decorator.h>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef ENTITY_DECORATOR_H
#define ENTITY_DECORATOR_H

namespace argos {
   class CEntityDecorator;
}

#include <argos2/simulator/space/entities/entity.h>

namespace argos {

   class CEntityDecorator : public CEntity {

   protected:

      CEntity* m_cOriginalEntity;

   public:

      CEntityDecorator(CEntity* pc_original_entity) :
         m_pcOriginalEntity(pc_original_entity) {}

      ~CEntityDecorator() {
         delete m_pcOriginalEntity;
      }

      inline virtual void Init(TConfigurationNode& t_tree) {
         m_cOriginalEntity->Init(t_tree);
      }

      inline virtual void Reset() {
         m_cOriginalEntity->Reset();
      }

      inline virtual void Destroy() {
         m_cOriginalEntity->Destroy();
      }

      inline virtual void AddPhysicsEngineEntity(const std::string& str_id,
                                                 CPhysicsEngineEntity& c_physics_entity) {
         m_cOriginalEntity->AddPhysicsEngineEntity(str_id, c_physics_entity);
      }

      inline virtual const CPhysicsEngineEntity& GetPhysicsEngineEntity(const std::string& str_id) const {
         return m_cOriginalEntity->GetPhysicsEngineEntity(str_id);
      }

      inline virtual const CVector3& GetPosition() const {
         return m_cOriginalEntity->GetPosition();
      }

      inline virtual const CVector3& GetInitPosition() const {
         return m_cOriginalEntity->GetInitPosition();
      }

      inline virtual void SetPosition(const CVector3& c_position) {
         m_cOriginalEntity->SetPosition(c_position);
      }

      inline virtual void SetInitPosition(const CVector3& c_position) {
         m_cOriginalEntity->SetInitPosition(c_position);
      }

      inline virtual const CQuaternion& GetOrientation() const {
         return m_cOriginalEntity->GetOrientation();
      }

      inline virtual const CQuaternion& GetInitOrientation() const {
         return m_cOriginalEntity->GetInitOrientation();
      }

      inline virtual void SetOrientation(const CQuaternion c_orientation) {
         m_cOriginalEntity->SetOrientation(c_orientation);
      }

      inline virtual void SetInitOrientation(const CQuaternion c_orientation) {
         m_cOriginalEntity->SetInitOrientation(c_orientation);
      }

      inline virtual const std::string& GetId() const {
         return m_cOriginalEntity->GetId();
      }

      inline virtual void SetId(const std::string& str_id) {
         m_cOriginalEntity->SetId(str_id);
      }

      inline virtual void AddPhysicsEngine(CPhysicsEngine& c_physics_engine) {
         m_cOriginalEntity->AddPhysicsEngine(c_physics_engine);
      }

      inline virtual CPhysicsEngine& GetPhysicsEngine(UInt32 un_index) const {
         return m_cOriginalEntity->GetPhysicsEngine(un_index);
      }

      inline virtual UInt32 GetPhysicsEngineNum() const {
         return m_cOriginalEntity->GetPhysicsEngineNum();
      }

      inline virtual bool CheckOcclusion(const CRay& c_ray,
                                         Real f_distance) const {
         return m_cOriginalEntity->CheckOcclusion(c_ray, f_distance);
      }

      inline virtual SInt8 MoveTo(const CVector3& c_position,
                                  const CQuaternion& c_orientation,
                                  bool b_check_only) {
         return m_cOriginalEntity->CheckOcclusion(c_position,
                                                  c_orientation,
                                                  b_check_only);
      }

      inline virtual bool IsCollisionDetected() const {
         return m_cOriginalEntity->IsCollisionDetected();
      }

      inline virtual void SetCollisionDetected() {
         m_cOriginalEntity->SetCollisionDetected();
      }

      inline virtual void ResetCollisionDetected() {
         m_cOriginalEntity->ResetCollisionDetected();
      }

      inline virtual UInt32 GetCollisionNumber() {
         return m_cOriginalEntity->GetCollisionNumber();
      }

      inline virtual void SetCollisionNumber(UInt32 un_collisions) {
         m_cOriginalEntity->SetCollisionNumber(un_collisions);
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return m_cOriginalEntity->GetTypeDescription();
      }

      inline virtual bool IsStretchable() const {
         return m_cOriginalEntity->IsStretchable();
      }

      inline virtual Real GetBoundingSphereRadius() const {
         return m_cOriginalEntity->GetBoundingSphereRadius();
      }

   };

}

#endif

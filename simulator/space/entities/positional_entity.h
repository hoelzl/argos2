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
 * @file <argos2/simulator/space/entities/positional_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef POSITIONAL_ENTITY_H
#define POSITIONAL_ENTITY_H

namespace argos {
   class CPositionalEntity;
}

#include <argos2/simulator/space/entities/entity.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/common/utility/math/quaternion.h>

namespace argos {
   class CPositionalEntity : public CEntity {

   public:

      CPositionalEntity(CEntity* pc_parent) :
         CEntity(pc_parent) {}
      virtual ~CPositionalEntity() {}

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();

      inline virtual const CVector3& GetPosition() const {
         return m_cPosition;
      }

      inline virtual const CVector3& GetInitPosition() const {
         return m_cInitPosition;
      }

      inline virtual void SetPosition(const CVector3& c_position) {
         m_cPosition = c_position;
      }

      inline virtual void SetInitPosition(const CVector3& c_position) {
         m_cInitPosition = c_position;
      }

      inline virtual const CQuaternion& GetOrientation() const {
         return m_cOrientation;
      }

      inline virtual const CQuaternion& GetInitOrientation() const {
         return m_cInitOrientation;
      }

      inline virtual void SetOrientation(const CQuaternion c_orientation) {
         m_cOrientation = c_orientation;
      }

      inline virtual void SetInitOrientation(const CQuaternion c_orientation) {
         m_cInitOrientation = c_orientation;
      }

      virtual bool MoveTo(const CVector3& c_position,
                          const CQuaternion& c_orientation,
                          bool b_check_only = false);

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "positional_entity";
      }

   private:
      
      CVector3 m_cPosition;
      CVector3 m_cInitPosition;
      CQuaternion m_cOrientation;
      CQuaternion m_cInitOrientation;

   };
}

#endif

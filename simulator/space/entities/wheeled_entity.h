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
 * @file <argos2/simulator/space/entities/wheeled_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef WHEELED_ENTITY_H
#define WHEELED_ENTITY_H

#include <argos2/simulator/space/entities/entity.h>
#include <argos2/common/utility/math/vector3.h>

namespace argos {

   template <SInt32 NUM_WHEELS> class CWheeledEntity : public CEntity {

   public:

      CWheeledEntity(CEntity* pc_parent) :
         CEntity(pc_parent) {
         ::bzero(m_cWheelSpeed, NUM_WHEELS * sizeof(Real));
      }
      virtual ~CWheeledEntity() {}

      virtual void Reset() {
         /* Reset speeds */
         ::bzero(m_cWheelSpeed, NUM_WHEELS * sizeof(Real));
      }

      inline virtual void GetSpeed(Real* f_speed) {
         ::memcpy(f_speed, m_cWheelSpeed, NUM_WHEELS * sizeof(Real));
      }

      inline virtual void SetSpeed(Real f_speed[NUM_WHEELS]) {
         ::memcpy(m_cWheelSpeed, f_speed, NUM_WHEELS * sizeof(Real));
      }

      inline virtual const CVector3& GetWheelPosition(UInt32 un_index) const {
         return m_cWheelPosition[un_index];
      }

      inline virtual void SetWheelPosition(UInt32 un_index,
                                           const CVector3& c_position) {
         m_cWheelPosition[un_index] = c_position;
      }

      inline virtual std::string GetTypeDescription() const {
         return "wheeled_entity<" + ToString(NUM_WHEELS) +">";
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
          visitor.Visit(*this);
      }

   private:

      CVector3 m_cWheelPosition[NUM_WHEELS];
      Real m_cWheelSpeed[NUM_WHEELS];

   };

   /****************************************/
   /****************************************/

   /*
    * This specialization is to optimize the case of robots with two wheels
    * (e.g., foot-bot, s-bot and e-puck)
    */
   template <> class CWheeledEntity<2> : public CEntity {

   public:

      CWheeledEntity(CEntity* pc_parent) :
         CEntity(pc_parent) {
         m_cWheelSpeed[0] = 0.0f;
         m_cWheelSpeed[1] = 0.0f;
      }
      virtual ~CWheeledEntity() {}

      virtual void Reset() {
         /* Reset speeds */
         m_cWheelSpeed[0] = 0.0f;
         m_cWheelSpeed[1] = 0.0f;
      }

      inline virtual void GetSpeed(Real* f_speed) {
         f_speed[0] = m_cWheelSpeed[0];
         f_speed[1] = m_cWheelSpeed[1];
      }

      inline virtual void SetSpeed(Real f_speed[2]) {
         m_cWheelSpeed[0] = f_speed[0];
         m_cWheelSpeed[1] = f_speed[1];
      }

      inline virtual const CVector3& GetWheelPosition(UInt32 un_index) const {
         return m_cWheelPosition[un_index];
      }

      inline virtual void SetWheelPosition(UInt32 un_index,
                                           const CVector3& c_position) {
         m_cWheelPosition[un_index] = c_position;
      }

      inline virtual std::string GetTypeDescription() const {
         return "wheeled_entity<2>";
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
          visitor.Visit(*this);
      }

   private:

      CVector3 m_cWheelPosition[2];
      Real m_cWheelSpeed[2];

   };

}

#endif

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
 * @file <argos2/simulator/space/entities/floor_entity.h>
 *
 * @author Carlo Pinciroli - <cpinciroli@ulb.ac.be>
 */

#ifndef FLOOR_ENTITY_H
#define FLOOR_ENTITY_H

namespace argos {
   class CFloorEntity;
}

#include <argos2/simulator/space/entities/entity.h>
#include <argos2/common/utility/math/vector2.h>
#include <argos2/common/utility/math/vector3.h>
#include <argos2/common/utility/datatypes/color.h>

namespace argos {

   class CFloorEntity : public CEntity {

   public:

      class CFloorColorSource {

      public:
	 virtual ~CFloorColorSource() {}
         virtual CColor GetColorAtPoint(Real f_x,
                                        Real f_y) = 0;

         virtual void SaveAsImage(const std::string& str_path) = 0;

      };

   public:

      CFloorEntity();
      virtual ~CFloorEntity();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();

      inline CColor GetColorAtPoint(Real f_x,
                                    Real f_y) {
         ARGOS_ASSERT(m_pcColorSource != NULL,
                      "The floor entity \"" <<
                      GetId() <<
                      "\" has no associated color source.");
         return m_pcColorSource->GetColorAtPoint(f_x, f_y);
      }

      inline bool HasChanged() const {
         return m_bHasChanged;
      }

      inline void SetChanged() {
         m_bHasChanged = true;
      }

      inline void ClearChanged() {
         m_bHasChanged = false;
      }

      inline void SaveAsImage(const std::string& str_path) {
         m_pcColorSource->SaveAsImage(str_path);
      }

      inline virtual void Accept(CEntityVisitor& visitor) {
         visitor.Visit(*this);
      }

      inline virtual std::string GetTypeDescription() const {
         return "floor_entity";
      }

   private:

      CFloorColorSource* m_pcColorSource;
      CVector3           m_cFloorSize;
      std::string        m_strColorSource;
      unsigned int       m_unPixelsPerMeter;
      bool               m_bHasChanged;
   };
}

#endif

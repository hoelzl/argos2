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
 * @file <common/configuration/memento.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef MEMENTO_H
#define MEMENTO_H

namespace argos {
   class CMemento;
}

#include <argos2/common/utility/datatypes/byte_array.h>

namespace argos {

   class CMemento {

   public:

      virtual ~CMemento() {}
      virtual void SaveState(CByteArray& c_buffer) = 0;
      virtual void LoadState(CByteArray& c_buffer) = 0;

   };

}

#endif

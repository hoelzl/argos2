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
 * @file <argos2/simulator/space/space_no_threads.h>
 *
 * @brief This file provides the definition of the Swarmanoid 3D Space.
 *
 * This file provides the definition of the Swarmanoid 3D Space.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef SPACE_NO_THREADS_H
#define SPACE_NO_THREADS_H

namespace argos {
   class CSpace;
}

#include <argos2/simulator/space/space.h>

namespace argos {

   class CSpaceNoThreads : public CSpace {

   public:

      CSpaceNoThreads() {}
      virtual ~CSpaceNoThreads() {}

      virtual void UpdateControllableEntities();
      virtual void UpdatePhysics();

   };

}

#endif

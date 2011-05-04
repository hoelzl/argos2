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
 * @file <argos2/simulator/space/space_hash_tr1.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef SPACE_HASH_TR1_H
#define SPACE_HASH_TR1_H

namespace argos {
   class CSpace;
   class CVector3;
   class CRay;
}

#include <argos2/simulator/space/space_hash.h>
#include <tr1/unordered_map>
#include <iterator>
#include <algorithm>

namespace argos {

   /****************************************/
   /****************************************/

   static const UInt32 SPACE_HASH_TR1_PRIME_FOR_X = 73856093u;
   static const UInt32 SPACE_HASH_TR1_PRIME_FOR_Y = 19349663u;
   static const UInt32 SPACE_HASH_TR1_PRIME_FOR_Z = 83492791u;

   /****************************************/
   /****************************************/

   template <class Element, class Updater> class CSpaceHashTR1 : public CSpaceHash<Element,Updater> {

   public:

      struct SCell {
         UInt64 StoreTimestamp;
         typename CSpaceHash<Element,Updater>::TElementList Elements;

         SCell(UInt32 un_store_timestamp = 0) :
            StoreTimestamp(un_store_timestamp) {}
      };

      typedef std::tr1::unordered_map<UInt32, SCell> TSpaceHashTable;
      typedef typename TSpaceHashTable::iterator iterator;
      typedef typename TSpaceHashTable::const_iterator const_iterator;

   public:

      CSpaceHashTR1() :
         m_unCurrentStoreTimestamp(0) {}

      virtual ~CSpaceHashTR1() {}

      inline virtual void Update() {
         /* Set the current store time stamp */
         m_unCurrentStoreTimestamp++;
         /* Call base class method */
         CSpaceHash<Element,Updater>::Update();
      }

      inline virtual void UpdateCell(SInt32 n_i,
                             SInt32 n_j,
                             SInt32 n_k,
                             Element& c_element) {
         /* Calculate the hash of the current position */
         SInt32 nHash = CSpaceHash<Element,Updater>::CoordinateHash(n_i, n_j, n_k);
         /* Get a reference to the cell */
         SCell& sCell = m_tSpaceHashTable[nHash];
         /* Check if the cell's content is obsolete */
         if(sCell.StoreTimestamp == m_unCurrentStoreTimestamp) {
            /* Add the current element to the cell */
            sCell.Elements.insert(&c_element);
         }
         else {
            /* The cell's content is obsolete, erase it */
            sCell.Elements.clear();
            /* Set the store timestamp to the current time */
            sCell.StoreTimestamp = m_unCurrentStoreTimestamp;
            /* Add the current element to the cell */
            sCell.Elements.insert(&c_element);
         }
      }

      inline virtual bool CheckCell(SInt32 n_i,
                                    SInt32 n_j,
                                    SInt32 n_k,
                                    typename CSpaceHash<Element,Updater>::TElementList& t_elements) {
         /* In the beginning, no new elements have been found */
         bool bNewElements = false;
         /* Look for the cell at the wanted coordinates */
         typename TSpaceHashTable::iterator itCell =
            m_tSpaceHashTable.find(
               CSpaceHash<Element,Updater>::CoordinateHash(n_i, n_j, n_k));
         /* Visit the cell IF:
            1. the cell has been found AND
            2. its data is up-to-date AND
            3. it is not empty
          */
         if((itCell != m_tSpaceHashTable.end()) && /* 1. */
            (itCell->second.StoreTimestamp == m_unCurrentStoreTimestamp) && /* 2. */
            !itCell->second.Elements.empty()) /* 3. */ {
            /* New elements to add to the list */
            bNewElements = true;
            /* Add the cell's elements to the list */
            t_elements.insert(itCell->second.Elements.begin(),
                              itCell->second.Elements.end());
         }
         return bNewElements;
      }

   private:

      UInt64 m_unCurrentStoreTimestamp;
      TSpaceHashTable m_tSpaceHashTable;
   };

}

#endif

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
 * @file <argos2/common/utility/datatypes/byte_array.h>
 *
 * @brief This file provides
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H

#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/common/utility/configuration/argos_exception.h>
#include <vector>
#include <iterator>

namespace argos {

   class CByteArray {

   public:

      CByteArray() {}

      CByteArray(const CByteArray& c_byte_array) :
         m_vecBuffer(c_byte_array.m_vecBuffer) {}

      CByteArray(const UInt8* pun_buffer,
                 size_t un_size);

      inline size_t Size() const {
         return m_vecBuffer.size();
      }

      inline bool Empty() const {
         return m_vecBuffer.empty();
      }

      inline CByteArray& operator=(const CByteArray& c_byte_array) {
         if(this != &c_byte_array) {
            m_vecBuffer = c_byte_array.m_vecBuffer;
         }
         return *this;
      }

      inline UInt8& operator[](size_t un_index) {
         if(un_index >= Size()) THROW_ARGOSEXCEPTION("CByteArray: index out of bounds [index = " << un_index << ", size=" << Size() << "]");
         return m_vecBuffer.at(un_index);
      }

      inline UInt8 operator[](size_t un_index) const {
         if(un_index >= Size()) THROW_ARGOSEXCEPTION("CByteArray: index out of bounds [index = " << un_index << ", size=" << Size() << "]");
         return m_vecBuffer.at(un_index);
      }

      CByteArray& AddBuffer(const UInt8* pun_buffer,
                            size_t un_size);

      CByteArray& FetchBuffer(UInt8* pun_buffer,
                              size_t un_size);

      CByteArray& operator<<(UInt8 un_value);
      CByteArray& operator>>(UInt8& un_value);
      CByteArray& operator<<(SInt8 n_value);
      CByteArray& operator>>(SInt8& n_value);
      CByteArray& operator<<(UInt16 un_value);
      CByteArray& operator>>(UInt16& un_value);
      CByteArray& operator<<(SInt16 n_value);
      CByteArray& operator>>(SInt16& n_value);
      CByteArray& operator<<(UInt32 un_value);
      CByteArray& operator>>(UInt32& un_value);
      CByteArray& operator<<(SInt32 un_value);
      CByteArray& operator>>(SInt32& un_value);
      CByteArray& operator<<(UInt64 un_value);
      CByteArray& operator>>(UInt64& un_value);
      CByteArray& operator<<(SInt64 un_value);
      CByteArray& operator>>(SInt64& un_value);
      CByteArray& operator<<(unsigned long int un_value);
      CByteArray& operator>>(unsigned long int& un_value);
      CByteArray& operator<<(signed long int n_value);
      CByteArray& operator>>(signed long int& n_value);
      CByteArray& operator<<(Real un_value);
      CByteArray& operator>>(Real& un_value);
      CByteArray& operator<<(const std::string& str_value);
      CByteArray& operator>>(std::string& str_value);

      friend std::ostream& operator<<(std::ostream& c_os, const CByteArray& c_byte_array);

   private:

      std::vector<UInt8> m_vecBuffer;

   };

}

#endif

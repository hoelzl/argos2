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
 * @file <common/control_interface/footbot/ci_footbot_rfid_sensor.h>
 *
 * @brief This file provides the definition of the RFID sensor.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CCI_FOOTBOTRFIDSENSOR_H
#define CCI_FOOTBOTRFIDSENSOR_H

/* To avoid dependency problems when including */
namespace argos {

   class CCI_FootBotRFIDSensor;

};

#include <argos2/common/control_interface/ci_sensor.h>



namespace argos {

   class CCI_FootBotRFIDSensor: public CCI_Sensor {

   public:

      struct TRFIDTag {
         long long id;        // RFID tag unique identifier (64 bit)
         int signal_strength; // received signal strength [0:31]
         int block_size;      // the size of block in bytes
         int block_count;     // the number of blocks

         TRFIDTag()
            : id(0),
              signal_strength(0),
              block_size(0),
              block_count(0) {}

         friend ostream& operator<<(ostream& os, const TRFIDTag& r) {
            os << "RFID< "
               << "id="              << r.id              << ", "
               << "signal_strength=" << r.signal_strength << ", "
               << "block_size="      << r.block_size << ", "
               << "block_count="     << r.block_count
               << " >";
            return os;
         }
      };

      struct TRFIDData {
         long long id;
         unsigned char* data;
         size_t size;

         TRFIDData() : id(0), data(NULL), size(0) {}

         friend ostream& operator<<(ostream& os, const TRFIDData& r) {
            os << "RFID-READ< "
               << "id=" << r.id << ", data='";
            for( unsigned int i = 0; i < r.size; i++ ) os << static_cast<short>(r.data[i]);
            os << "' >";
            return os;
         }
      };

      typedef map<long long, TRFIDTag> TRFIDTags;

   public:

      CCI_FootBotRFIDSensor() {}
      virtual ~CCI_FootBotRFIDSensor() {}

      // TODO unclear what to return, the conversion to Real is tricky
      virtual inline unsigned int GetNumberOfReadings() const { return 0; }

      // TODO unclear what to return, the conversion to Real is tricky
      virtual const Real* GetAllReadings(Real* pf_buffer = NULL) { return pf_buffer; }

      // Performs an RFID scan to discover tags
      virtual void PerformScan() = 0;

      // true if we are on an RFID tag
      inline virtual bool AmIonTag() { return m_tTagsFound.size() > 0; }

      // returns the list of RFID tags found
      virtual inline void FoundTags(TRFIDTags& t_tags_found) { t_tags_found = m_tTagsFound; }

      // performs a read operation on the RFID tag
      virtual inline void GetReading(TRFIDData& t_rfid_data) = 0;

   protected:

      TRFIDTags m_tTagsFound;

   };

};

#endif

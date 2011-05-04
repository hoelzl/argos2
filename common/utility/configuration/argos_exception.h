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
 * @file <common/configuration/argos_exception.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef ARGOS_EXCEPTION_H
#define ARGOS_EXCEPTION_H

namespace argos {
   class CARGoSException;
}

#include <stdexcept>
#include <sstream>

namespace argos {

   class CARGoSException : public std::exception {

   public:

      CARGoSException(const std::string& str_what, std::exception* c_nested = NULL) throw() :
         m_strWhat("CARGoSException thrown: " + str_what), m_cNested(c_nested) {
         if (m_cNested != NULL) {
            std::ostringstream w;
            w << m_strWhat << " [nested: \"" << m_cNested->what() << "\"]";
            m_strWhat = w.str();
         }
      }
      virtual ~CARGoSException() throw() {
      }

      virtual const char* what() const throw() {
         return m_strWhat.c_str();
      }

   private:

      std::string m_strWhat;
      std::exception* m_cNested;

   };

}

#define THROW_ARGOSEXCEPTION(message) { std::ostringstream what; what << __FILE__ << ":" << __LINE__ << std::endl << "        " << message; throw CARGoSException(what.str()); }
#define THROW_ARGOSEXCEPTION_NESTED(message, nested) { std::ostringstream what; what << __FILE__ << ":" << __LINE__ << std::endl << "        " << message; throw CARGoSException(what.str(), &nested); }

#ifndef NDEBUG
#define ARGOS_ASSERT(condition, message) { if ( !(condition) ) THROW_ARGOSEXCEPTION(message); }
#else
#define ARGOS_ASSERT(condition, message)
#endif

#endif

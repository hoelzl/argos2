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
 * @file <common/utility_classes/string_utilities.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef STRING_UTILITIES_H
#define STRING_UTILITIES_H

#include <argos2/common/utility/configuration/argos_exception.h>
#include <argos2/common/utility/datatypes/datatypes.h>
#include <string>
#include <vector>
#include <sstream>

namespace argos {

   /****************************************/
   /****************************************/

   template<typename T> std::string ToString(const T& t_value) {
      std::ostringstream ss;
      ss << t_value;
      return ss.str();
   }

   /****************************************/
   /****************************************/

   template<typename T> T FromString(const std::string& t_value) {
      T tReturnValue;
      std::istringstream ss(t_value);
      ss >> tReturnValue;
      return tReturnValue;
   }

   /****************************************/
   /****************************************/

   template<typename T> void ParseValues(std::istream& str_input,
                                         UInt32 un_num_fields,
                                         T* pt_field_buffer,
                                         const char ch_delimiter = '\n') {
      std::string s[un_num_fields];
      UInt32 i = 0;
      while(i < un_num_fields && std::getline(str_input, s[i], ch_delimiter)) {
         i++;
      }
      if (i == un_num_fields) {
         str_input.clear(); // the istream was read completely and this is fine, so set the flag to 'good'
         for(i = 0; i < un_num_fields; i++) {
            std::istringstream iss(s[i]);
            iss >> pt_field_buffer[i];
         }
      }
      else {
         THROW_ARGOSEXCEPTION("Parse error: expected " << un_num_fields
                              << " values, but " << i << " have been found in \""
                              << str_input << "\"");
      }
   }

   /****************************************/
   /****************************************/

   template<typename T> void ParseValues(const std::string& str_input,
                                         const UInt32 un_num_fields,
                                         T* pt_field_buffer,
                                         const char ch_delimiter = '\n') {
      std::istringstream issInput(str_input);
      ParseValues(issInput, un_num_fields, pt_field_buffer, ch_delimiter);
   }

   /****************************************/
   /****************************************/

   extern "C" {

      /**
       * @brief Tokenizes the given string according to the wanted delimiters (by default just a " ").
       *
       * @param s_str The string to tokenize.
       * @param vec_tokens The vector to fill with tokens.
       * @param s_deimiters The delimiters to use.
       */
      void Tokenize(const std::string& str_string,
                    std::vector<std::string>& vec_tokens,
                    const std::string& str_delimiters = " ");

      /**
       * @brief Converts a string to upper case.
       *
       * @param s_str The string to convert.
       * @return The upper case string.
       */
      std::string StringToUpperCase(const std::string& str_string);

      /**
       * @brief Converts a string to lower case.
       *
       * @param s_str The string to convert.
       * @return The lower case string.
       */
      std::string StringToLowerCase(const std::string& str_string);

      /**
       * @brief Parses a range specified as [x:y], where x and y are the
       * range lower and upper limits
       *
       * @param s_range the string to be parsed
       * @ param s_low_lim the range lower limit
       * @p aram s_upp_lim the range upper limit
       * @re turn 0 if no errors occurred, -1 otherwise.
       */
      SInt8 ParseRange(const std::string& s_range,
                       std::string& s_low_lim,
                       std::string& s_upp_lim);

      /****************************************/
      /****************************************/

      std::string ExpandARGoSInstallDir(const std::string& str_buffer);

      /****************************************/
      /****************************************/

      void Replace(std::string& str_buffer,
                   const std::string& str_original,
                   const std::string& str_new);

      /****************************************/
      /****************************************/

      bool MatchPattern(const std::string& str_input,
                        const std::string str_pattern);

      /****************************************/
      /****************************************/

   }

}

#endif

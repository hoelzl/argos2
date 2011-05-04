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
 * @file <common/configuration/argos_configuration.h>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef ARGOS_CONFIGURATION_H
#define ARGOS_CONFIGURATION_H

#include <argos2/common/utility/datatypes/datatypes.h>
#include <argos2/common/utility/configuration/argos_exception.h>
#include <argos2/common/utility/tinyxml-cpp/ticpp.h>
#include <string>

namespace argos {

   /****************************************/
   /****************************************/

   typedef ticpp::Element TConfigurationNode;
   typedef ticpp::Iterator <ticpp::Element> TConfigurationNodeIterator;

   /****************************************/
   /****************************************/

   inline bool NodeExists(TConfigurationNode& t_node,
                          const std::string& str_tag) {
      TConfigurationNodeIterator it(str_tag);
      it = it.begin(&t_node);
      return it != NULL;
   }

   /****************************************/
   /****************************************/

   inline TConfigurationNode& GetNode(TConfigurationNode& t_node,
                                      const std::string& str_tag) {
      try {
         TConfigurationNodeIterator it(str_tag);
         it = it.begin(&t_node);
         if(it == NULL) {
            THROW_ARGOSEXCEPTION("Node '" << str_tag << "' not found");
         }
         return *it;
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error searching for '" << str_tag << "' ", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline void AddChildNode(TConfigurationNode& t_parent_node,
                            TConfigurationNode& t_child_node) {
      try {
         t_parent_node.InsertEndChild(t_child_node);
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error inserting node '" << t_child_node << "' into node '" << t_parent_node << "'", ex);
      }      
   }

   /****************************************/
   /****************************************/

   template <typename T> void GetNodeText(TConfigurationNode& t_node,
                                          T& t_buffer) {
      try {
         t_node.GetText(&t_buffer);
      }
      catch(std::exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Parse error", ex);
      }
   }

   /****************************************/
   /****************************************/

   template <typename T> void GetNodeTextOrDefault(TConfigurationNode& t_node,
                                                   T& t_buffer,
                                                   const T& t_default) {
      try {
         t_node.GetTextOrDefault(&t_buffer, t_default);
      }
      catch(std::exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Parse error", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline bool NodeAttributeExists(TConfigurationNode& t_node,
                                   const std::string& str_attribute) {
      return t_node.HasAttribute(str_attribute);
   }

   /****************************************/
   /****************************************/

   inline void GetNodeAttribute(TConfigurationNode& t_node,
                                const std::string& str_attribute,
                                bool& b_buffer) {
      std::string strBuffer;
      try {
         t_node.GetAttribute(str_attribute, &strBuffer, true);
         if(strBuffer == "true") {
            b_buffer = true;
         }
         else if(strBuffer == "false") {
            b_buffer = false;
         }
         else {
            THROW_ARGOSEXCEPTION("Cannot convert '" << strBuffer << "' into a bool. Accepted values: 'true', 'false'.");
         }
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline void GetNodeAttribute(TConfigurationNode& t_node,
                                const std::string& str_attribute,
                                UInt8& un_buffer) {
      try {
         UInt32 unTmpBuffer;
         t_node.GetAttribute(str_attribute, &unTmpBuffer, true);
         un_buffer = unTmpBuffer;
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline void GetNodeAttribute(TConfigurationNode& t_node,
                                const std::string& str_attribute,
                                SInt8& n_buffer) {
      try {
         SInt32 nTmpBuffer;
         t_node.GetAttribute(str_attribute, &nTmpBuffer, true);
         n_buffer = nTmpBuffer;
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   template <typename T> void GetNodeAttribute(TConfigurationNode& t_node,
                                               const std::string& str_attribute,
                                               T& t_buffer) {
      try {
         t_node.GetAttribute(str_attribute, &t_buffer, true);
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline void GetNodeAttributeOrDefault(TConfigurationNode& t_node,
                                         const std::string& str_attribute,
                                         bool& b_buffer,
                                         const bool b_default) {
      std::string strBuffer;
      const std::string strDefault = (b_default ? "true" : "false");
      try {
         t_node.GetAttributeOrDefault(str_attribute, &strBuffer, strDefault);
         if(strBuffer == "true") {
            b_buffer = true;
         }
         else if(strBuffer == "false") {
            b_buffer = false;
         }
         else {
            THROW_ARGOSEXCEPTION("Cannot convert '" << strBuffer << "' into a bool. Accepted values: 'true', 'false'.");
         }
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline void GetNodeAttributeOrDefault(TConfigurationNode& t_node,
                                         const std::string& str_attribute,
                                         UInt8& un_buffer) {
      try {
         UInt32 unTmpBuffer;
         t_node.GetAttributeOrDefault(str_attribute, &unTmpBuffer, true);
         un_buffer = unTmpBuffer;
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline void GetNodeAttributeOrDefault(TConfigurationNode& t_node,
                                         const std::string& str_attribute,
                                         SInt8& n_buffer) {
      try {
         SInt32 nTmpBuffer;
         t_node.GetAttributeOrDefault(str_attribute, &nTmpBuffer, true);
         n_buffer = nTmpBuffer;
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   template <typename T> void GetNodeAttributeOrDefault(TConfigurationNode& t_node,
                                                        const std::string& str_attribute,
                                                        T& t_buffer,
                                                        const T& t_default) {
      try {
         t_node.GetAttributeOrDefault(str_attribute, &t_buffer, t_default);
      }
      catch(ticpp::Exception& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error parsing attribute \"" << str_attribute << "\"", ex);
      }
   }

   /****************************************/
   /****************************************/

   inline void SetNodeAttribute(TConfigurationNode& t_node,
                                const std::string& str_attribute,
                                bool b_value) {
      if(b_value) {
         t_node.SetAttribute(str_attribute, "true");
      }
      else {
         t_node.SetAttribute(str_attribute, "false");
      }
   }

   /****************************************/
   /****************************************/

   template <typename T> void SetNodeAttribute(TConfigurationNode& t_node,
                                               const std::string& str_attribute,
                                               const T& t_value) {
      t_node.SetAttribute(str_attribute, t_value);
   }

   /****************************************/
   /****************************************/

}

#endif

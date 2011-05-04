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
 * This file comes from an external source and has been copied inside the ARGoS project.
 *
 * See http://iridia-dev.ulb.ac.be/projects/argos/trac/wiki/ExternalCode for rules about
 * copying code from external sources and a listing of all code from external sources
 * inside ARGoS.
 *
 * Description: This file provides the implementation of the 'any' type.
 * Source: http://www.boost.org/libs/any
 * Date: 23/10/2009
 * Copied from: Manuele Brambilla <mbrambilla@iridia.ulb.ac.be>
 * License: Boost Software License, Version 1.0
 */

/**
 * Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/**
 * @file <common/utility_classes/swarmanoid_datatypes/any.h>
 *
 * @brief This file provides the implementation of the 'any' type.
 * It's a copy almost one to one of the boost::any type. The main difference is the removal of exceptions and a semplification of the cast via reference mechanism.
 * See http://www.boost.org/libs/any for Documentation on the original file.
 *
 * @author Manuele Brambilla <mbrambilla@iridia.ulb.ac.be>
 */

#ifndef SWARMANOIDANY_H
#define SWARMANOIDANY_H

#include <cxxabi.h>
#include <algorithm>
#include <typeinfo>

#include <argos2/common/utility/logging/argos_log.h>

namespace argos
{

    /** This class manages "any" type. Functions for various kind of casting and manipulators are defined.
    */

    class any
    {
    public:

        any()
          : content(0)
        {
        }

        template<typename ValueType>
        any(const ValueType & value)
          : content(new holder<ValueType>(value))
        {
        }

        /** Clone the argument if it is not NULL
        */
        any(const any & other)
          : content(other.content ? other.content->clone() : 0)
        {
        }

        ~any()
        {
            delete content;
        }

    public: // modifiers

        /** Redefinition of the "swap" function from the std lib
        * @param rhs the variable to swap
        */
        any & swap(any & rhs)
        {
            std::swap(content, rhs.content);
            return *this;
        }

        /** Redefinition of the "=" operator with a template parameter
        * @param rhs the variable to assign
        */
        template<typename ValueType>
        any & operator=(const ValueType & rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

        /** Redefinition of the "=" operator with any
        * @param rhs the variable to assign
        */
        any & operator=(const any & rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

    public: // queries

        /** Test if empty
        */
        bool empty() const
        {
            return !content;
        }

        /** Return the type of the variable. It is used mainly for casting
        */
        const std::type_info & type() const
        {
            return content ? content->type() : typeid(void);
        }

    public: // types

        /** Abstract class for the content held
        */
        class placeholder
        {
        public: // structors

            virtual ~placeholder()
            {
            }

        public: // queries

            virtual const std::type_info & type() const = 0;

            virtual placeholder * clone() const = 0;

        };

        /** Implementation of the placeholder abstract class
        */
        template<typename ValueType>
        class holder : public placeholder
        {
        public: // structors

            holder(const ValueType & value)
              : held(value)
            {
            }

        public: // queries

            /** Return the type of the variable. It is used mainly for casting
            */
            virtual const std::type_info & type() const
            {
                return typeid(ValueType);
            }

            /** Clone the object
            */
            virtual placeholder * clone() const
            {
                return new holder(held);
            }

        public: // representation

            ValueType held;  /**< The variable held */

        };


    public: // representation

        placeholder * content;  /**< A pointer to the internal content of the variable */

    };

    /** Check if the argument is Null, if not it returns the variable casted to the selected template
    * If the variable is not of the type in the template, it returns 0
    * @param operand A pointer to variable to be casted
    */
    template<typename ValueType>
    ValueType * any_cast(any * operand)
    {
       char* operand_demangled = abi::__cxa_demangle(operand->type().name(), NULL, NULL, NULL);
       char* any_demangled = abi::__cxa_demangle(typeid(ValueType).name(), NULL, NULL, NULL);
       free(operand_demangled);
       free(any_demangled);
        return operand && operand->type() == typeid(ValueType)
            ? &static_cast<any::holder<ValueType> *>(operand->content)->held
            : 0;
    }

    /** Check if the argument is Null, if not it returns the variable casted to the selected template
    * If the variable is not of the type in the template, it returns 0
    * @param operand A pointer to the const variable to be casted
    */
    template<typename ValueType>
    const ValueType * any_cast(const any * operand)
    {
      return any_cast<ValueType>(const_cast<any *>(operand)); /**< Performs a const_cast and then calls the equivalent function */
    }

    /** Check if the argument is Null, if not it returns the variable casted to the selected template
    * If the variable is not of the type in the template, it returns 0
    * @param operand The const variable to be casted
    */
    template<typename ValueType>
    ValueType any_cast(const any & operand)
    {
      const ValueType * result = any_cast<ValueType>(&operand); /**< Calls the equivalent function with the pointer */
      if (!result)
        DEBUG_SIMULATOR("Failed conversion using swarmanoid::any_cast (common/utility_classes/swarmanoid_datatypes/any.h)");
      return *result;
    }

    /** Check if the argument is Null, if not it returns the variable casted to the selected template
    * If the variable is not of the type in the template, it returns 0
    * @param operand The variable to be casted
    */
    template<typename ValueType>
    ValueType any_cast(any & operand)
    {

      ValueType * result = any_cast<ValueType>(&operand);  /**< Calls the equivalent function with the pointer */
      if (!result)
        DEBUG_SIMULATOR("Failed conversion using swarmanoid::any_cast (common/utility_classes/swarmanoid_datatypes/any.h)");
      return *result;
    }

}

#endif

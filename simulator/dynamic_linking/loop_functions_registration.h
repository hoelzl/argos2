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

#ifndef LOOP_FUNCTIONS_REGISTRATION
#define LOOP_FUNCTIONS_REGISTRATION

namespace argos {
   class CLoopFunctions;
}

/* Definitions useful for dynamic linking of loop functions */

/* typedef to make it easier to set up controller factory */
typedef argos::CLoopFunctions *CLoopFunctions_Maker();

/* the actual controller factory */
extern std::map<std::string, CLoopFunctions_Maker *, std::less<std::string> > mapLoopFunctionFactory;

/* to add the controller to the factory */
#define REGISTER_LOOP_FUNCTIONS(class_name, label)                      \
   extern "C" {                                                         \
      CLoopFunctions* class_name ## _maker(){                           \
         return new class_name;                                         \
      }                                                                 \
                                                                        \
      class class_name ## _proxy {                                      \
      public:                                                           \
      class_name ## _proxy(){                                           \
         LOG << "[INFO] Registering loop function <" #class_name ", " label ">" << std::endl; \
         mapLoopFunctionFactory[ label ] = class_name ## _maker;        \
      }                                                                 \
      };                                                                \
      class_name ## _proxy class_name ## _p;                            \
   }

#endif

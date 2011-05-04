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
 * @file <common/control_interface/behavioral_toolkit/utility_classes/helper.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef HELPER_H
#define HELPER_H

#define GET_ALL_VALUES_HELPER(USED, TO_BUFFER, FROM_BUFFER, TYPE, SIZE) \
   if (USED) {                                                          \
      if( TO_BUFFER != NULL ) {                                         \
         ::memcpy(TO_BUFFER, FROM_BUFFER, sizeof(TYPE) * SIZE);         \
         return TO_BUFFER;                                              \
      }                                                                 \
      else {                                                            \
         return FROM_BUFFER;                                            \
      }                                                                 \
   }                                                                    \
   else {                                                               \
      return NULL;                                                      \
   }

#define SENSOR_INIT_HELPER(STRING_TYPE, CPP_TYPE, MEMBER_VAR, USING_VAR)        \
   itSensors = mapSensors.find(STRING_TYPE);                                    \
   if (itSensors != mapSensors.end()) {                                         \
      MEMBER_VAR = dynamic_cast<CPP_TYPE*>(m_pcRobot->GetSensor(STRING_TYPE));  \
      USING_VAR = true;                                                         \
   }

#define ACTUATOR_INIT_HELPER(STRING_TYPE, CPP_TYPE, MEMBER_VAR, USING_VAR)      \
   itActuators = mapActuators.find(STRING_TYPE);                                \
   if (itActuators != mapActuators.end()) {                                     \
      MEMBER_VAR = dynamic_cast<CPP_TYPE*>(m_pcRobot->GetActuator(STRING_TYPE));\
      USING_VAR = true;                                                         \
   }

#define SET_SENSOR_ACTIVATION_HELPER(TYPE, ACTIVATION)  \
   if (str_sensor == TYPE) {                            \
      ACTIVATION = b_status;                            \
      return;                                           \
   }

#define CHECK_IS_SENSOR_USED_HELPER(STRING_TYPE, USING_VAR, METHOD_NAME)                  \
   if (!USING_VAR) {                                                                      \
      THROW_ARGOSEXCEPTION("ERROR: method " << METHOD_NAME << " called, but the sensor `" \
      << STRING_TYPE << "` has not been declared in the XML configuration\n");            \
   }

#define CHECK_IS_ACTUATOR_USED_HELPER(STRING_TYPE, USING_VAR, METHOD_NAME)                  \
   if (!USING_VAR) {                                                                        \
      THROW_ARGOSEXCEPTION("ERROR: method " << METHOD_NAME << " called, but the actuator `" \
      << STRING_TYPE << "` has not been declared in the XML configuration\n");              \
   }

#endif

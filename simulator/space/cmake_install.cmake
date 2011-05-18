# Install script for directory: /Users/tc/Prog/Robots/argos2/simulator/space

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator/space" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/simulator/space/space.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/space_no_threads.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/space_multi_thread.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/space_hash_tr1.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/space_hash_native.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/space_hash.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator/space/entities" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/positional_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/embodied_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/composable_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/controllable_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/wheeled_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/led_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/led_equipped_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/gripper_equipped_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/distance_scanner_equipped_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/entity_decorator.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/box_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/cylinder_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/floor_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/footbot_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/epuck_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/eyebot_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/light_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/rab_equipped_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/medium_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/wifi_medium_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/space/entities/wifi_equipped_entity.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/space/Debug/libargos2_simulator_space.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/Debug/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/space/Release/libargos2_simulator_space.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/Release/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/space/MinSizeRel/libargos2_simulator_space.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/MinSizeRel/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/space/RelWithDebInfo/libargos2_simulator_space.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/RelWithDebInfo/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_space.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")


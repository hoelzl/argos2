# Install script for directory: /Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator/physics_engines/dynamics3d" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/dynamics3d_box.h"
    "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/dynamics3d_cylinder.h"
    "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/dynamics3d_eyebot.h"
    "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/dynamics3d_add_visitor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/dynamics3d_remove_visitor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/dynamics3d_entity.h"
    "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/dynamics3d_engine.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/Debug/libargos2_simulator_physics_engines_dynamics3d.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_physics_engines_dynamics3d.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/Release/libargos2_simulator_physics_engines_dynamics3d.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_physics_engines_dynamics3d.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/MinSizeRel/libargos2_simulator_physics_engines_dynamics3d.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_physics_engines_dynamics3d.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/RelWithDebInfo/libargos2_simulator_physics_engines_dynamics3d.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_physics_engines_dynamics3d.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_physics_engines_dynamics3d.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")


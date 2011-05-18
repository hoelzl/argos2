# Install script for directory: /Users/tc/Prog/Robots/argos2/simulator

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator" TYPE FILE FILES "/Users/tc/Prog/Robots/argos2/simulator/simulator.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/Debug/libargos2_simulator.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/Debug/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/Debug/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/Debug/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/Debug/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/Debug/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/Debug/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/Debug/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/Debug/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/Debug/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/Debug/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/Debug/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/Debug/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/Debug/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/Debug/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/Debug/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/Debug/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/Release/libargos2_simulator.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/Release/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/Release/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/Release/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/Release/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/Release/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/Release/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/Release/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/Release/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/Release/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/Release/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/Release/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/Release/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/Release/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/Release/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/Release/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/Release/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/MinSizeRel/libargos2_simulator.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/MinSizeRel/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/MinSizeRel/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/MinSizeRel/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/MinSizeRel/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/MinSizeRel/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/MinSizeRel/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/MinSizeRel/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/MinSizeRel/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/MinSizeRel/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/MinSizeRel/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/MinSizeRel/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/MinSizeRel/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/MinSizeRel/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/MinSizeRel/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/MinSizeRel/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/MinSizeRel/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/RelWithDebInfo/libargos2_simulator.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/RelWithDebInfo/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/RelWithDebInfo/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/RelWithDebInfo/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/RelWithDebInfo/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/RelWithDebInfo/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/RelWithDebInfo/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/RelWithDebInfo/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/RelWithDebInfo/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/RelWithDebInfo/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/RelWithDebInfo/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/RelWithDebInfo/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/RelWithDebInfo/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/RelWithDebInfo/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/RelWithDebInfo/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/RelWithDebInfo/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/RelWithDebInfo/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/tc/Prog/Robots/argos2/simulator/Debug/argos")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -change "/Users/tc/Prog/Robots/argos2/simulator/Debug/libargos2_simulator.dylib" "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/Debug/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/Debug/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/Debug/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/Debug/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/Debug/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/Debug/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/Debug/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/Debug/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/Debug/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/Debug/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/Debug/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/Debug/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/Debug/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/Debug/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/Debug/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/Debug/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/tc/Prog/Robots/argos2/simulator/Release/argos")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -change "/Users/tc/Prog/Robots/argos2/simulator/Release/libargos2_simulator.dylib" "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/Release/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/Release/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/Release/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/Release/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/Release/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/Release/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/Release/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/Release/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/Release/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/Release/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/Release/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/Release/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/Release/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/Release/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/Release/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/Release/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/tc/Prog/Robots/argos2/simulator/MinSizeRel/argos")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -change "/Users/tc/Prog/Robots/argos2/simulator/MinSizeRel/libargos2_simulator.dylib" "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/MinSizeRel/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/MinSizeRel/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/MinSizeRel/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/MinSizeRel/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/MinSizeRel/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/MinSizeRel/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/MinSizeRel/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/MinSizeRel/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/MinSizeRel/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/MinSizeRel/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/MinSizeRel/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/MinSizeRel/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/MinSizeRel/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/MinSizeRel/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/MinSizeRel/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/MinSizeRel/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/tc/Prog/Robots/argos2/simulator/RelWithDebInfo/argos")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -change "/Users/tc/Prog/Robots/argos2/simulator/RelWithDebInfo/libargos2_simulator.dylib" "libargos2_simulator.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/actuators/RelWithDebInfo/libargos2_simulator_actuators.dylib" "libargos2_simulator_actuators.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/configuration/RelWithDebInfo/libargos2_simulator_configuration.dylib" "libargos2_simulator_configuration.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/RelWithDebInfo/libargos2_simulator_dynamic_linking.dylib" "libargos2_simulator_dynamic_linking.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/factories/RelWithDebInfo/libargos2_simulator_factories.dylib" "libargos2_simulator_factories.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/libs/FreeImage/RelWithDebInfo/libargos2_libs_freeimage.dylib" "libargos2_libs_freeimage.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/RelWithDebInfo/libargos2_simulator_physics_engines.dylib" "libargos2_simulator_physics_engines.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/RelWithDebInfo/libargos2_simulator_physics_engines_dynamics2d.dylib" "libargos2_simulator_physics_engines_dynamics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics2d/chipmunk-physics/RelWithDebInfo/libchipmunk.dylib" "libchipmunk.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/dynamics3d/RelWithDebInfo/libargos2_simulator_physics_engines_dynamics3d.dylib" "libargos2_simulator_physics_engines_dynamics3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/kinematics2d/RelWithDebInfo/libargos2_simulator_physics_engines_kinematics2d.dylib" "libargos2_simulator_physics_engines_kinematics2d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/physics_engines/pointmass3d/RelWithDebInfo/libargos2_simulator_physics_engines_pointmass3d.dylib" "libargos2_simulator_physics_engines_pointmass3d.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/sensors/RelWithDebInfo/libargos2_simulator_sensors.dylib" "libargos2_simulator_sensors.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/space/RelWithDebInfo/libargos2_simulator_space.dylib" "libargos2_simulator_space.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/RelWithDebInfo/libargos2_simulator_visualizations.dylib" "libargos2_simulator_visualizations.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/povray/RelWithDebInfo/libargos2_simulator_povray_renderer.dylib" "libargos2_simulator_povray_renderer.dylib"
        -change "/Users/tc/Prog/Robots/argos2/simulator/visualizations/text/RelWithDebInfo/libargos2_simulator_text_renderer.dylib" "libargos2_simulator_text_renderer.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/argos")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/libs/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/configuration/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/actuators/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/sensors/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/physics_engines/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/visualizations/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/space/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/factories/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/visitors/cmake_install.cmake")
  INCLUDE("/Users/tc/Prog/Robots/argos2/simulator/dynamic_linking/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/tc/Prog/Robots/argos2/simulator/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/tc/Prog/Robots/argos2/simulator/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)

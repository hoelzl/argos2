# Install script for directory: /Users/tc/Prog/Robots/argos2/simulator/sensors

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator/sensors" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/simulated_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/range_and_bearing_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/generic_sampled_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/sensor_samples.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/wifi_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/clock_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator/sensors/footbot" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_base_ground_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_motor_ground_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_encoder_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_wheel_speed_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_distance_scanner_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_proximity_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_sampled_proximity_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_omnidirectional_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_ceiling_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_simple_omnidirectional_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_light_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_turret_torque_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_turret_encoder_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/foot-bot/footbot_gripper_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator/sensors/epuck" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/e-puck/epuck_light_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/e-puck/epuck_proximity_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/e-puck/epuck_ground_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/e-puck/epuck_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/e-puck/epuck_range_and_bearing_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/e-puck/epuck_encoder_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/e-puck/epuck_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/simulator/sensors/eyebot" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/eye-bot/eyebot_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/eye-bot/eyebot_altitude_sensor.h"
    "/Users/tc/Prog/Robots/argos2/simulator/sensors/eye-bot/eyebot_distance_scanner_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/sensors/Debug/libargos2_simulator_sensors.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_sensors.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/sensors/Release/libargos2_simulator_sensors.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_sensors.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/sensors/MinSizeRel/libargos2_simulator_sensors.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_sensors.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/simulator/sensors/RelWithDebInfo/libargos2_simulator_sensors.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_simulator_sensors.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_simulator_sensors.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")


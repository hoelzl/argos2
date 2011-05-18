# Install script for directory: /Users/tc/Prog/Robots/argos2/common/control_interface

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/ci_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/ci_clock_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/ci_controller.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/ci_robot.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/ci_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/ci_wifi_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/ci_wifi_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/swarmanoid" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/ci_battery_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/ci_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/ci_range_and_bearing_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/ci_range_and_bearing_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/swarmanoid/footbot" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_base_ground_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_beacon_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_omnidirectional_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_ceiling_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_distance_scanner_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_distance_scanner_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_encoder_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_gripper_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_gripper_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_leds_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_base_leds_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_light_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_motor_ground_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_proximity_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_torque_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_encoder_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_turret_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_wheel_speed_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/footbot/ci_footbot_wheels_actuator.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/swarmanoid/handbot" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_arm_encoders_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_arms_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_beacon_leds_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_gripper_cameras.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_leds_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_retrieve_book_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_proximity_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/handbot/ci_handbot_head_camera_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/swarmanoid/eyebot" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_altitude_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_distance_scanner_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_leds_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_pan_and_tilt_camera_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_pan_and_tilt_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_propellers_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/swarmanoid/eyebot/ci_eyebot_speech_actuator.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/sbot" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_slope_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_gripper_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_turret_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_traction_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_ir_ambient_light_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_wheels_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_light_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_turret_rotation_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_wheels_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_gripper_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_proximity_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_leds_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_ground_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/sbot/ci_sbot_binary_sound_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/e-puck" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_leds_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_light_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_proximity_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_ground_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_wheels_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_range_and_bearing_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_range_and_bearing_actuator.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_camera_sensor.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/e-puck/ci_epuck_encoder_sensor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/neural_networks" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/neural_networks/ci_ctrnn_multilayer_controller.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/neural_networks/ci_neural_network_controller.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/neural_networks/ci_perceptron_controller.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/neural_networks/ci_rnctn_controller.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/behavioral_toolkit" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/ci_behavior_controller.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/ci_behavior.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/ci_robot_state.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/ci_robot_data.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/behavioral_toolkit/utility/fsm" TYPE FILE FILES
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/utility_classes/fsm/fsm.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/utility_classes/fsm/transition.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/utility_classes/fsm/state.h"
    "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/utility_classes/fsm/action.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/behavioral_toolkit/swarmanoid/footbot" TYPE FILE FILES "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/swarmanoid/footbot/ci_footbot_state.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/behavioral_toolkit/swarmanoid/eyebot" TYPE FILE FILES "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/swarmanoid/eyebot/ci_eyebot_state.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos2/common/control_interface/behavioral_toolkit/swarmanoid/handbot" TYPE FILE FILES "/Users/tc/Prog/Robots/argos2/common/control_interface/behavioral_toolkit/swarmanoid/handbot/ci_handbot_state.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/common/control_interface/Debug/libargos2_common_control_interface.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_common_control_interface.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/common/control_interface/Release/libargos2_common_control_interface.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_common_control_interface.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/common/control_interface/MinSizeRel/libargos2_common_control_interface.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_common_control_interface.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos2" TYPE SHARED_LIBRARY FILES "/Users/tc/Prog/Robots/argos2/common/control_interface/RelWithDebInfo/libargos2_common_control_interface.dylib")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libargos2_common_control_interface.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos2/libargos2_common_control_interface.dylib")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")


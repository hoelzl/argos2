set(argos2_simulator_sensors_HEADERS_base
  simulated_sensor.h
  range_and_bearing_sensor.h
  generic_sampled_sensor.h
  sensor_samples.h
  wifi_sensor.h
  clock_sensor.h
)

set(argos2_simulator_sensors_HEADERS_footbot
  foot-bot/footbot_sensor.h
  foot-bot/footbot_base_ground_sensor.h
  foot-bot/footbot_motor_ground_sensor.h
  foot-bot/footbot_encoder_sensor.h
  foot-bot/footbot_wheel_speed_sensor.h
  foot-bot/footbot_distance_scanner_sensor.h
  foot-bot/footbot_proximity_sensor.h
  foot-bot/footbot_sampled_proximity_sensor.h
  foot-bot/footbot_omnidirectional_camera_sensor.h
  foot-bot/footbot_ceiling_camera_sensor.h
  foot-bot/footbot_simple_omnidirectional_camera_sensor.h
  foot-bot/footbot_light_sensor.h
  foot-bot/footbot_turret_torque_sensor.h
  foot-bot/footbot_turret_encoder_sensor.h
  foot-bot/footbot_gripper_sensor.h
)

set(argos2_simulator_sensors_HEADERS_epuck
  e-puck/epuck_light_sensor.h
  e-puck/epuck_proximity_sensor.h
  e-puck/epuck_ground_sensor.h
  e-puck/epuck_camera_sensor.h
  e-puck/epuck_range_and_bearing_sensor.h
  e-puck/epuck_encoder_sensor.h
  e-puck/epuck_sensor.h
  
)

set(argos2_simulator_sensors_HEADERS_eyebot
  eye-bot/eyebot_sensor.h
  eye-bot/eyebot_altitude_sensor.h
  eye-bot/eyebot_distance_scanner_sensor.h
)

set(argos2_simulator_sensors_IMPLEMENTATIONS
  range_and_bearing_sensor.cpp
  generic_sampled_sensor.cpp
  sensor_samples.cpp
  wifi_sensor.cpp
  clock_sensor.cpp
  foot-bot/footbot_base_ground_sensor.cpp
  foot-bot/footbot_motor_ground_sensor.cpp
  foot-bot/footbot_encoder_sensor.cpp
  foot-bot/footbot_wheel_speed_sensor.cpp
  foot-bot/footbot_distance_scanner_sensor.cpp
  foot-bot/footbot_proximity_sensor.cpp
  foot-bot/footbot_sampled_proximity_sensor.cpp
  foot-bot/footbot_omnidirectional_camera_sensor.cpp
  foot-bot/footbot_ceiling_camera_sensor.cpp
  foot-bot/footbot_simple_omnidirectional_camera_sensor.cpp
  foot-bot/footbot_light_sensor.cpp
  foot-bot/footbot_turret_torque_sensor.cpp
  foot-bot/footbot_turret_encoder_sensor.cpp
  foot-bot/footbot_gripper_sensor.cpp
  e-puck/epuck_range_and_bearing_sensor.cpp
  e-puck/epuck_light_sensor.cpp
  e-puck/epuck_proximity_sensor.cpp
  e-puck/epuck_ground_sensor.cpp
  e-puck/epuck_camera_sensor.cpp
  e-puck/epuck_encoder_sensor.cpp
  eye-bot/eyebot_altitude_sensor.cpp
  eye-bot/eyebot_distance_scanner_sensor.cpp
)

add_library(argos2_simulator_sensors SHARED ${argos2_simulator_sensors_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_sensors_HEADERS_base} DESTINATION include/argos2/simulator/sensors)
install(FILES ${argos2_simulator_sensors_HEADERS_footbot} DESTINATION include/argos2/simulator/sensors/footbot)
install(FILES ${argos2_simulator_sensors_HEADERS_epuck} DESTINATION include/argos2/simulator/sensors/epuck)
install(FILES ${argos2_simulator_sensors_HEADERS_eyebot} DESTINATION include/argos2/simulator/sensors/eyebot)
install(TARGETS argos2_simulator_sensors
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

set(argos2_simulator_actuators_HEADERS_base
  simulated_actuator.h
  range_and_bearing_actuator.h
  wifi_actuator.h
)

set(argos2_simulator_actuators_HEADERS_footbot
  foot-bot/footbot_actuator.h
  foot-bot/footbot_leds_actuator.h
  foot-bot/footbot_base_leds_actuator.h
  foot-bot/footbot_beacon_actuator.h
  foot-bot/footbot_wheels_actuator.h
  foot-bot/footbot_turret_actuator.h
  foot-bot/footbot_gripper_actuator.h
  foot-bot/footbot_distance_scanner_actuator.h
)

set(argos2_simulator_actuators_HEADERS_epuck
  e-puck/epuck_actuator.h
  e-puck/epuck_leds_actuator.h
  e-puck/epuck_wheels_actuator.h
  e-puck/epuck_range_and_bearing_actuator.h
)

set(argos2_simulator_actuators_HEADERS_eyebot
  eye-bot/eyebot_actuator.h
  eye-bot/eyebot_leds_actuator.h
  eye-bot/eyebot_propellers_actuator.h
)

set(argos2_simulator_actuators_IMPLEMENTATIONS
  range_and_bearing_actuator.cpp
  wifi_actuator.cpp
  foot-bot/footbot_leds_actuator.cpp
  foot-bot/footbot_base_leds_actuator.cpp
  foot-bot/footbot_beacon_actuator.cpp
  foot-bot/footbot_wheels_actuator.cpp
  foot-bot/footbot_turret_actuator.cpp
  foot-bot/footbot_gripper_actuator.cpp
  foot-bot/footbot_distance_scanner_actuator.cpp
  e-puck/epuck_leds_actuator.cpp
  e-puck/epuck_wheels_actuator.cpp
  e-puck/epuck_range_and_bearing_actuator.cpp
  eye-bot/eyebot_leds_actuator.cpp
  eye-bot/eyebot_propellers_actuator.cpp
)

add_library(argos2_simulator_actuators SHARED ${argos2_simulator_actuators_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_actuators_HEADERS_base} DESTINATION include/argos2/simulator/actuators)
install(FILES ${argos2_simulator_actuators_HEADERS_footbot} DESTINATION include/argos2/simulator/actuators/footbot)
install(FILES ${argos2_simulator_actuators_HEADERS_epuck} DESTINATION include/argos2/simulator/actuators/epuck)
install(FILES ${argos2_simulator_actuators_HEADERS_eyebot} DESTINATION include/argos2/simulator/actuators/eyebot)
install(TARGETS argos2_simulator_actuators
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

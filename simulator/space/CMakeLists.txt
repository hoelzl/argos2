set(argos2_simulator_space_HEADERS_base
  space.h
  space_no_threads.h
  space_multi_thread.h
  space_hash_tr1.h
  space_hash_native.h
  space_hash.h
)

set(argos2_simulator_space_HEADERS_entities
  entities/entity.h
  entities/positional_entity.h
  entities/embodied_entity.h
  entities/composable_entity.h
  entities/controllable_entity.h
  entities/wheeled_entity.h
  entities/led_entity.h
  entities/led_equipped_entity.h
  entities/gripper_equipped_entity.h
  entities/distance_scanner_equipped_entity.h
  entities/entity_decorator.h
  entities/box_entity.h
  entities/cylinder_entity.h
  entities/floor_entity.h
  entities/footbot_entity.h
  entities/epuck_entity.h
  entities/eyebot_entity.h
  entities/light_entity.h
  entities/rab_equipped_entity.h
  entities/medium_entity.h
  entities/wifi_medium_entity.h
  entities/wifi_equipped_entity.h
)

set(argos2_simulator_space_IMPLEMENTATIONS
  space.cpp
  space_no_threads.cpp
  space_multi_thread.cpp
  entities/entity.cpp
  entities/positional_entity.cpp
  entities/embodied_entity.cpp
  entities/controllable_entity.cpp
  entities/led_entity.cpp
  entities/led_equipped_entity.cpp
  entities/distance_scanner_equipped_entity.cpp
  entities/box_entity.cpp
  entities/cylinder_entity.cpp
  entities/floor_entity.cpp
  entities/footbot_entity.cpp
  entities/epuck_entity.cpp
  entities/eyebot_entity.cpp
  entities/light_entity.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/libs/FreeImage
  ${CMAKE_SOURCE_DIR}/libs/FreeImage/Source
  ${CMAKE_SOURCE_DIR}/libs/FreeImage/Wrapper/FreeImagePlus)

link_directories(${CMAKE_BINARY_DIR}/libs/FreeImage/)
add_library(argos2_simulator_space SHARED ${argos2_simulator_space_IMPLEMENTATIONS})
target_link_libraries(argos2_simulator_space argos2_libs_freeimage)

install(FILES ${argos2_simulator_space_HEADERS_base} DESTINATION include/argos2/simulator/space)
install(FILES ${argos2_simulator_space_HEADERS_entities} DESTINATION include/argos2/simulator/space/entities)
install(TARGETS argos2_simulator_space
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2
)

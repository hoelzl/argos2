add_subdirectory(chipmunk-physics)

set(argos2_simulator_physics_engines_dynamics2d_HEADERS
  dynamics2d_box_entity.h
  dynamics2d_cylinder_entity.h
  dynamics2d_epuck_entity.h
  dynamics2d_footbot_entity.h
  dynamics2d_eyebot_entity.h
  dynamics2d_add_visitor.h
  dynamics2d_remove_visitor.h
  dynamics2d_entity.h
  dynamics2d_engine.h)

set(argos2_simulator_physics_engines_dynamics2d_IMPLEMENTATIONS
  dynamics2d_box_entity.cpp
  dynamics2d_cylinder_entity.cpp
  dynamics2d_epuck_entity.cpp
  dynamics2d_footbot_entity.cpp
  dynamics2d_eyebot_entity.cpp
  dynamics2d_add_visitor.cpp
  dynamics2d_remove_visitor.cpp
  dynamics2d_engine.cpp)

link_directories(${CMAKE_BUILD_DIR}/physics_engines/dynamics2d/chipmunk-physics)
add_library(argos2_simulator_physics_engines_dynamics2d SHARED ${argos2_simulator_physics_engines_dynamics2d_IMPLEMENTATIONS})
target_link_libraries(argos2_simulator_physics_engines_dynamics2d chipmunk)

install(FILES ${argos2_simulator_physics_engines_dynamics2d_HEADERS} DESTINATION include/argos2/simulator/physics_engines/dynamics2d)
install(TARGETS argos2_simulator_physics_engines_dynamics2d
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

set(argos2_simulator_physics_engines_pointmass3d_HEADERS
  pointmass3d_eyebot.h
  pointmass3d_add_visitor.h
  pointmass3d_remove_visitor.h
  pointmass3d_entity.h
  pointmass3d_engine.h)

set(argos2_simulator_physics_engines_pointmass3d_IMPLEMENTATIONS
  pointmass3d_eyebot.cpp
  pointmass3d_add_visitor.cpp
  pointmass3d_remove_visitor.cpp
  pointmass3d_engine.cpp)

add_library(argos2_simulator_physics_engines_pointmass3d SHARED ${argos2_simulator_physics_engines_pointmass3d_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_physics_engines_pointmass3d_HEADERS} DESTINATION include/argos2/simulator/physics_engines/pointmass3d)
install(TARGETS argos2_simulator_physics_engines_pointmass3d
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

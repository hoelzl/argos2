set(argos2_simulator_physics_engines_dynamics3d_HEADERS
  dynamics3d_box.h
  dynamics3d_cylinder.h
  dynamics3d_eyebot.h
  dynamics3d_add_visitor.h
  dynamics3d_remove_visitor.h
  dynamics3d_entity.h
  dynamics3d_engine.h)

set(argos2_simulator_physics_engines_dynamics3d_IMPLEMENTATIONS
  dynamics3d_box.cpp
  dynamics3d_cylinder.cpp
  dynamics3d_eyebot.cpp
  dynamics3d_add_visitor.cpp
  dynamics3d_remove_visitor.cpp
  dynamics3d_entity.cpp
  dynamics3d_engine.cpp)

include_directories(${ODE_INCLUDE_DIR})
add_library(argos2_simulator_physics_engines_dynamics3d SHARED ${argos2_simulator_physics_engines_dynamics3d_IMPLEMENTATIONS})
target_link_libraries(argos2_simulator_physics_engines_dynamics3d ${ODE_LIBRARY})
set_target_properties(argos2_simulator_physics_engines_dynamics3d PROPERTIES COMPILE_FLAGS ${ODE_DEFINITIONS})

install(FILES ${argos2_simulator_physics_engines_dynamics3d_HEADERS} DESTINATION include/argos2/simulator/physics_engines/dynamics3d)
install(TARGETS argos2_simulator_physics_engines_dynamics3d
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

find_package(ODE 0.11.1)

add_subdirectory(dynamics2d)
add_subdirectory(pointmass3d)
add_subdirectory(kinematics2d)

if(ODE_FOUND)
  add_subdirectory(dynamics3d)
endif(ODE_FOUND)

set(argos2_simulator_physics_engines_HEADERS
  physics_engine.h
  physics_engine_entity.h)

set(argos2_simulator_physics_engines_IMPLEMENTATIONS
  physics_engine.cpp)

add_library(argos2_simulator_physics_engines SHARED ${argos2_simulator_physics_engines_IMPLEMENTATIONS})
target_link_libraries(argos2_simulator_physics_engines
  argos2_simulator_physics_engines_dynamics2d
  argos2_simulator_physics_engines_pointmass3d
  argos2_simulator_physics_engines_kinematics2d)

if(ODE_FOUND)
  target_link_libraries(argos2_simulator_physics_engines
    argos2_simulator_physics_engines_dynamics3d)
endif(ODE_FOUND)

install(FILES ${argos2_simulator_physics_engines_HEADERS} DESTINATION include/argos2/simulator/physics_engines)
install(TARGETS argos2_simulator_physics_engines
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

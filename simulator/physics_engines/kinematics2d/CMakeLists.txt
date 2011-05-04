set(argos2_simulator_physics_engines_kinematics2d_HEADERS
  kinematics2d_box.h
  kinematics2d_footbot.h
  kinematics2d_eyebot.h
  kinematics2d_add_visitor.h
  kinematics2d_remove_visitor.h
  kinematics2d_collision_circle.h
  kinematics2d_collision_rectangle.h
  kinematics2d_entity.h
  kinematics2d_engine.h)

set(argos2_simulator_physics_engines_kinematics2d_IMPLEMENTATIONS
  kinematics2d_box.cpp
  kinematics2d_footbot.cpp
  kinematics2d_eyebot.cpp
  kinematics2d_add_visitor.cpp
  kinematics2d_remove_visitor.cpp
  kinematics2d_collision_circle.cpp
  kinematics2d_collision_rectangle.cpp
  kinematics2d_entity.cpp
  kinematics2d_engine.cpp)

add_library(argos2_simulator_physics_engines_kinematics2d SHARED ${argos2_simulator_physics_engines_kinematics2d_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_physics_engines_kinematics2d_HEADERS} DESTINATION include/argos2/simulator/physics_engines/kinematics2d)
install(TARGETS argos2_simulator_physics_engines_kinematics2d
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

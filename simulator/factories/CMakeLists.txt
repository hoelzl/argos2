set(argos2_simulator_factories_HEADERS
  actuators_factory.h
  entities_factory.h
  physicsengines_factory.h
  renderers_factory.h
  sensors_factory.h)

set(argos2_simulator_factories_IMPLEMENTATIONS
  actuators_factory.cpp
  entities_factory.cpp
  physicsengines_factory.cpp
  renderers_factory.cpp
  sensors_factory.cpp)

add_library(argos2_simulator_factories SHARED ${argos2_simulator_factories_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_factories_HEADERS} DESTINATION include/argos2/simulator/factories)
install(TARGETS argos2_simulator_factories
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

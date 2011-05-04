set(argos2_simulator_dynamic_linking_HEADERS
  dynamic_linking_manager.h
  loop_functions_registration.h
  loop_functions.h)

set(argos2_simulator_dynamic_linking_IMPLEMENTATIONS
  dynamic_linking_manager.cpp
  loop_functions.cpp)

add_library(argos2_simulator_dynamic_linking SHARED ${argos2_simulator_dynamic_linking_IMPLEMENTATIONS})
target_link_libraries(argos2_simulator_dynamic_linking dl)

install(FILES ${argos2_simulator_dynamic_linking_HEADERS} DESTINATION include/argos2/simulator/dynamic_linking)
install(TARGETS argos2_simulator_dynamic_linking
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

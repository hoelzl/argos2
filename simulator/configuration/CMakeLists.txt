set(argos2_simulator_configuration_HEADERS
  command_line_argument_parser.h
  fix_config.h)

set(argos2_simulator_configuration_IMPLEMENTATIONS
  command_line_argument_parser.cpp)

add_library(argos2_simulator_configuration SHARED ${argos2_simulator_configuration_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_configuration_HEADERS} DESTINATION include/argos2/simulator/configuration)
install(TARGETS argos2_simulator_configuration
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

set(argos2_simulator_text_renderer_HEADERS
  text_render.h)

set(argos2_simulator_text_renderer_IMPLEMENTATIONS
  text_render.cpp)

add_library(argos2_simulator_text_renderer SHARED ${argos2_simulator_text_renderer_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_text_renderer_HEADERS} DESTINATION include/argos2/simulator/visualisations/text)
install(TARGETS argos2_simulator_text_renderer
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

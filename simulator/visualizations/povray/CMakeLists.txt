set(argos2_simulator_povray_renderer_HEADERS
  povray_render.h)

set(argos2_simulator_povray_renderer_IMPLEMENTATIONS
  povray_render.cpp)

add_library(argos2_simulator_povray_renderer SHARED ${argos2_simulator_povray_renderer_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_povray_renderer_HEADERS} DESTINATION include/argos2/simulator/visualisations/povray)
install(TARGETS argos2_simulator_povray_renderer
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

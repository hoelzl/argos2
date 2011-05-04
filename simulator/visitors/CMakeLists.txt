set(argos2_simulator_visitors_HEADERS
  entity_visitor.h
  povray_render_visitor_draw.h
  space_visitor_add.h
  space_visitor_remove.h
  text_render_visitor.h
  text_render_visitor_draw.h
)

set(argos2_simulator_visitors_IMPLEMENTATIONS
   empty.cpp
   povray_render_visitor_draw.cpp
)

add_library(argos2_simulator_visitors SHARED ${argos2_simulator_visitors_IMPLEMENTATIONS})

install(FILES ${argos2_simulator_visitors_HEADERS} DESTINATION include/argos2/simulator/visitors)
install(TARGETS argos2_simulator_visitors
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)
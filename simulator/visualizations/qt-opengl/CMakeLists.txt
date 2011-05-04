include(${QT_USE_FILE})

set(argos2_simulator_qtopengl_renderer_HEADERS
  qtopengl_render.h
  qtopengl_visitor.h
  qtopengl_user_functions.h
)

set(argos2_simulator_qtopengl_renderer_HEADERS_models
  models/qtopengl_box.h
  models/qtopengl_cylinder.h
  models/qtopengl_footbot.h
  models/qtopengl_epuck.h
  models/qtopengl_eyebot.h
  models/qtopengl_light.h
)

set(argos2_simulator_qtopengl_renderer_MOC_HEADERS
  qtopengl_camera.h
  qtopengl_main_window.h
  qtopengl_widget.h
)

if(SDL_FOUND)
  set(argos2_simulator_qtopengl_renderer_MOC_HEADERS
    ${argos2_simulator_qtopengl_renderer_MOC_HEADERS}
    qtopengl_joystick.h)
endif(SDL_FOUND)

qt4_wrap_cpp(argos2_simulator_qtopengl_renderer_MOC_IMPLEMENTATIONS
  ${argos2_simulator_qtopengl_renderer_MOC_HEADERS}
)

set(argos2_simulator_qtopengl_renderer_IMPLEMENTATIONS
  ${argos2_simulator_qtopengl_renderer_MOC_IMPLEMENTATIONS}
  models/qtopengl_box.cpp
  models/qtopengl_cylinder.cpp
  models/qtopengl_footbot.cpp
  models/qtopengl_epuck.cpp
  models/qtopengl_eyebot.cpp
  models/qtopengl_light.cpp
  qtopengl_user_functions.cpp
  qtopengl_visitor.cpp
  qtopengl_camera.cpp
  qtopengl_main_window.cpp
  qtopengl_widget.cpp
  qtopengl_render.cpp
)

if(SDL_FOUND)
  set(argos2_simulator_qtopengl_renderer_IMPLEMENTATIONS
    ${argos2_simulator_qtopengl_renderer_IMPLEMENTATIONS}
    qtopengl_joystick.cpp)
endif(SDL_FOUND)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/visualizations/qt-opengl)
if(SDL_FOUND)
  include_directories(${SDL_INCLUDE_DIR})
endif(SDL_FOUND)

add_library(argos2_simulator_qtopengl_renderer SHARED ${argos2_simulator_qtopengl_renderer_IMPLEMENTATIONS})

target_link_libraries(argos2_simulator_qtopengl_renderer ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
if(SDL_FOUND)
 target_link_libraries(argos2_simulator_qtopengl_renderer ${SDL_LIBRARY})
endif(SDL_FOUND)

install(FILES ${argos2_simulator_qtopengl_renderer_HEADERS}        DESTINATION include/argos2/simulator/visualizations/qt-opengl)
install(FILES ${argos2_simulator_qtopengl_renderer_MOC_HEADERS}    DESTINATION include/argos2/simulator/visualizations/qt-opengl)
install(FILES ${argos2_simulator_qtopengl_renderer_HEADERS_models} DESTINATION include/argos2/simulator/visualizations/qt-opengl/models)
install(TARGETS argos2_simulator_qtopengl_renderer
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2
)

if( NOT ARGOS_COMPILE_REAL_SWARMANOID )
  find_package(GSL REQUIRED)
endif( NOT ARGOS_COMPILE_REAL_SWARMANOID )

set(argos2_common_utility_HEADERS_base
  PQi.h
  frac_time.h
  string_utilities.h
  argos_random.h
  tree.h
)

set(argos2_common_utility_HEADERS_configuration
  configuration/argos_exception.h
  configuration/argos_configuration.h
  configuration/base_configurable_resource.h
  configuration/memento.h
)

set(argos2_common_utility_HEADERS_datatypes
  datatypes/any.h
  datatypes/color.h
  datatypes/datatypes.h
  datatypes/byte_array.h
)

set(argos2_common_utility_HEADERS_logging
  logging/argos_log.h
  logging/argos_log_no_threads.h
  logging/argos_log_thread_safe.h
  logging/argos_colored_text.h
)

set(argos2_common_utility_HEADERS_math
  math/angles.h
  math/general.h
  math/quaternion.h
  math/range.h
  math/ray.h
  math/segment.h
  math/vector2.h
  math/vector3.h
  math/matrix3x3.h
)

set(argos2_common_utility_HEADERS_math_shapes2
  math/shapes2/primitive2.h
)

set(argos2_common_utility_HEADERS_profiler
  profiler/profiler.h
)

set(argos2_common_utility_HEADERS_tinyxml
  tinyxml-cpp/ticpp.h
  tinyxml-cpp/ticpprc.h
  tinyxml-cpp/tinystr.h
  tinyxml-cpp/tinyxml.h)

set(argos2_common_utility_IMPLEMENTATIONS
  argos_random.cpp
  string_utilities.cpp
  frac_time.cpp
  math/vector2.cpp
  math/angles.cpp
  math/vector3.cpp
  math/matrix3x3.cpp
  math/segment.cpp
  math/shapes2/primitive2.cpp
  logging/argos_log.cpp
  datatypes/color.cpp
  datatypes/byte_array.cpp
  profiler/profiler.cpp
  tinyxml-cpp/tinyxml.cpp
  tinyxml-cpp/tinystr.cpp
  tinyxml-cpp/tinyxmlerror.cpp
  tinyxml-cpp/ticpp.cpp
  tinyxml-cpp/tinyxmlparser.cpp
)

if( NOT ARGOS_COMPILE_REAL_SWARMANOID )
  add_definitions(${CMAKE_GSL_CXX_FLAGS})
  link_directories(${GSL_LINK_DIRECTORIES})
endif( NOT ARGOS_COMPILE_REAL_SWARMANOID )

add_library(argos2_common_utility SHARED ${argos2_common_utility_IMPLEMENTATIONS})

if( NOT ARGOS_COMPILE_REAL_SWARMANOID )
  target_link_libraries(argos2_common_utility ${GSL_LIBRARIES})
  link_googleperftools_to(argos2_common_utility)
endif( NOT ARGOS_COMPILE_REAL_SWARMANOID )

install(FILES ${argos2_common_utility_HEADERS_base} DESTINATION include/argos2/common/utility)
install(FILES ${argos2_common_utility_HEADERS_configuration} DESTINATION include/argos2/common/utility/configuration)
install(FILES ${argos2_common_utility_HEADERS_datatypes} DESTINATION include/argos2/common/utility/datatypes)
install(FILES ${argos2_common_utility_HEADERS_logging} DESTINATION include/argos2/common/utility/logging)
install(FILES ${argos2_common_utility_HEADERS_math} DESTINATION include/argos2/common/utility/math)
install(FILES ${argos2_common_utility_HEADERS_math_shapes2} DESTINATION include/argos2/common/utility/math/shapes2)
install(FILES ${argos2_common_utility_HEADERS_profiler} DESTINATION include/argos2/common/utility/profiler)
install(FILES ${argos2_common_utility_HEADERS_tinyxml} DESTINATION include/argos2/common/utility/tinyxml-cpp)
install(TARGETS argos2_common_utility
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

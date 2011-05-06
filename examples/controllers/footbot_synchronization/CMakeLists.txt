set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
if( NOT ARGOS_COMPILE_REAL_SWARMANOID )
  find_package(GSL REQUIRED)
endif( NOT ARGOS_COMPILE_REAL_SWARMANOID )
 
add_library(footbot_synchronization MODULE footbot_synchronization.cpp)

if( NOT ARGOS_COMPILE_REAL_SWARMANOID )
  add_definitions(${CMAKE_GSL_CXX_FLAGS})
  include_directories(${GSL_INCLUDE_DIR})
  link_directories(${GSL_LINK_DIRECTORIES})
endif( NOT ARGOS_COMPILE_REAL_SWARMANOID )

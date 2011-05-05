cmake_minimum_required(VERSION 2.6)
project(argos2_simulator)

execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
if (GCC_VERSION VERSION_GREATER 4.2 OR GCC_VERSION VERSION_EQUAL 4.2)
  message(STATUS "GCC/G++ version >= 4.2")
else()
  message(FATAL_ERROR "You need to have at least GCC/G++ version 4.2!")
endif()

set(CPACK_GENERATOR TBZ2)
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ARGoS2 simulator package")
include(CPack)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_SOURCE_DIR}/../common/cmake)

if( NOT ARGOS_COMPILE_REAL_SWARMANOID )
  find_package(GSL REQUIRED)
  add_definitions(${CMAKE_GSL_CXX_FLAGS})
  include_directories(${GSL_INCLUDE_DIR})
  link_directories(${GSL_LINK_DIRECTORIES})
endif( NOT ARGOS_COMPILE_REAL_SWARMANOID )

find_package(Pthreads)
if(NOT PTHREADS_FOUND)  
  message(FATAL_ERROR "Required library pthread not found.")
endif(NOT PTHREADS_FOUND)
add_definitions(${PTHREADS_DEFINITIONS})

find_package(GooglePerfTools)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/..)
add_definitions(-DTIXML_USE_TICPP)
include(${CMAKE_SOURCE_DIR}/../common/cmake/SimulationConfig.cmake)
if(EXISTS ${CMAKE_SOURCE_DIR}/../user/my_user/cmake/user_config.cmake)
  include(${CMAKE_SOURCE_DIR}/../user/my_user/cmake/user_config.cmake)
endif(EXISTS ${CMAKE_SOURCE_DIR}/../user/my_user/cmake/user_config.cmake)  

add_subdirectory(libs)
add_subdirectory(configuration)
add_subdirectory(actuators)
add_subdirectory(sensors)
add_subdirectory(physics_engines)
add_subdirectory(visualizations)
add_subdirectory(space)
add_subdirectory(factories)
add_subdirectory(visitors)
add_subdirectory(dynamic_linking)

set(argos2_simulator_HEADERS
  simulator.h)

set(argos2_simulator_IMPLEMENTATIONS
  simulator.cpp)

link_directories(
  ${CMAKE_BINARY_DIR}/../common/simulator/utility
  ${CMAKE_BINARY_DIR}/../common/simulator/control_interface)

add_library(argos2_simulator SHARED ${argos2_simulator_IMPLEMENTATIONS})
set_target_properties(argos2_simulator PROPERTIES VERSION 2.0)
target_link_libraries(argos2_simulator
  argos2_common_utility
  argos2_common_control_interface
  argos2_simulator_configuration
  argos2_simulator_factories
  argos2_simulator_actuators
  argos2_simulator_sensors
  argos2_simulator_space
  argos2_simulator_physics_engines
  argos2_simulator_visualizations
  argos2_simulator_dynamic_linking
  ${PTHREADS_LIBRARY})
link_googleperftools_to(argos2_simulator)

add_executable(argos main.cpp)
target_link_libraries(argos argos2_simulator)
link_googleperftools_to(argos)

install(FILES ${argos2_simulator_HEADERS} DESTINATION include/argos2/simulator)
install(TARGETS argos2_simulator argos
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)

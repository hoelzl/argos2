cmake_minimum_required(VERSION 2.6)
project(argos2_common)

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
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ARGoS2 common package")
include(CPack)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
add_definitions(-DTIXML_USE_TICPP)
include(${CMAKE_SOURCE_DIR}/cmake/SimulationConfig.cmake)
if(EXISTS ${CMAKE_SOURCE_DIR}/../user/my_user/cmake/user_config.cmake)
  include(${CMAKE_SOURCE_DIR}/../user/my_user/cmake/user_config.cmake)
endif(EXISTS ${CMAKE_SOURCE_DIR}/../user/my_user/cmake/user_config.cmake)  
include_directories(${CMAKE_SOURCE_DIR}/..)

if( ARGOS_COMPILE_REAL_SWARMANOID )

  set(ARGOSINSTALLDIR $ENV{ARGOSINSTALLDIR})
  include(${CMAKE_SOURCE_DIR}/../real_robot/swarmanoid/cmake/moboard.cmake)
  add_definitions(-DCROSSCOMPILING)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/EclipseRealSwarmanoidProjectFile.xml ${CMAKE_BINARY_DIR}/.project)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/EclipseRealSwarmanoidCProjectFile.xml ${CMAKE_BINARY_DIR}/.cproject)

else( ARGOS_COMPILE_REAL_SWARMANOID )

  find_package(GooglePerfTools)

endif( ARGOS_COMPILE_REAL_SWARMANOID )

add_subdirectory(utility)
add_subdirectory(control_interface)

cmake_minimum_required(VERSION 2.6)
project(argos2_sample)



# Find the ARGoS package
set(CMAKE_MODULE_PATH /usr/local/share/argos2)
find_package(ARGoS REQUIRED)

# Include the compiler configuration, to avoid link errors on MacOS
include(${CMAKE_SOURCE_DIR}/cmake/Config.cmake)

# Set ARGoS include dir
include_directories(${ARGOS_INCLUDE_DIR})

# Set ARGoS link dir
link_directories(${ARGOS_LINK_DIR})

# Descend into the controllers directory
add_subdirectory(controllers)

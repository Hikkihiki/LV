cmake_minimum_required (VERSION 2.6)

project (LV)

# The version number.
set (LV_VERSION_MAJOR 1)
set (LV_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code

configure_file (
  "${PROJECT_SOURCE_DIR}/version.hpp.in"
  "${PROJECT_BINARY_DIR}/version.hpp"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(lv main.cpp logic/symbol/symbol.cpp)

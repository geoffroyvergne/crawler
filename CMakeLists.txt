cmake_minimum_required(VERSION 3.10)
project(crawler VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include config.h
#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${BINARY}")
configure_file ("${PROJECT_SOURCE_DIR}/include/config.h.in" "${PROJECT_BINARY_DIR}/include/config.h")
include_directories("${PROJECT_BINARY_DIR}/include")

# Configure a header file to pass some of the CMake settings
configure_file(include/config.h.in include/config.h)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

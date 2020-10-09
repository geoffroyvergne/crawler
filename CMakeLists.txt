cmake_minimum_required(VERSION 3.10)
project(crawler VERSION 1.0)

set(APP_NAME crawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#-Wc++11-narrowing
#add_definitions("-Wc++11-narrowing")

# group src file list to compile
file(GLOB_RECURSE SOURCES_SRC LIST_DIRECTORIES true src/*.hpp src/*.cpp src/*.h include/*.hpp include/*.h)
set(SOURCES_SRC ${SOURCES_SRC})

# group test file list to compile
file(GLOB_RECURSE SOURCES_TEST LIST_DIRECTORIES true test/*.hpp test/*.cpp test/*.h include/*.hpp include/*.h)
set(SOURCES_TEST ${SOURCES_TEST})

# Add include config.h
#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${BINARY}")
configure_file ("${PROJECT_SOURCE_DIR}/include/app.h.in" "${PROJECT_BINARY_DIR}/include/app.h")
include_directories("${PROJECT_BINARY_DIR}/include")

# Configure a header file to pass some of the CMake settings
configure_file(include/app.h.in include/app.h)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

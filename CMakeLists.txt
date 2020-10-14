cmake_minimum_required(VERSION 3.10)
project(crawler VERSION 1.0)

set(APP_NAME crawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#-Wc++11-narrowing
#add_definitions("-Wc++11-narrowing")

# group common lib file list to compile
file(GLOB_RECURSE SOURCES_COMMON LIST_DIRECTORIES true common/*.cpp)
set(SOURCES_COMMON ${SOURCES_COMMON})

# group cli file list to compile
file(GLOB_RECURSE SOURCES_CLI LIST_DIRECTORIES true cli/*.cpp)
set(SOURCES_SRC ${SOURCES_CLI})

# group rest file list to compile
file(GLOB_RECURSE SOURCES_REST LIST_DIRECTORIES true rest/*.cpp)
set(SOURCES_SRC ${SOURCES_REST})

# group test file list to compile
file(GLOB_RECURSE SOURCES_TEST LIST_DIRECTORIES true test/*.cpp)
set(SOURCES_TEST ${SOURCES_TEST})

# Add include config.h
#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${BINARY}")
configure_file ("${PROJECT_SOURCE_DIR}/include/app.h.in" "${PROJECT_BINARY_DIR}/include/app.h")
include_directories("${PROJECT_BINARY_DIR}/include")

# Configure a header file to pass some of the CMake settings
configure_file(include/app.h.in include/app.h)

# Add conan dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include)

# add common folder as lib
add_subdirectory(common)
list(APPEND EXTRA_LIBS common)

add_subdirectory(cli)
add_subdirectory(rest)
add_subdirectory(test)

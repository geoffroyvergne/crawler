cmake_minimum_required(VERSION 3.10)
project(crawler VERSION 1.0)

set(APP_NAME crawler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# group common lib file list to compile
file(GLOB_RECURSE SOURCES_COMMON LIST_DIRECTORIES true src/common/*.cpp)
set(SOURCES_COMMON ${SOURCES_COMMON})

# group cli file list to compile
file(GLOB_RECURSE SOURCES_CLI LIST_DIRECTORIES true src/cli/*.cpp)
set(SOURCES_SRC ${SOURCES_CLI})

# group rest file list to compile
file(GLOB_RECURSE SOURCES_REST LIST_DIRECTORIES true src/rest/*.cpp)
set(SOURCES_SRC ${SOURCES_REST})

# group test file list to compile
file(GLOB_RECURSE SOURCES_TEST LIST_DIRECTORIES true src/test/*.cpp)
set(SOURCES_TEST ${SOURCES_TEST})

# CURL
#set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)

#Gumbo
include(FetchContent)

set(FETCHCONTENT_QUIET off)
get_filename_component(fc_base "../fc_base" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(FETCHCONTENT_BASE_DIR ${fc_base})

FetchContent_Declare(
        gumbo
        GIT_REPOSITORY "https://github.com/geoffroyvergne/gumbo-parser"
        GIT_TAG "v0.11.0-cmake"
)

FetchContent_MakeAvailable(gumbo)

include_directories(${CURL_INCLUDE_DIR} include)
# ${OpenSSL_INCLUDE_DIRS} 

# add common folder as lib
add_subdirectory(src/common)
list(APPEND EXTRA_LIBS src/common)

add_subdirectory(src/cli)
add_subdirectory(src/rest)
add_subdirectory(src/test)

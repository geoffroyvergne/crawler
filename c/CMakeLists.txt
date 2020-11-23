cmake_minimum_required(VERSION 3.10)
project(crawler VERSION 1.0)

set(C_STANDARD 11)

# group common lib file list to compile
file(GLOB_RECURSE SOURCES_COMMON LIST_DIRECTORIES true src/common/*.c)
set(SOURCES_COMMON ${SOURCES_COMMON})

file(GLOB_RECURSE SOURCES_CLI LIST_DIRECTORIES true src/cli/*.c)
set(SOURCES_CLI ${SOURCES_CLI})

file(GLOB_RECURSE SOURCES_REST LIST_DIRECTORIES true src/rest/*.c)
set(SOURCES_REST ${SOURCES_REST})

file(GLOB_RECURSE SOURCES_TEST LIST_DIRECTORIES true src/test/*.c)
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
        #GIT_BRANCH "master"
)

FetchContent_MakeAvailable(gumbo)

include_directories(${CURL_INCLUDE_DIR} include)

# add common folder as lib
add_subdirectory(src/common)
list(APPEND EXTRA_LIBS src/common)

add_subdirectory(src/cli)
add_subdirectory(src/rest)
add_subdirectory(src/test)

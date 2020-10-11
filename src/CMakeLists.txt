set(BINARY ${CMAKE_PROJECT_NAME})
#set(LIB ${CMAKE_PROJECT_NAME}_src_lib)

# Set source
#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ./*.hpp ./*.cpp ./*.h ../include/*.hpp ../include/*.h)
#set(SOURCES ${SOURCES})

# Add specific compilation options
add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)

# Add conan dependencies
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

add_executable(${BINARY} ${SOURCES_SRC})
#add_library(${LIB} STATIC ${SOURCES})
#target_link_libraries(${BINARY} ${CONAN_LIBS})

find_package( CURL )
target_link_libraries(${BINARY} ${CONAN_LIBS} CURL)

#target_include_directories(${CMAKE_PROJECT_NAME}/src PUBLIC "${PROJECT_BINARY_DIR}")

# Copy binary to build/bin
add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})

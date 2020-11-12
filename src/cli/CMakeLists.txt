set(BINARY ${CMAKE_PROJECT_NAME}_cli)
set(LIB_COMMON common)

# Add specific compilation options
add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)

# Add conan dependencies
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

add_executable(${BINARY} ${SOURCES_CLI})
#add_library(${LIB} STATIC ${SOURCES_CLI})

target_link_libraries(${BINARY} ${Boost_LIBRARIES} ${LIB_COMMON})

# Copy binary to build/bin
add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})

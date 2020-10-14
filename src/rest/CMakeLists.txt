set(BINARY ${CMAKE_PROJECT_NAME}_rest)
set(LIB_COMMON common)

# Add specific compilation options
add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)

add_executable(${BINARY} ${SOURCES_REST})
#add_library(${LIB} STATIC ${SOURCES_REST})

target_link_libraries(${BINARY} ${CONAN_LIBS} ${LIB_COMMON})

#find_package( CURL )
#include_directories(${CURL_INCLUDE_DIR})
#target_link_libraries(${BINARY} ${CONAN_LIBS} ${CURL_LIBRARIES} ${LIB_COMMON})

# Copy binary to build/bin
add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})

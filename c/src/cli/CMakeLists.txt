set(BINARY ${CMAKE_PROJECT_NAME}_cli)
set(LIB_COMMON common)

# Add specific compilation options
#-fvisibility=default
add_compile_options(-fvisibility=hidden)

add_executable(${BINARY} ${SOURCES_CLI})
#add_library(${LIB} STATIC ${SOURCES_REST})

target_link_libraries(${BINARY} ${LIB_COMMON})

# Copy binary to build/bin
add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})

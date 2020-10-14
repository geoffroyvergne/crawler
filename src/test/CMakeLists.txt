set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(LIB_COMMON common)

add_executable(${BINARY} ${SOURCES_TEST})
#add_library(${LIB} STATIC ${SOURCES})

target_link_libraries(${BINARY} ${CONAN_LIBS} ${LIB_COMMON})

#find_package( CURL )
#include_directories(${CURL_INCLUDE_DIR})
#target_link_libraries(${BINARY} ${CONAN_LIBS} ${CURL_LIBRARIES} ${LIB_COMMON})

# Copy binary to build/test
add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})

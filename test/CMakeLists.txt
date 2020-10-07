set(BINARY ${CMAKE_PROJECT_NAME}_test_bin)
#set(LIB ${CMAKE_PROJECT_NAME}_test_lib)

# Set source
#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ./*.hpp ./*.cpp ./*.h ../include/*.hpp ../include/*.h)
#set(SOURCES ${SOURCES})

# Add conan dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${BINARY} ${SOURCES_TEST})
#add_library(${LIB} STATIC ${SOURCES})
target_link_libraries(${BINARY} ${CONAN_LIBS})

# Copy binary to build/test
add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})

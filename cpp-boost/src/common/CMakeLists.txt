
add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)

# Add conan dependencies
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

# [STATIC | SHARED | MODULE]
add_library(common STATIC ${SOURCES_COMMON})

target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(common ${LIB_COMMON} gumbo ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
# ${OPENSSL_LIBRARIES}

install(TARGETS common DESTINATION lib)

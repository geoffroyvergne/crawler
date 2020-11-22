add_compile_options(-fvisibility=hidden)

# [STATIC | SHARED | MODULE]
add_library(common STATIC ${SOURCES_COMMON})

target_include_directories( common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_libraries(common ${LIB_COMMON} gumbo ${CURL_LIBRARIES})

install(TARGETS common DESTINATION lib)

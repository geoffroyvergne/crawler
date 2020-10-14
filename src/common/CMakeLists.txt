# [STATIC | SHARED | MODULE]
add_library(common STATIC ${SOURCES_COMMON})

target_include_directories( common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )

install(TARGETS common DESTINATION lib)

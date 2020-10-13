file(GLOB_RECURSE SOURCES_COMMON LIST_DIRECTORIES true *.cpp *.h)
set(SOURCES_COMMON ${SOURCES_COMMON})

include_directories("../include")

# [STATIC | SHARED | MODULE]
add_library(common STATIC ${SOURCES_COMMON})

target_include_directories( common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )

install(TARGETS common DESTINATION lib)
#install(FILES mysqrt.h DESTINATION include)


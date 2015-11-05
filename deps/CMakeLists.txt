project(deps)

# for the command line UI
set(CARGO_BUILD_STATIC_LIB TRUE)
set(CARGO_TEST FALSE)
add_subdirectory(cargo)

# for zip file
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(zlib)
set(MINIZIP_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/minizip)
add_subdirectory(minizip-cmake)

# for code-message
set(CODE_MESSAGE_ENTRY "${libfwtool_SOURCE_DIR}/messages/message_all.h")
add_subdirectory(libcodemsg)

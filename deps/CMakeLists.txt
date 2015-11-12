project(deps)

# for the command line UI
set(CARGO_BUILD_STATIC_LIB ON)
set(CARGO_TEST OFF)
add_subdirectory(cargo)

# for zip file
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(zlib)
set(MINIZIP_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/minizip)
add_subdirectory(minizip-cmake)

# for cross-platform dirent.h
set(DIRENT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/dirent)
add_subdirectory(dirent-cmake)

# for decryption/encryption
set(USE_STATIC_MBEDTLS_LIBRARY ON)
set(USE_SHARED_MBEDTLS_LIBRARY OFF)
set(ENABLE_TESTING OFF)
set(ENABLE_PROGRAMS OFF)
add_subdirectory(mbedtls)
set(mbedtls_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/mbedtls/include PARENT_SCOPE)

# for code-message
set(CODE_MESSAGE_ENTRY "${libfwtool_SOURCE_DIR}/messages/message_all.h")
add_subdirectory(libcodemsg)

project(libfwtool)

set(fw_archive_SRCS
        archive/ZipFile.cc
        archive/ZipFile.hh
)

set(libfwtool_SRCS
        pack.cc
        pack.h
        ${fw_archive_SRCS}
)

include_directories(
        ${libcodemsg_SOURCE_DIR}
        ${libcodemsg_BINARY_DIR}
        ${zlib_SOURCE_DIR}
)

add_library(libfwtool ${libfwtool_SRCS})

# specify the libs to be linked
target_link_libraries(libfwtool
        libcodemsg
        zlibstatic
        minizip
)

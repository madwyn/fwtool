project(libfwtool)

set(fw_archive_SRCS
        archive/ZipFile.cc
        archive/ZipFile.hh
)

set(libfwtool_SRCS
        ${fw_archive_SRCS}
)

include_directories(
        ${libcodemsg_SOURCE_DIR}
        ${libcodemsg_BINARY_DIR}
)

add_library(libfwtool ${libfwtool_SRCS})


project(fwtool)

set(fwtool_SRCS
        main.c
)

include_directories(
        ${cargo_SOURCE_DIR}
        ${libfwtool_SOURCE_DIR}
)

add_executable(fwtool ${fwtool_SRCS})

# specify the libs to be linked
target_link_libraries(fwtool
        cargo
        libfwtool
)

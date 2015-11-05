project(deps)

# for the command line UI
set(CARGO_BUILD_STATIC_LIB TRUE)
set(CARGO_TEST FALSE)
add_subdirectory(cargo)

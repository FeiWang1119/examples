project(binding-to-globals)

find_package(PkgConfig REQUIRED)

pkg_check_modules(wayland-client REQUIRED IMPORTED_TARGET wayland-client)

add_executable(binding-to-globals main.c)

target_link_libraries(binding-to-globals PUBLIC
    PkgConfig::wayland-client
)

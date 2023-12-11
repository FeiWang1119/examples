project(wayland-client)

find_package(PkgConfig REQUIRED)

pkg_check_modules(wayland-client REQUIRED IMPORTED_TARGET wayland-client)

add_executable(wayland-client main.c)

target_link_libraries(wayland-client PUBLIC
    PkgConfig::wayland-client
)

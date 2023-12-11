project(wayland-server)

find_package(PkgConfig REQUIRED)

pkg_check_modules(wayland-server REQUIRED IMPORTED_TARGET wayland-server)

add_executable(wayland-server main.c)

target_link_libraries(wayland-server PUBLIC
    PkgConfig::wayland-server
)

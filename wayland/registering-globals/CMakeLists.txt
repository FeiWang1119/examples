project(registering-globals)

find_package(PkgConfig REQUIRED)

pkg_check_modules(wayland-server REQUIRED IMPORTED_TARGET wayland-server)
pkg_check_modules(wayland-client REQUIRED IMPORTED_TARGET wayland-client)

add_executable(registering-globals main.c)

target_link_libraries(registering-globals PUBLIC
    PkgConfig::wayland-server
    PkgConfig::wayland-client
)

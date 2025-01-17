project(client)

find_package(PkgConfig REQUIRED)

pkg_check_modules(wayland-client REQUIRED IMPORTED_TARGET wayland-client)

add_executable(client main.c)

target_link_libraries(client PUBLIC
    PkgConfig::wayland-client
)

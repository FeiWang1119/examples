project(select-based-server)

find_package(Libevent 2.2 REQUIRED COMPONENTS core)

add_executable(select-based-server select-based-server.c)

target_link_libraries(select-based-server libevent::core)

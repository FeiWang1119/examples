project(libevent-server)

find_package(Libevent 2.2 REQUIRED COMPONENTS core)

add_executable(libevent-server libevent-server.c)

target_link_libraries(libevent-server libevent::core)

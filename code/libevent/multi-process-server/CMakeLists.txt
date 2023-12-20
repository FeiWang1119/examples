project(multi-process-server)

find_package(Libevent 2.2 REQUIRED COMPONENTS core)

add_executable(multi-process-server multi-process-server.c)

target_link_libraries(multi-process-server libevent::core)

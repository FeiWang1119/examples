project(hello-world)

find_package(Libevent 2.2 REQUIRED COMPONENTS core)

add_executable(hello-world hello-world.c)

target_link_libraries(hello-world libevent::core)

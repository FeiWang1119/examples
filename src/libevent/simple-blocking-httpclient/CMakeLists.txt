project(simple-blocking-httpclient)

find_package(Libevent 2.2 REQUIRED COMPONENTS core)

add_executable(simple-blocking-httpclient simple-blocking-httpclient.c)

target_link_libraries(simple-blocking-httpclient libevent::core)

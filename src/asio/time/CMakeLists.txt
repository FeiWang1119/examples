project(time)

add_executable(time1 time1.cpp)
add_executable(time2 time2.cpp)

target_link_libraries(time1 INTERFACE Boost::boost Boost::system)
target_link_libraries(time2 INTERFACE Boost::boost Boost::system)


cmake_minimum_required(VERSION 3.7)

project(asio)

find_package(Boost 1.54.0 COMPONENTS system REQUIRED)

target_link_libraries(asio INTERFACE Boost::boost Boost::system)
    

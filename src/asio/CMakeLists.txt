cmake_minimum_required(VERSION 3.7)

project(asio)

find_package(
  Boost 1.54.0
  COMPONENTS system
  REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(time)

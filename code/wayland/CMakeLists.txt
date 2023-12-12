cmake_minimum_required(VERSION 3.5)

project(
  wayland
  VERSION 1.0.0
  DESCRIPTION "wayland programming"
  HOMEPAGE_URL "https://github.com/feiwang1119/job-data.git"
  LANGUAGES C)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(binding-to-globals)

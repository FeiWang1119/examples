cmake_minimum_required(VERSION 3.5)

project(
  unix-environment
  VERSION 1.0.0
  DESCRIPTION "xcb programming"
  HOMEPAGE_URL "https://github.com/feiwang1119/xcb-example.git"
  LANGUAGES C)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(xcb-xlib)
add_subdirectory(xcb-examples)

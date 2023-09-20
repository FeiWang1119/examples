cmake_minimum_required(VERSION 3.5)

project(
  unix-environment
  VERSION 1.0.0
  DESCRIPTION "unix system programming"
  HOMEPAGE_URL "https://github.com/feiwang1119/unix-environment"
  LANGUAGES C)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(chapter1)
add_subdirectory(chapter3)
add_subdirectory(chapter4)
add_subdirectory(chapter5)
add_subdirectory(chapter11)

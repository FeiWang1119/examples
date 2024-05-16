cmake_minimum_required(VERSION 3.5)

project(
  unix-system
  VERSION 1.0.0
  DESCRIPTION "unix system programming"
  HOMEPAGE_URL "https://github.com/feiwang1119/unix-environment"
  LANGUAGES C)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

file(GLOB_RECURSE COMMON_SRC ${CMAKE_SOURCE_DIR}/utils/*.h ${CMAKE_SOURCE_DIR}/utils/*.c)

add_subdirectory(ipc)

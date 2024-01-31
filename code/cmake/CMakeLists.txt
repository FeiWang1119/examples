cmake_minimum_required(VERSION 3.25)

project(CMakeExample)

set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG" )

# set normal
set(variable_normal 1)
message(DEBUG variable_normal: ${variable_normal})
unset(variable_normal)


# set cache
set(variable_cache 1)
message(DEBUG variable_cache: ${variable_cache})
set(variable_cache 2 CACHE STRING "for testing cache")
message(DEBUG variable_cache: ${variable_cache})
set(variable_cache 3)
message(DEBUG variable_cache: ${variable_cache})

# Directory Scope
set(parent_variable 4)

# option
option(BUILD_SHARED_LIBS "Build Qt statically or dynamically" ON)
set(QT_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
message(DEBUG option: ${QT_BUILD_SHARED_LIBS})

add_subdirectory(example)

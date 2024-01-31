cmake_minimum_required(VERSION 3.25)

project(CMakeExample)

# set normal
set(variable_normal 1)
message(variable_normal: ${variable_normal})
unset(variable_normal)


# set cache
set(variable_cache 1)
message(variable_cache: ${variable_cache})
set(variable_cache 2 CACHE STRING "for testing cache")
message(variable_cache: ${variable_cache})
set(variable_cache 3)
message(variable_cache: ${variable_cache})

# Directory Scope
set(parent_variable 4)


add_subdirectory(example)

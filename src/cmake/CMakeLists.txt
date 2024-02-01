cmake_minimum_required(VERSION 3.25)

project(CMakeExample)

set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")

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

# PROPERTY
set_property(DIRECTORY example PROPERTY EXCLUDE_FROM_ALL TRUE)
get_property(exclude_from_all DIRECTORY example PROPERTY EXCLUDE_FROM_ALL)
message(DEBUG property: ${exclude_from_all})

# parent_scope
message(DEBUG parent_scope: ${variable_parent})
message(DEBUG parent_no_scope: ${variable_no_parent})

# get_filename_component
# set(_infile)
set(_xml_file ./org.example.chat.xml)
get_filename_component(_infile ${_xml_file} ABSOLUTE)
message(DEBUG "file absolute: " ${_infile})

# function
function(TestFunction _sources _xml_file _include) # _optionalParentClass _optionalRelativename _optionalClassName)
  message(DEBUG "ARGV0:${ARGV0}")
  message(DEBUG "ARGV1:${ARGV1}")
  message(DEBUG "ARGV2:${ARGV2}")
endfunction()

TestFunction("a" "b" "c")

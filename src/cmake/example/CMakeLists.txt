#

# set normal
message(subdirectory: parent_variable: ${parent_variable})

get_property(exclude_from_all DIRECTORY PROPERTY EXCLUDE_FROM_ALL)
message(DEBUG subdir property: ${exclude_from_all})

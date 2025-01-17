#

# set normal
message(subdirectory: parent_variable: ${parent_variable})

get_property(exclude_from_all DIRECTORY PROPERTY EXCLUDE_FROM_ALL)
message(DEBUG subdir property: ${exclude_from_all})

# parent_scope
set(variable_parent 5 PARENT_SCOPE)
set(variable_no_parent 6)

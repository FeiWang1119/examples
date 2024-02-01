project(chapter3)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(test_input_lseek test_input_lseek.c)
add_executable(create_hole_file create_hole_file.c)
add_executable(copy copy.c)
add_executable(fcntl fcntl.c)

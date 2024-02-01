project(chapter4)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(filetype filetype.c)
add_executable(test_access test_access.c)
add_executable(test_umask test_umask.c)
add_executable(test_chmod test_chmod.c)
add_executable(test_unlink test_unlink.c)
add_executable(test_futimens test_futimens.c)
add_executable(test_chdir test_chdir.c)
add_executable(test_getcwd test_getcwd.c)
add_executable(test_st_dev test_st_dev.c)

project(chapter11)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(print_thread_ID print_thread_ID.c)
add_executable(get_exit_code get_exit_code.c)
add_executable(exit_code_error exit_code_error.c)
add_executable(pthread_cleanup pthread_cleanup.c)
add_executable(pthread_mutex_timedlock pthread_mutex_timedlock.c)
add_executable(pthread_barrier pthread_barrier.c)

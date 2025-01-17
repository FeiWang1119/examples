project(chapter1)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ls ls.c)
add_executable(in2out_sys in2out_sys.c)
add_executable(in2out_std in2out_std.c)
add_executable(print_procID print_procID.c)
add_executable(shell shell.c)
add_executable(uid_gid uid_gid.c)
add_executable(signal_shell signal_shell.c)

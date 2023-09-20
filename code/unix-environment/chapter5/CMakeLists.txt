project(chapter5)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(getc_putc getc_putc.c)
add_executable(fgetc_fputc fgetc_fputc.c)
add_executable(fgets_fputs fgets_fputs.c)

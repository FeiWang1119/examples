#include "apue.h"

int main(int argc, char *argv[]) {
  char *ptr;
  size_t size;
  if (chdir("/usr/include") < 0) {
    err_sys("chdir failed");
  }
  ptr = path_alloc(&size);
  if (getcwd(ptr, size) == NULL) {
    err_sys("getcwd failed");
  }
  printf("cwd = %s\n", ptr);
  return EXIT_SUCCESS;
}

#include "apue.h"
#include <unistd.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
  int n;
  char buf[BUFFSIZE];

  while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
    if (write(STDOUT_FILENO, buf, n) != n) {
      err_sys("wirte error");
    }
  }
  if (n < 0) {
    err_sys("read error");
  }
  return 0;
}

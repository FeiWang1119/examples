#include "apue.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

static void sig_int(int);

int main(int argc, char *argv[]) {
  char buf[MAXLINE];
  pid_t pid;
  int status;

  if (signal(SIGINT, sig_int)) {
    err_sys("signal error");
  }

  printf("%% ");
  while (fgets(buf, MAXLINE, stdin)) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = 0; // replace newline with null
    }
    if ((pid = fork()) < 0) {
      err_sys("for error");
    } else if (pid == 0) { // child
      execlp(buf, buf, (char *)0);
      err_ret("couldn't execute: %s", buf);
      exit(127);
    }

    // parent
    if ((pid = waitpid(pid, &status, 0)) < 0) {
      err_sys("waitpid error");
    }
    printf("%% ");
  }
  exit(0);
}

void sig_int(int signo) { printf("interrupt\n%% "); }

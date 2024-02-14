#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  int p[2];
  pipe(p);
  if (fork() == 0) {
    // parent process
    int pid = getpid();
    char buf = 1;
    write(p[1], &buf, 1);
    close(p[1]);
    read(p[0], &buf, 1);
    close(p[0]);
    fprintf(1, "%d: received pong\n", pid);
  } else {
    int pid = getpid();
    char buf = 0;
    read(p[1], &buf, 1);
    close(p[1]);
    fprintf(1, "%d: received ping\n", pid);
    buf = 0;
    write(p[0], &buf, 1);
    close(p[0]);
  }
  exit(0);
}
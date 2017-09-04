#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define WEB_REF 100

int main(void)
{
  int fd_pipe[2];
  int status_pipe;
  int pid;
  char www[WEB_REF];
  int stat;

  status_pipe = pipe(fd_pipe);

  if (status_pipe == -1)
  {
    exit(1);
  }

  pid = fork();

  if (pid==-1)
  {
    exit(1);
  }
  else if(pid)
  {
    puts("Enter the address (ulr) a page web: ");
    scanf("%s", www);
    close(fd_pipe[0]);
    write(fd_pipe[1], www, WEB_REF);
    close(fd_pipe[1]);
    waitpid(pid, &stat, 0);
    exit(0);
  }
  else if (!pid)
  {
    close(fd_pipe[1]);
    read(fd_pipe[0], www, WEB_REF);
    close(fd_pipe[0]);
    execlp("x-www-browser", "x-www-browser", www, NULL);
    exit(0);
  }

  return 0;
}

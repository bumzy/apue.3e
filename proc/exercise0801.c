#include "apue.h"

int     globvar = 6;        /* external variable in initialized data */

int
main(void)
{
    int     var, i, fd;        /* automatic variable on the stack */
    pid_t   pid;
    char buf[256];

    var = 88;
    fd = dup(STDOUT_FILENO);
    printf("before vfork\n");   /* we don't flush stdio */
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {      /* child */
        globvar++;              /* modify parent's variables */
        var++;
        fclose(stdout);
        exit(0);                /* child terminates */
    }

    /* parent continues here */
    i = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,
      var);
    sprintf(buf, "%d\n", i);
    write(fd, buf, strlen(buf));
    exit(0);
}

/*************************************************************************
	> File Name: exercise0902.c
	> Author: bumzy
	> Mail: bumzycm@gmail.com
	> Created Time: Tue 24 Apr 2018 09:08:06 PM CST
 ************************************************************************/
#include "apue.h"
#include <errno.h>
#include <unistd.h>

static void
pr_ids(char *name)
{
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
	    name, (long)getpid(), (long)getppid(), (long)getpgrp(),
	    (long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main() {
    char c;
    pid_t pid;

    pr_ids("parent");
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        sleep(5);
    } else {
        pr_ids("child");
        setsid();
        pr_ids("child");
        if (read(STDIN_FILENO, &c, 1) != 1) {
            printf("read error %d on controlling TTY\n", errno);
        }
    }
    exit(0);
}

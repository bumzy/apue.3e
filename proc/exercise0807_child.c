/*
refer: http://www.cnblogs.com/JesseEisen/p/3688513.html
 */
#include "apue.h"
#include <fcntl.h>

int
main(int argc ,char *argv[]) {
    int fd,val;

    sscanf(argv[1], "%d", &fd);
    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("fcntl");
    if (val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("clsose-on-exec is off\n");

    return 0;
}

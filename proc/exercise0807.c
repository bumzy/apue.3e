/*
refer: http://www.cnblogs.com/JesseEisen/p/3688513.html
 */
#include "apue.h"
#include <dirent.h>
#include <fcntl.h>

int main(void)
{
    DIR *dir;
    int val, fd;
    char buf[10];
    pid_t pid;

    if ((dir = opendir("/")) == NULL)
        err_sys("opendir error");
    if ((fd = dirfd(dir)) == -1)
        err_sys("dirfd error");
    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("fcntl error");
    if (val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("clsose-on-exec is off\n");

    sprintf(buf,"%d",fd);

    /*
    val &= ~FD_CLOEXEC;
    fcntl(fd, F_SETFD, val);
     */

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        execl("./exercise0807_child","exercise0807_child", buf, NULL);
        exit(0);
    }

return 0;
}

#include "apue.h"
#include <sys/wait.h>

static void handler(int signo, siginfo_t *info, void *context);

int
main(void)
{
    pid_t   pid;
    int     status;
    struct sigaction act, oact;

    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGCLD, &act, &oact) < 0)
        return(SIG_ERR);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)                /* child */
        exit(7);

    if (waitpid(pid, NULL, 0) != pid) /* wait for child */
        err_sys("waitpid error");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)                /* child */
        abort();                      /* generates SIGABRT */

    if (waitpid(pid, NULL, 0) != pid) /* wait for child */
        err_sys("waitpid error");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)                /* child */
        status /= 0;                  /* divide by 0 generates SIGFPE */

    if (waitpid(pid, NULL, 0) != pid) /* wait for child */
        err_sys("waitpid error");

    exit(0);
}

static void
handler(int signo, siginfo_t *info, void *context) {
    int status = info->si_status;
    int code = info->si_code;
    if (code == CLD_KILLED || code == CLD_DUMPED)
        printf("abnormal termination, signal number = %d%s\n", status,
                code == CLD_DUMPED ? " (core file generated)" : "");
    else
        printf("normal termination, exit status = %d\n", status);
}

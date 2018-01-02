#include <stdio.h>
#include <sys/utsname.h>

int main(int argc, char const *argv[])
{
    struct utsname name;
    uname(&name);
    printf("%s %s %s %s %s\n",
        name.sysname,
        name.nodename,
        name.release,
        name.version,
        name.machine);
    return 0;
}

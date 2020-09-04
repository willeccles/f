#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

void printitem(char* name, char* val) {
    if (name && val) {
        printf("\033[36m%s\033[m: %s\n", name, val);
    }
}

int main(void) {
    struct utsname un;
    if (uname(&un) == -1) {
        perror("error getting system info");
        return 1;
    }

    struct passwd* pw = getpwuid(getuid());
    if (!pw) {
        perror("error getting user info");
        return 1;
    }

    char* editor = getenv("EDITOR");

    printf("\033[32m%s\033[m@\033[32m%s\033m\n",
            pw->pw_name, un.nodename);

    printitem("os", un.sysname);
    printitem("release", un.release);
    printitem("version", un.version);
    printitem("machine", un.machine);
    printitem("editor", editor);
    printitem("shell", pw->pw_shell);

    return 0;
}

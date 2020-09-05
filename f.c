#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <libgen.h>

void printitem(char* name, char* val) {
    if (name && *name && val && *val) {
        printf("\033[36m%7s\033[m | %s\n", name, val);
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
    if (editor && *editor) editor = basename(editor);

    printf("\033[32m%s\033[m@\033[32m%s\033m\n",
            pw->pw_name, un.nodename);

    char* os = malloc(strlen(un.sysname) + strlen(un.release) + 2);
    if (!os) {
        perror("malloc");
        return 1;
    }

    sprintf(os, "%s %s", un.sysname, un.release);

    printitem("os", os);
    printitem("arch", un.machine);
    printitem("editor", editor);
    printitem("shell", basename(pw->pw_shell));

    for (int i = 0; i < 6; i++) {
        printf(" \033[%dm▄▄\033[m", 31 + i);
    }
    printf("\n");
    for (int i = 0; i < 6; i++) {
        printf(" \033[%dm▀▀\033[m", 91 + i);
    }
    printf("\n");

    free(os);

    return 0;
}

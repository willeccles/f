#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

void printitem(char* name, char* val) {
    if (name && val) {
        printf("\033[36m%s\033[m: %s\n", name, val);
    }
}

int main(void) {
    char hostname[256] = {0};
    // TODO use uname(2) to get more bang for your buck
    gethostname(hostname, 255);

    struct passwd* pw = getpwuid(getuid());
    if (!pw) {
        perror("error getting user info");
        return 1;
    }

    char* editor = getenv("EDITOR");

    printf("\033[32m%s\033[m@\033[32m%s\033m\n",
            pw->pw_name, hostname);

    printitem("editor", editor);
    printitem("shell", pw->pw_shell);

    return 0;
}

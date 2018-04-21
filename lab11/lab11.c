#include "sys/types.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "wait.h"

int execvpe(const char *file, char *const argv[], char *envp[]) {
    extern char **environ;
    environ = envp;
    return execvp(file, argv);
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("you need to specify executed program\n");
        exit(1);
    }

    pid_t pid;

    char *nenv[ ]  = {
        "NAME=value",
        "nextname=nextvalue",
        "HOME=/xyz",
        (char *) 0 
    };

    execvpe(argv[1], argv + 1, nenv);
    perror(argv[0]);
    exit(1);
}

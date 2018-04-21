#include "sys/types.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "wait.h"

int main(int argc, char **argv) {

    pid_t pid;

    if ((pid = fork()) > 0) {
        wait(NULL);
        for(int i = 0; i < 10; ++i) {
            printf("1111111111111111111111lbdlbdlbdlbdlbdlbdlbdlbdl\n");
        }

    } else if (pid == 0) {
        execlp("cat", "cat", "../lab8/lab8.c", (char *)NULL);
        perror("exec cat failed");
        exit(1);

    } else {
        perror(argv[0]);
        exit(1);
    }
    return 0;
}

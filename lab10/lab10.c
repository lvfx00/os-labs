#include "sys/types.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "wait.h"

int main(int argc, char **argv) {

    pid_t pid;

    if (argc < 2) {
        printf("you need to specify executed program\n");
        exit(1);
    }

    if ((pid = fork()) > 0) {
        int child_status;
        wait(&child_status);

        if (WIFEXITED(child_status)) {
            printf("child's exited status is: %d\n", 
                    WEXITSTATUS(child_status));
        } 
        else if (WIFSIGNALED(child_status)) {
            printf("child'signal is: %d\n", 
                    WTERMSIG(child_status));
        }

    } else if (pid == 0) {
        execvp(argv[1], argv + 1);
        perror("exec new program failed");
        exit(1);

    } else {
        perror(argv[0]);
        exit(1);
    }
    return 0;
}

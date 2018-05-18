#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define READ_BUF_SIZE 1000

int main(int argc, char **argv) {
  int fd[2];
  pid_t pid;

  char *lines[3] = {"Here are 3 lines of text.\n",
                    "You will see all lower case\n", "made to upper!!\n"};

  if (pipe(fd) == -1) {
    perror(argv[0]);
    exit(1);
  }

  if ((pid = fork()) > 0) { /* parent */
    close(fd[0]);
    for (int i = 0; i < 3; i++) {
      write(fd[1], lines[i], strlen(lines[i]));
    }
    close(fd[1]);

  } else if (pid == 0) { /* child */
    close(fd[1]);

    char input[READ_BUF_SIZE];
    int rtn;

    while ((rtn = read(fd[0], input, READ_BUF_SIZE)) > 0) {
      for (int i = 0; i < rtn; i++) {
        if (islower(input[i])) {
          input[i] = toupper(input[i]);
        }
      }
      write(1, input, rtn);
    }
    close(fd[0]);

  } else { /* cannot fork */
    perror(argv[0]);
    exit(2);
  }

  exit(0);
}

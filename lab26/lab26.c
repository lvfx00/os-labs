#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *fptr;
  char *lines[3] = {"Here are 3 lines of text.\n",
                    "You will see all lower case\n", "made to upper!!\n"};

  if ((fptr = popen("./toup", "w")) == (FILE *)NULL) {
    perror(argv[0]);
    exit(1);
  }

  for (int i = 0; i < 3; i++) {
    fputs(lines[i], fptr);
  }

  pclose(fptr);
  return 0;
}

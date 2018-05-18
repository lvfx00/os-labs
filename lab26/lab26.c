#include <stdio.h>

int main() {
  FILE *fptr;
  char *lines[3] = {"Here are 3 lines of text.\n",
                    "You will see all lower case\n", "made to upper!!\n"};

  fptr = popen("./toup", "w");

  for (int i = 0; i < 3; i++) {
    fputs(lines[i], fptr);
  }

  pclose(fptr);
  return 0;
}


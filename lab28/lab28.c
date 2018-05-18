// !!!for solarkaOS system only!!!

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  FILE *ptrs[2];
  char num[4];

  srand(time(0));

  if (p2open("/bin/sort", ptrs) == -1) {
    perror("/bin/sort");
    exit(1);
  }

  int i;
  for (i = 0; i < 100; i++) {
    sprintf(num, "%02d\n", rand() % 100);
    fputs(num, ptrs[0]);
  }

  fclose(ptrs[0]); // needed for sort to find EOF

  while (fgets(num, 4, ptrs[1]) != NULL) {
    num[2] = '\0';
    printf("%s\t", num);
  }
  printf("\n");

  return 0;
}

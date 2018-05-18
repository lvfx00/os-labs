#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 512

int main(int argc, char **argv) {
  FILE *fpin, *fpout;
  char line[BUFSIZE];

  if(argc < 2) {
    fprintf(stderr, "usage: %s filename [filename...]\n", argv[0]);
    exit(1);
  }

  if ((fpin = fopen(argv[1], "r")) == (FILE *)NULL) {
    perror(argv[0]);
    exit(1);
  }

  if ((fpout = popen("wc -l", "w")) == (FILE *)NULL) {
    perror("wc -l");
    exit(1);
  }

  while (fgets(line, BUFSIZ, fpin) != (char *)NULL) {
    if (line[0] == '\n') {
      fputs(line, fpout);
    }
  }

  fclose(fpin);
  pclose(fpout);
}

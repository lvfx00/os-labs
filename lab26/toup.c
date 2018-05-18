#include <ctype.h>
#include <unistd.h>

#define READ_BUF_SIZE 1000

int main() {
  char input[READ_BUF_SIZE];
  int rtn;

  while ((rtn = read(0, input, 1000)) > 0) {
    for (int i = 0; i < rtn; i++) {
      if (islower(input[i])) {
        input[i] = toupper(input[i]);
      }
    }
    write(1, input, rtn);
  }

  return 0;
}

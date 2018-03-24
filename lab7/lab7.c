#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#define MAX_LEN 100

volatile sig_atomic_t fd;

void print_file() {
    char ch;
    lseek(fd, 0L, SEEK_SET);
    int size = lseek(fd, 0, SEEK_END);
    char *p = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    for(int i = 0; i < size; ++i) {
        printf("%c", p[i]);
    }
    // close program
    exit(0);
}

int main(int argc, char *argv[])
{
    static struct sigaction sa;

    sa.sa_handler = print_file;
    sigaction(SIGALRM, &sa, NULL);

    if(( fd =  open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    char *offsets[MAX_LEN + 1];
    int line_length[MAX_LEN + 1];
    char c, buf[257];


    int size = lseek(fd, 0, SEEK_END);
    char *p = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);

    int i = 1; // iterator for curr string num
    int j = 1; // iterator for number of symbols in curr string

    // offsets array contains a pointers to the line beginnings
    offsets[1] = p;
    for(int count = 0; count < size; count++) {
        if( *(p+count) == '\n' ) {
            line_length[i++] = j;
            offsets[i] = count + p + 1;
            j = 1;
        }
        else {
            j++;
        }
    }
    // if last string not ends by '\n' it won't be printed (like in cat)
    int number_of_lines = i - 1;

    while (1) {
        printf("Line number: ");
        alarm(5);

        int line_num;
        if(scanf("%d", &line_num)) {
            alarm(0);
            if(line_num <= 0 || line_num > number_of_lines) {
                exit(0);
            }
            write(0, offsets[line_num], line_length[line_num]);
        } else {
            exit(0);
        }
    }

    return 0;
}

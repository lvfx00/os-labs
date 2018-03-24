#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

volatile sig_atomic_t fd;

void print_file() {
    char ch;
    lseek(fd, 0L, SEEK_SET);
    while (read(fd, &ch, 1)) {
        printf("%c", ch);
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

    long offsets[MAX_LEN + 1];
    int line_length[MAX_LEN + 1];
    char c, buf[257];

    offsets[1] = 0L;
    int i = 1; // iterator for curr string num
    int j = 0; // iterator for number of symbols in curr string

    while(read(fd, &c, 1) && i <= MAX_LEN) {
        j++;
        if( c == '\n' ) {
            line_length[i++] = j;
            offsets[i] = lseek(fd, 0L, SEEK_CUR);
            j = 0;
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

            // set current position in the file to beginning of entered line number
            lseek(fd, offsets[line_num], SEEK_SET);
            // read line to buffer
            if(read(fd, buf, line_length[line_num])) {
                // write buffer to stdout
                write(1, buf, line_length[line_num]);
            }
            else {
                fprintf(stderr, "Bad Line Number\n");
            }
        } else {
            exit(0);
        }
    }

    return 0;
}

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int main(int argc, char *argv[])
{
    int fd;
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

    int line_num;
    while( printf("Line number : ") && scanf("%d", &line_num)) {
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
    }
    return 0;
}

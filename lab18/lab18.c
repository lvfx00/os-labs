#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <libgen.h>

char* formatdate(char* str, time_t val)
{
        strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        return str;
}

int main(int argc, char **argv) {

    for(int i = 1; i < argc; ++i) {

        struct stat stbuf;

        if (stat(argv[i], &stbuf) == -1) {
            perror(argv[i]);
            exit(1);
        }

        // print type of file
        switch(stbuf.st_mode & S_IFMT) {
            case S_IFDIR:
                printf("d");
                break;
            case S_IFREG:
                printf("-");
                break;
            default:
                printf("?");
                break;
        }

        // print file access permissions
        printf("%c%c%c%c%c%c%c%c%c",
                stbuf.st_mode & S_IRUSR ? 'r' : '-',
                stbuf.st_mode & S_IWUSR ? 'w' : '-',
                stbuf.st_mode & S_IXUSR ? 'x' : '-',
                stbuf.st_mode & S_IRGRP ? 'r' : '-',
                stbuf.st_mode & S_IWGRP ? 'w' : '-',
                stbuf.st_mode & S_IXGRP ? 'x' : '-',
                stbuf.st_mode & S_IROTH ? 'r' : '-',
                stbuf.st_mode & S_IWOTH ? 'w' : '-',
                stbuf.st_mode & S_IXOTH ? 'x' : '-');

        // print number of links to file
        printf(" %lu", stbuf.st_nlink); 

        // print owner name
        printf(" %s", getpwuid(stbuf.st_uid)->pw_name);
        
        // print owner group
        printf(" %s", getgrgid(stbuf.st_gid)->gr_name);

        // print size of regular file
        if ((stbuf.st_mode & S_IFMT) == S_IFREG) {
            printf(" %ld", stbuf.st_size);
        }
        
        // print date and time of last file modification
        char time_str[36];
        formatdate(time_str, stbuf.st_mtime);
        printf(" %s", time_str);

        // print name of file
        printf(" %s\n", basename(argv[i]));
    }

    return 0;
}

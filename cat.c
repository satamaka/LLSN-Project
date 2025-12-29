#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void do_cat(int fd);

int main(int argc, char *argv[])
{
    int fd;

    if (argc == 1) {
        do_cat(0);
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-") == 0) {
            do_cat(0);
        } else {
            fd = open(argv[i], O_RDONLY);
            if (fd < 0) {
                perror(argv[i]); 
                fprintf(stderr, "Skipping file: %s\n", argv[i]);
                continue;
            }
        
        do_cat(fd);
        close(fd);
        }
    }

    return EXIT_SUCCESS;
}

void do_cat(int fd)
{
    char buf[4096];
    ssize_t n;
    while (0 < (n = read(fd, buf, 4096))) {
        if(write(1, buf, n) == -1) {
            perror("write");
			exit(EXIT_FAILURE);
        }
    }
    if (n == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

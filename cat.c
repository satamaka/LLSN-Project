#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 4096

void do_cat(int fd);

int main(int argc, char *argv[])
{
    int fd;
    int exit_status = EXIT_SUCCESS;

    if (argc == 1) {
        do_cat(STDIN_FILENO);
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-") == 0) {
            do_cat(STDIN_FILENO);
        } else {
            fd = open(argv[i], O_RDONLY);
            if (fd < 0) {
                perror(argv[i]);
                exit_status = EXIT_FAILURE;
                fprintf(stderr, "Skipping file: %s\n", argv[i]);
                continue;
            }
        
        do_cat(fd);
        close(fd);
        }
    }

    return exit_status;
}

void do_cat(int fd)
{
    char buf[BUF_SIZE];
    ssize_t n;

    while (0 < (n = read(fd, buf, sizeof(buf)))) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            perror("write");
			exit(EXIT_FAILURE);
        }
    }
    
    if (n == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

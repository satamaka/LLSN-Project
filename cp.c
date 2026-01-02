#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 4096

void do_cp(int src_fd, int dest_fd);
void die(const char *msg);


int main(int argc, char *argv[])
{
	int src_fd = -1, dest_fd = -1;
	int exit_status = EXIT_FAILURE;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <src> <dest>\n", argv[0]);
		return EXIT_FAILURE;
	}

	if ((src_fd = open(argv[1], O_RDONLY)) < 0) {
		perror(argv[1]);
		goto cleanup;
	}

	if ((dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
		perror(argv[2]);
		goto cleanup;
	}

	do_cp(src_fd, dest_fd);
	exit_status = EXIT_SUCCESS;

cleanup:
	if (0 <= src_fd) 
		close(src_fd);
    
	if (0 <= dest_fd)
		close(dest_fd);

	return exit_status;
}

void do_cp(int src_fd, int dest_fd)
{
	char buf[BUF_SIZE];
	ssize_t n_read, n_written;
	char *ptr;

	while (0 < (n_read = read(src_fd, buf, sizeof(buf)))) {
		ptr = buf;
		while (0 < n_read) {
			n_written = write(dest_fd, ptr, n_read);
			if (n_written <= 0) {
				die("write");
			}
			
			n_read -= n_written;
			ptr += n_written;
		}
	}
    
	if (n_read < 0)
		die("read");
}

void die(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
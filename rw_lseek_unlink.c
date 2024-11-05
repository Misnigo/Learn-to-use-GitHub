#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
	int fd = open("tempfile", O_RDWR | O_CREAT, 0660), b;
	if (fd < 0) {
		perror("open failed");
		exit(-1);
	}
	off_t offset;
	if ((offset = lseek(fd, 0, SEEK_CUR)) < 0) {
		perror("lseek failed");
		exit(-1);
	}
	printf("offset after open: %ld\n", offset);
	if (unlink("tempfile") < 0) {
		perror("unlink failed");
		exit(-1);
	}
	printf("file unlinked\n");
	char buff[32] = "this is the fucking buff";
	printf("buff: %s\n", buff);
	char read_buff[32];
	if ((b = write(fd, buff, sizeof(buff))) < 0) {
		perror("write failed");
		exit(-1);
	}
	printf("bytes have written: %d\n", b);
	if ((offset = lseek(fd, 0, SEEK_CUR)) < 0) {
		perror("lseek failed");
		exit(-1);
	}
	printf("offset after write: %ld\n", offset);
	lseek(fd, 0, SEEK_SET);
	if (read(fd, read_buff, sizeof(read_buff)) < 0) {
		perror("read failed");
		exit(-1);
	}
	printf("bytes have written: %d\n", b);
	if ((offset = lseek(fd, 0, SEEK_CUR)) < 0) {
		perror("lseek failed");
		exit(-1);
	}
	printf("offset after read: %ld\n", offset);

	printf("read: %s\n", read_buff);	
	sleep(5);
	printf("done\n");
	exit(0);
}

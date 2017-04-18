#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "kernel/ioctl_basic.h"
#include "kernel/hexdump_common.h"
#include "hexdump.h"

int hexdump_valid_line_size(int size)
{
	if (size != 8 && size != 16)
		return 0;

	return 1;
}

int hexdump_line_kernel(char *in, int size, char *out, int line_size, int fd)
{
	struct ioctl_param p;
	p.in = in;
	p.size = size;
	p.out = out;
	p.line_size = line_size;

	return ioctl(fd, IOCTL_HEXDUMP, &p);
}

int hexdump(char *input, int size, FILE *out, int line_size, int kernel_mode)
{
	int line_no = 0;
	int fd;
	if (!out)
		return -1;

	if (hexdump_valid_line_size(line_size) == 0)
		return -1;

	if (kernel_mode) {
		fd = open("/dev/hexdump", O_RDWR);
		if (fd < 0) {
			printf("Error in opening file %d %s\n", errno, strerror(errno));
			return errno;
		}
	}


	while (size > 0) {
		char line_buf[200];
		memset(line_buf, 0, 200);
		sprintf(line_buf, "%06x  ", line_no * line_size);

		if (kernel_mode)
			hexdump_line_kernel(input + line_no * line_size, size, line_buf + 8, line_size, fd);
		else
			hexdump_line(input + line_no * line_size, size, line_buf + 8, line_size);
		fprintf(out, "%s\n", line_buf);

		line_no++;
		size -= line_size;
	}

	if (kernel_mode)
		close(fd);

	return 0;
}

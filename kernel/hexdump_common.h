#ifndef __HEXDUMP_COMMON_H__
#define __HEXDUMP_COMMON_H__

#ifdef __KERNEL__
#include <linux/string.h>
#include <linux/ctype.h>
#else
#include <string.h>
#include <ctype.h>
#endif

static inline int hexdump_line(char *input, int size, char *output, int line_size)
{
	int i;

	if (input == NULL)
		return -1;

	for (i = 0; i < line_size; i++) {
		if (i < size)
			sprintf(output + i * 3, "%02x ", (unsigned char)input[i]);
		else
			sprintf(output + i * 3, "   ");
	}
	sprintf(output + line_size * 3, " ");

	for (i = 0; i < line_size; i++) {
		if (i < size) {
			if (isprint(input[i]) && isascii(input[i]))
				sprintf(output + i + line_size * 3 + 1, "%c", input[i]);
			else
				sprintf(output + i + line_size * 3 + 1, ".");
		}
		else {
			sprintf(output + i + line_size * 3 + 1, " ");
		}
	}

	return line_size * 4;
}

#endif

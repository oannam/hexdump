#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hexdump.h"

int hexdump(char *input, int size, FILE *out, int line_size)
{
	int line_no = 0;
	if (!out)
		return -1;

	if (line_size != 8 && line_size != 16)
		return -1;

	while (size > 0) {
		char line_buf[200];
		memset(line_buf, 0, 200);
		sprintf(line_buf, "%06x  ", line_no * line_size);

		hexdump_line(input + line_no * line_size, size, line_buf + 8, line_size);
		fprintf(out, "%s\n", line_buf);

		line_no++;
		size -= line_size;
	}

	return 0;
}

int hexdump_line(char *input, int size, char *output, int line_size)
{
	if (input == NULL)
		return -1;

	for (int i = 0; i < line_size; i++) {
		if (i < size)
			sprintf(output + i * 3, "%02x ", (unsigned char)input[i]);
		else
			sprintf(output + i * 3, "   ");
	}
	sprintf(output + line_size * 3, " ");

	for (int i = 0; i < line_size; i++) {
		if (i < size) {
			if (isprint(input[i]))
				sprintf(output + i + line_size * 3 + 1, "%c", input[i]);
			else
				sprintf(output + i + line_size * 3 + 1, ".");
		}
		else {
			sprintf(output + i + line_size * 3 + 1, " ");
		}
	}

	return 0;
}

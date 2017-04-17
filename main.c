#include <stdio.h>
#include <unistd.h>
#include "hexdump.h"

#define INPUT_MAX_SIZE 1024

int hexdump_to_file(char *input_file, char *output_file, int line_size)
{
	FILE *in = fopen(input_file, "rb");
	if (!in)
		return -1;

	char input_buf[INPUT_MAX_SIZE];
	int input_size = fread(input_buf, 1, INPUT_MAX_SIZE, in);
	if (input_size <= 0) {
		fclose(in);
		return -1;
	}

	FILE *out = fopen(output_file, "wt");
	hexdump(input_buf, input_size, out, line_size);

	fclose(in);
	fclose(out);

	return 0;
}

int main(int argc, char *argv[])
{
	int opt;
	char *input_file = NULL;
	char *output_file = NULL;
	int err_flag = 0;
	int line_size = 8;

	while ((opt = getopt (argc, argv, "o:f:h")) != -1) {
		switch (opt) {
		case 'o':
			output_file = optarg;
			break;
		case 'f':
			input_file = optarg;
			break;
		case 'h':
			printf("Usage:\n main -f input.bin -o output.txt\n");
			return 0;
		}
	}

	if (input_file == NULL) {
		printf("Missing input file\n");
		err_flag = 1;
	}
	if (output_file == NULL) {
		printf("Missing output file\n");
		err_flag = 2;
	}
	if (err_flag != 0)
		return err_flag;

	hexdump_to_file(input_file, output_file, line_size);

	return 0;
}

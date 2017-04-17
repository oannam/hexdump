#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int opt;
	char *input_file = NULL;
	char *output_file = NULL;
	int err_flag = 0;

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

	return 0;
}

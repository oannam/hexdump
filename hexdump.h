#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__
int hexdump(char *input, int size, FILE *out, int line_size, int kernel_mode);
int hexdump_valid_line_size(int size);

#endif

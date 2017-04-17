#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__
int hexdump_line(char *input, int size, char *output, int line_size);
int hexdump(char *input, int size, FILE *out, int line_size);

#endif

#include <linux/ioctl.h>
#define IOC_MAGIC 'k'

struct ioctl_param {
	char *in;
	int size;
	char *out;
	int line_size;
};

#define IOCTL_HEXDUMP _IOWR(IOC_MAGIC, 0, struct ioctl_param *)

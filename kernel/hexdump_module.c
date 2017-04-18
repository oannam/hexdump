#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "ioctl_basic.h"
#include "hexdump_common.h"
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#define AUTHOR "Oana Murarasu"
#define DESC "Hexdump Driver"
#define DEVICE_NAME "hexdump"
#define CLASS_NAME "hex"
#define IN_MAX 16
#define OUT_MAX (IN_MAX * 5)

static int Major;

static struct class *dev_class = NULL;
static struct device *dev = NULL;

int device_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Inside open \n");
	return 0;
}

int device_release(struct inode *inode, struct file *filp)
{
	printk (KERN_INFO "Inside close \n");
	return 0;
}

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd) {
		case IOCTL_HEXDUMP:
			{
				struct ioctl_param *param = (struct ioctl_param *)arg;
				int to_copy;
				char temp_in_buff[IN_MAX];
				char temp_out_buff[OUT_MAX];
				memset(temp_out_buff, 0, OUT_MAX);
				if (param->line_size > param->size)
					to_copy = param->size;
				else
					to_copy = param->line_size;
				if (to_copy > IN_MAX)
					to_copy = IN_MAX;
				if (copy_from_user(temp_in_buff, param->in, to_copy) != 0)
					return -EFAULT;

				to_copy = hexdump_line(temp_in_buff, param->size, temp_out_buff, param->line_size);
				if (copy_to_user(param->out, temp_out_buff, to_copy))
					return -EFAULT;
				printk(KERN_INFO "In the ioctl command in %s out %s size %d lien_size %d", param->in, param->out, param->size, param->line_size);
				break;
			}
		default:
			printk(KERN_INFO "Wrong command");
			return 1;
	}

	return 0;
}

struct file_operations fops = {
open: device_open,
      unlocked_ioctl: device_ioctl,
      release: device_release,
};

int init_module(void)
{
	printk(KERN_INFO "Hexdump module init\n");
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk(KERN_ALERT "Registering char device failed with %d\n", Major);
		return Major;
	}
	dev_class = class_create(THIS_MODULE, CLASS_NAME);
	if (dev_class == NULL) {
		unregister_chrdev(Major, DEVICE_NAME);
		printk(KERN_ALERT "Failed register device class\n");
		return -1;
	}
	dev = device_create(dev_class, NULL, MKDEV(Major, 0), NULL, DEVICE_NAME);
	if (dev == NULL) {
		class_destroy(dev_class);
		unregister_chrdev(Major, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create device\n");
		return -1;
	}
	printk(KERN_INFO "I was assigned major number %d.\n", Major);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Hexdump module goodbye\n");
	device_destroy(dev_class, MKDEV(Major, 0));
	class_unregister(dev_class);
	class_destroy(dev_class);
	unregister_chrdev(Major, DEVICE_NAME);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);

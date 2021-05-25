/*
 * Character device drivers lab
 *
 * All tasks
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <asm/atomic.h>
#include "../include/so2_cdev.h"

MODULE_DESCRIPTION("SO2 character device");
MODULE_AUTHOR("SO2");
MODULE_LICENSE("GPL");

#define LOG_LEVEL 	KERN_INFO

#define MY_MAJOR		42
#define MY_MINOR		0
#define NUM_MINORS		1
#define MODULE_NAME		"so2_cdev"
#define MESSAGE			"hello\n"
#define IOCTL_MESSAGE		"Hello ioctl"

#ifndef BUFSIZ
#define BUFSIZ		4096
#endif

 /* TODO 2: add cdev member */
/* TODO 3: add atomic_t access variable to keep track
 if file is opened */
struct so2_device_data {
	struct cdev cdev;
	atomic_t accessible;
	/* TODO 4: add buffer with BUFSIZ elements */
	char buffer[BUFSIZ];
	/* TODO 7: extra members for home */
};

struct so2_device_data devs[NUM_MINORS];

static int so2_cdev_open(struct inode *inode, struct file *file)
{
	struct so2_device_data *data;
	/* TODO 2: print message when the device file is open. */
	printk( LOG_LEVEL "Device file opened");
	/* TODO 3: inode->i_cdev contains our cdev struct,
	 use container_of to obtain a pointer to so2_device_data */
	data = container_of(inode->i_cdev, struct so2_device_data, cdev);
	file->private_data = data;
	/* TODO 3: return immediately if access is != 0,
	use atomic_cmpxchg */
	if( atomic_cmpxchg(&(data->accessible), 0, 1) != 1 ){
		printk( LOG_LEVEL "target was busy sorry");
		return -EBUSY;
	} // device is busy
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(10 * HZ);
	printk( LOG_LEVEL "opened the device");
	return 0;
}

static int
so2_cdev_release(struct inode *inode, struct file *file)
{
	/* TODO 2: print message when the device file is closed. */
	printk( LOG_LEVEL "Device file is closed");
	struct so2_device_data *data = (struct so2_device_data *) file->private_data;
	/* TODO 3: reset access variable to 0, use atomic_set */
	atomic_set(&(data->accessible), 0);
	return 0;
}

static ssize_t
so2_cdev_read(struct file *file,
		char __user *user_buffer,
		size_t size, loff_t *offset)
{
	struct so2_device_data *data =
		(struct so2_device_data *) file->private_data;
	size_t to_read = size - *offset;
	if(to_read <= 0){ return 0; }
#ifdef EXTRA
	/* TODO 7: extra tasks for home */
#endif
	/* TODO 4: Copy data->buffer to user_buffer */
	if(size <= BUFSIZ){
		printk( LOG_LEVEL "being read");
		to_read = (size_t)copy_to_user(user_buffer,
				data->buffer + *offset, to_read);
		if(to_read){ return -EFAULT; }
	}
	*offset += to_read;
	return to_read;
}

static ssize_t
so2_cdev_write(struct file *file,
		const char __user *user_buffer,
		size_t size, loff_t *offset)
{
	struct so2_device_data *data =
		(struct so2_device_data *) file->private_data;
	/* TODO 5: copy user_buffer to data->buffer,
	use copy_from_user */
	if(size <= BUFSIZ){
		copy_from_user(data->buffer, user_buffer, size);
	}
	/* TODO 7: extra tasks for home */
	return size;
}

static long
so2_cdev_ioctl(struct file *file, unsigned int cmd,
unsigned long arg)
{
	struct so2_device_data *data =
		(struct so2_device_data *) file->private_data;
	int ret = 0;
	switch (cmd) {
		/* TODO 6: display IOCTL_MESSAGE */
		case MY_IOCTL_PRINT:
			printk( LOG_LEVEL "Ioctl message is %s", IOCTL_MESSAGE);
		/* TODO 7: extra tasks, for home */
			break;
		case MY_IOCTL_SET_BUFFER:
			if( copy_from_user(data->buffer, (struct so2_device_data *)arg, BUFSIZ) )
            			return -EFAULT;
			break;
		case MY_IOCTL_GET_BUFFER:
			if( copy_to_user((struct so2_device_data *)arg, data->buffer, BUFSIZ) )
				return -EFAULT;
			break;
		case MY_IOCTL_DOWN:
			
			break;
		case MY_IOCTL_UP:
			
			break;
		default:
			ret = -EINVAL;
			break;
	}
	return ret;
}

static const struct file_operations so2_fops = {
	.owner = THIS_MODULE,
/* TODO 2: add open and release functions */
	.open = so2_cdev_open,
	.release = so2_cdev_release,
/* TODO 4: add read function */
	.read = so2_cdev_read,
/* TODO 5: add write function */
	.write = so2_cdev_write,
/* TODO 6: add ioctl function */
	.unlocked_ioctl = so2_cdev_ioctl
};

static int so2_cdev_init(void)
{
	int err;
	int i;
	printk( LOG_LEVEL "Registering the char device");
	/* TODO 1: register char device region for MY_MAJOR and NUM_MINORS starting at MY_MINOR */
	register_chrdev_region(MKDEV(MY_MAJOR, MY_MINOR), NUM_MINORS, MODULE_NAME);
	for (i = 0; i < NUM_MINORS; i++) {
		/* TODO 7: extra tasks, for home */
		/*TODO 4: initialize buffer with MESSAGE string */
		strncpy(devs[i].buffer, MESSAGE, BUFSIZ);
		/* TODO 7: extra tasks for home */
		/* TODO 3: set access variable to 0, use atomic_set */
		atomic_set(&devs[i].accessible, 0);
		/* TODO 2: init and add cdev to kernel core */
		cdev_init(&devs[i].cdev, &so2_fops);
		cdev_add(&devs[i].cdev, MKDEV(MY_MAJOR, i), 1);
	}
	return 0;
}

static void so2_cdev_exit(void)
{
	int i;
	for (i = 0; i < NUM_MINORS; i++) {
		/* TODO 2: delete cdev from kernel core */
		cdev_del(&devs[i].cdev);
	}
	printk( LOG_LEVEL "Unregistering char device");
	/* TODO 1: unregister char device region, for MY_MAJOR and NUM_MINORS starting at MY_MINOR */
	unregister_chrdev_region(MKDEV(MY_MAJOR, MY_MINOR), NUM_MINORS);
}

module_init(so2_cdev_init);
module_exit(so2_cdev_exit);

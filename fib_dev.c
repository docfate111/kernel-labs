#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#define DEVICE_NAME "fibonacci"
static int Major;

static int device_open(struct inode *inode, struct file *filp)
{
  printk(KERN_INFO "[device_open] device opened\n");
  return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
  printk(KERN_INFO "[device_release] device closed\n");
  return 0;
}

static ssize_t device_read(struct file *filp, 
		char* buffer, size_t length,
		loff_t *offset)
{
    printk(KERN_INFO "[device_read] device read %d\n", *offset);
    // memoization for fibonacci
    int arr[2] = {0, 1};
    int i;
    for(i = 2; i <= *offset; i++)
	   arr[i%2] = arr[0] + arr[1];
    return arr[(*offset)%2];
}

loff_t device_llseek(struct file *filp, loff_t off, int whence)
{
  printk(KERN_INFO "[device_llseek] llseek is called\n");
  void *dev = filp->private_data;
  loff_t newpos;
  switch(whence) {
   case 0: /* SEEK_SET */
    newpos = off;
    break;

   default: /* can't happen */
    return -EINVAL;
  }
  filp->f_pos = newpos;
  return newpos;
}

static struct file_operations fops = {
  .read = device_read,
  .open = device_open,
  .release = device_release,
  .llseek = device_llseek
};

int init_module(void)
{
  Major = register_chrdev(0, DEVICE_NAME, &fops);
  if (Major < 0) {
    printk(KERN_ALERT "Registering char device failed with %d\n", Major);
    return Major;
  }

  printk(KERN_INFO "[init_module] 'mknod /dev/%s c %d 0'\n", DEVICE_NAME, Major);
  return 0;
}

void cleanup_module(void)
{
  unregister_chrdev(Major, DEVICE_NAME);
}

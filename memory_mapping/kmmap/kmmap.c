/*
 * PSO - Memory Mapping Lab(#11)
 *
 * Exercise #1: memory mapping using kmalloc'd kernel areas
 */

#include <linux/version.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <asm/pgtable.h>
#include <linux/sched/mm.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <asm/highmem.h>
#include <linux/rmap.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "../test/mmap-test.h"

MODULE_DESCRIPTION("simple mmap driver");
MODULE_AUTHOR("PSO");
MODULE_LICENSE("Dual BSD/GPL");

#define MY_MAJOR	42
/* how many pages do we actually kmalloc */
#define NPAGES		16

/* character device basic structure */
static struct cdev mmap_cdev;

/* pointer to kmalloc'd area */
static void *kmalloc_ptr;

/* pointer to the kmalloc'd area, rounded up to a page boundary */
static char *kmalloc_area;

static int my_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int my_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static int my_read(struct file *file, char __user *user_buffer,
		size_t size, loff_t *offset)
{
	/* TODO 2: check size doesn't exceed our mapped area size */
	// if size < 
	/* TODO 2: copy from mapped area to user buffer */

	return size;
}

static int my_write(struct file *file, const char __user *user_buffer,
		size_t size, loff_t *offset)
{
	/* TODO 2: check size doesn't exceed our mapped area size */
	
	/* TODO 2: copy from user buffer to mapped area */
	/*if(copy_from_user(user_buffer, kmalloc_ptr, size)){
		return -EINVAL;
	}*/
	return size;
}

static int my_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int ret;
	long length = vma->vm_end - vma->vm_start;

	/* do not map more than we can */
	if (length > NPAGES * PAGE_SIZE)
		return -EIO;

	/* TODO 1: map the whole physically contiguous area in one piece */
	int pfn = virt_to_phys(((void*)kmalloc_area) >> PAGE_SHIFT);
	remap_pfn_range(vma, vma->vm_start, pfn, length, vma->vm_page_prot);
	return 0;
}

static const struct file_operations mmap_fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_release,
	.mmap = my_mmap,
	.read = my_read,
	.write = my_write
};

static int my_seq_show(struct seq_file *seq, void *v)
{
	struct mm_struct *mm;
	struct vm_area_struct *vma_iterator;
	unsigned long total = 0;

	/* TODO 3: Get current process' mm_struct */

	/* TODO 3: Iterate through all memory mappings */

	/* TODO 3: Release mm_struct */

	/* TODO 3: write the total count to file  */
	return 0;
}

static int my_seq_open(struct inode *inode, struct file *file)
{
	/* TODO 3: Register the display function */
}

static const struct proc_ops my_proc_ops = {
	.proc_open    = my_seq_open,
	.proc_read    = seq_read,
	.proc_lseek   = seq_lseek,
	.proc_release = single_release,
};

static int __init my_init(void)
{
	int ret = 0;
	int i;
	/* TODO 3: create a new entry in procfs */

	ret = register_chrdev_region(MKDEV(MY_MAJOR, 0), 1, "mymap");
	if (ret < 0) {
		pr_err("could not register region\n");
		goto out_no_chrdev;
	}

	/* TODO 1: allocate NPAGES+2 pages using kmalloc */
	kmalloc_ptr = kmalloc((NPAGES+2) * PAGE_SIZE, GFP_KERNEL);
	if(!kmalloc_ptr) {
		ret = -ENOMEM;
		pr_err("[my_init] Error allocating memory\n");
		goto out_unreg;
	}
	/* TODO 1: round kmalloc_ptr to nearest page start address */
	kmalloc_area = (char *) PAGE_ALIGN(((unsigned long)kmalloc_ptr));
	/* TODO 1: mark pages as reserved */
	size_t i;
	// loop through each page by getting their address then adding page size each time
	for(i = 0; i < NPAGES * PAGE_SIZE; i += PAGE_SIZE){
	        SetPageReserved(virt_to_page(((unsigned long)kmalloc_area) + i));
	}
	/* TODO 1: write data in each page
	For verification purpose (using the test below), fill in the first 4 bytes of each page with
	 the following values: 0xaa, 0xbb, 0xcc, 0xdd.
	*/
	for(i = 0; i < NPAGES * PAGE_SIZE; i += PAGE_SIZE) {
		kmalloc_area[i] = 0xaa;
		kmalloc_area[i+1] = 0xbb;
		kmalloc_area[i+2] = 0xcc;
		kmalloc_area[i+3] = 0xdd;
	}
	/* Init device. */
	cdev_init(&mmap_cdev, &mmap_fops);
	ret = cdev_add(&mmap_cdev, MKDEV(MY_MAJOR, 0), 1);
	if (ret < 0) {
		pr_err("could not add device\n");
		goto out_kfree;
	}

	return 0;

out_kfree:
	kfree(kmalloc_ptr);
out_unreg:
	unregister_chrdev_region(MKDEV(MY_MAJOR, 0), 1);
out_no_chrdev:
	remove_proc_entry(PROC_ENTRY_NAME, NULL);
out:
	return ret;
}

static void __exit my_exit(void)
{
	int i;

	cdev_del(&mmap_cdev);

	/* TODO 1: clear reservation on pages and free mem. */
	for(i = 0; i < npages * PAGE_SIZE; i += PAGE_SIZE){
	        ClearPageReserved(virt_to_page(((unsigned long)kmalloc_area) + i));
	}
	unregister_chrdev_region(MKDEV(MY_MAJOR, 0), 1);
	/* TODO 3: remove proc entry */
}

module_init(my_init);
module_exit(my_exit);

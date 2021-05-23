/*
 * Kernel API lab
 *
 * sched-spin.c: Sleeping in atomic context
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
MODULE_DESCRIPTION("Sleep while atomic");
MODULE_AUTHOR("SO2");
MODULE_LICENSE("GPL");

static int sched_spin_init(void)
{
	spinlock_t lock;
	spin_lock_init(&lock);
	/* TODO 0: Use spin_lock to aquire the lock */
	printk("Locking...\n");
	spin_lock(&lock);
	set_current_state(TASK_INTERRUPTIBLE);
	/* Try to sleep for 5 seconds. */
	// not allowed to sleep in atomic context(between lock and unlock on a spinlock) 
	// schedule_timeout(5 * HZ);
	/* TODO 0: Use spin_unlock to release the lock */
	spin_unlock(&lock);
	printk("Unlocking...\n");
	return 0;
}

static void sched_spin_exit(void)
{
	printk("Exiting...");
}

module_init(sched_spin_init);
module_exit(sched_spin_exit);

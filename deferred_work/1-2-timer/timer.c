/*
 * Deferred Work
 *
 * Exercise #1, #2: simple timer
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_DESCRIPTION("Simple kernel timer");
MODULE_AUTHOR("SO2");
MODULE_LICENSE("GPL");

#define TIMER_TIMEOUT	1

static struct timer_list timer;

static void timer_handler(struct timer_list *tl)
{
	static size_t nsecs;
	nsecs += TIMER_TIMEOUT;
	/* TODO 1: print a message */
	pr_info("[timer_handler] number of sceonds %d", nsecs);
	/* TODO 2: rechedule timer */
	mod_timer(&timer, TIMER_TIMEOUT*HZ + jiffies);
}

static int __init timer_init(void)
{
	pr_info("[timer_init] Init module\n");
	/* TODO 1: initialize timer */
	timer_setup(&timer,
                 timer_handler,
                 0);
	/* TODO 1: schedule timer for the first time */
	if(mod_timer(&timer, jiffies+HZ*TIMER_TIMEOUT))
	{
		printk("timer modified");
	}
	return 0;
}

static void __exit timer_exit(void)
{
	pr_info("[timer_exit] Exit module\n");

	/* TODO 1: cleanup; make sure the timer is not running
	 after we exit */
	del_timer_sync(&timer);
}

module_init(timer_init);
module_exit(timer_exit);

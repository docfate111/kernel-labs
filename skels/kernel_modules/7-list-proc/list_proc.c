#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
MODULE_DESCRIPTION("List current processes");
MODULE_AUTHOR("Kernel Hacker");
MODULE_LICENSE("GPL");

static int my_proc_init(void)
{
	struct task_struct *p = current;
	/* print current process pid and its name */
	printk("Current pid %d name %s\n", p->pid, p->comm);
	/* print the pid and name of all processes */
	/*struct task_struct* task_list;
	for_each_process(task_list){
		printk("Current pid %d name %s\n", task_list->pid, task_list->comm);
	}*/
	return 0;
}

static void my_proc_exit(void)
{
	/* print current process pid and name */
	printk("Current process id: %d and name %s", current->pid, current->comm);
}

module_init(my_proc_init);
module_exit(my_proc_exit);

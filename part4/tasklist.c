#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/task.h>

void traverse_list(struct list_head *node, int depth);

void print_task(struct task_struct *task, int depth);

int tasklist_init(void)
{
	printk(KERN_INFO "Loading Module\n");

	printk(KERN_INFO "\\_ [%d] %s\n", init_task.pid, init_task.comm);
	traverse_list(&init_task.children, 1);
	return 0;
}

void tasklist_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
}

void traverse_list(struct list_head *node, int depth) {
	struct task_struct *sib;
	list_for_each_entry(sib, node, sibling) {
		print_task(sib, depth);
		traverse_list(&sib->children, depth+1);
	}
}

void print_task(struct task_struct *task, int depth) {
	depth = depth > 20 ? 20 : depth;
	printk(KERN_INFO "%*.0s \\_ [%d] %s\n", depth*2, ' ', task->pid, task->comm);
}

module_init( tasklist_init );
module_exit( tasklist_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Tasklist Module");
MODULE_AUTHOR("zz2700");

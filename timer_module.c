#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple example Linux kernel timer module.");
MODULE_VERSION("0.1");

static struct timer_list my_timer;

void my_timer_callback(struct timer_list *timer) {
    printk(KERN_INFO "%s: my_timer_callback called (%ld).\n", __FUNCTION__, jiffies);
}

static int __init my_timer_init(void) {
    printk(KERN_INFO "my_timer_module: Module init.\n");

    // Setup timer to call my_timer_callback
    timer_setup(&my_timer, my_timer_callback, 0);

    // Setup timer interval to 200 jiffies (~2 seconds on most systems)
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(2000));

    return 0;
}

static void __exit my_timer_exit(void) {
    del_timer(&my_timer);
    printk(KERN_INFO "my_timer_module: Module unloaded.\n");
}

module_init(my_timer_init);
module_exit(my_timer_exit);

#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

static int major;
static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o)
{
        printk("chr_Dev- read is called...\n");
        return 0;
}

static struct file_operations fops={
        .read=my_read
};
static int __init init_fun(void)
{
        major=register_chrdev(0,"char_dev_driver",&fops);
        if(major<0)
        {
                pr_err("Error register in chrdev\n");
                return major;
        }
        printk("hello in chrdev- major devise number--> %d\n",major);
        return 0;
}

static void __exit exit_fun(void)
{

        unregister_chrdev(major,"module is remove from kernal..\n");
}

module_init(init_fun);
module_exit(exit_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Janvi");

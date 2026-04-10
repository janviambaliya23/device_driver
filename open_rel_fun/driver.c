#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

static int major;
static int my_open (struct inode *inode, struct file *fp){
    pr_info("major-> %d, minor-> %d\n",imajor(inode),iminor(inode));
    pr_info("file position -> %lld\n", fp->f_pos);
    pr_info("file mode -> 0x%x\n", fp->f_mode);
    pr_info("file flag -> 0x%x\n", fp->f_flags);
    return 0;
}

static int my_release (struct inode *inode, struct file *fp)
{
    pr_info("file is close here..\n");
    return 0;

}

static struct file_operations fops={
       .open=my_open,
       .release=my_release,
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


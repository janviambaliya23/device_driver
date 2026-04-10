#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

static int major;
static char text[64];   //char buffer which point to user buffer

static int my_open (struct inode *inode, struct file *fp){

    fp->f_pos=0;
    pr_info("OPEN FUN :- major-> %d, minor-> %d \n",imajor(inode),iminor(inode));
    //pr_info("file position -> %lld\n", fp->f_pos);
    //pr_info("file mode -> 0x%x\n", fp->f_mode);
    //pr_info("file flag -> 0x%x\n", fp->f_flags);
    return 0;
}

static int my_release (struct inode *inode, struct file *fp)
{
    pr_info("RELESE FUN :- file is close here..\n");
    return 0;

}
//len of buf, off- current file offset
static ssize_t my_read(struct file *fp, char __user *user_buf, size_t len, loff_t *off) 
{
        int copied,delta,copy=(len + *off)< sizeof(text) ? len : (sizeof(text) - *off);

        //printk("Read FUN :- we want to read %ld bytes, but actually only copy %d bytes. the offset is %lld\n",len,copy,*off);
        if(*off>=sizeof(text))
        {
                        return 0;
        }

        copied=copy_to_user(user_buf, &text[*off],copy);
        delta = copy-copied;
        if(copied)
                pr_warn("could not copy %d bytes\n",delta);
        *off+=delta;
        return delta;
}

static ssize_t my_write(struct file *fp,const char __user *user_buf, size_t len, loff_t *off) 
{
        int copied,delta,copy=(len + *off)< sizeof(text) ? len : (sizeof(text) - *off);

        //printk("chr_Dev- write is called, we want to write %ld bytes, but actually only copy %d bytes. the offset is %lld\n",len,copy,*off);
        if(*off>=sizeof(text))
        {
                        return 0;
        }

        copied=copy_from_user( &text[*off],user_buf,copy);
        delta = copy-copied;
        if(copied)
                pr_warn("could not copy %d bytes\n",delta);
        *off+=delta;
        return delta;
}

static struct file_operations fops={
        .read=my_read,
        .write=my_write,
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



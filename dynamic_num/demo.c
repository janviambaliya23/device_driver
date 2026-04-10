#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

dev_t dev = 0;

static int __init demo_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"demo_dev_dynamic"))<0){
		pr_err("cannot allocate major number for device..\n");
	}
	printk("major num ->%d minor num ->%d",MAJOR(dev),MINOR(dev));
	printk("WELCOME TO INIT FUNCTION..\n");
	return 0;	
}

static void __exit demo_exit(void)	//execute last 
{
	unregister_chrdev_region(dev,1);
	pr_notice("I AM REMOVING HERE..\n");
}


module_init(demo_init);		//register itself
module_exit(demo_exit);		

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Janvi");
MODULE_DESCRIPTION("Simple Demo Driver");



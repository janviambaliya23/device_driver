#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

dev_t dev = MKDEV(23,0);

static int __init demo_init(void)	//execute first when the Linux device driver is loaded
{
	register_chrdev_region(dev,1,"demo_dev");
	printk("major num -%d minor num -%d",MAJOR(dev),MINOR(dev));
	printk("WELCOME TO INIT FUNCTION..\n");
	printk(KERN_INFO"LOG-MSG:- INFORMATION\n");
	printk(KERN_WARNING"LOG-MSG:- WARNING IN INIT\n");
	return 0;	
//	return -1;	// till printk it load into kernal but from this line kernal gets to know whatever this module is that could not load. 
}

static void __exit demo_exit(void)	//execute last 
{
	unregister_chrdev_region(dev,1);
	pr_notice("I AM REMOVING HERE..\n");
	pr_err("LOG-MSG :- ERROR IS HERE...\n");
	pr_info("normal printing..%d\n",23);
}


module_init(demo_init);		//register itself
module_exit(demo_exit);		

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Janvi");
MODULE_DESCRIPTION("Simple Demo Driver");


/*PRACTICE:- 

make		:- compile
sudo rmmod demo :- to remoce kernal module  # (ignore error if not loaded)
sudo insmod demo.ko:- to add kernal module
sudo dmesg | tail :- to print msg from tail.
sudo dmesg | head :- to print msg from head
sudo dmesg | tail -n 10 :- only 10 msg will print
sudo dmesg -WT:- for watching contious output 👉 It is used to view kernel logs in a human-readable time format
dmesg -W :- live updates, -T:- timestamps
*/

//SPDX-License-Identifier:GPL-3.0
/*
Copyright(C) 2020 Yamato Yoshinuma All rights reserved.
*/

#include <linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/io.h>
#include<linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{	
	int p;
	char c;
	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;

//	printk(KERN_INFO "receive %c\n", c);
	if(c == '0')
		gpio_base[10] = 1 << 25;
	else if(c == '1'){
		for(p = 0;p <= 55;p++){
			switch(p) {
				case 2:
				case 8:
				case 10:
				case 12:
				case 13:
				case 15:
				case 17:
				case 18:
				case 20:
				case 22:
				case 23:
				case 25:
				case 29:
				case 35:
				case 36:
				case 40:
				case 43:
				case 50:
				case 52:
				case 54:
					gpio_base[7] = 1<<25;
					msleep (200);
					gpio_base[10] = 1<<25;
					msleep (200);
					break;
				case 0:
				case 1:
				case 4:
				case 5:
				case 6:
				case 9:
				case 16:
				case 21:
				case 26:
				case 28:
				case 31:
				case 32:
				case 33:
				case 37:
				case 39:
				case 42:
				case 44:
				case 46:
				case 47:
				case 48:
				case 51:
				case 53:
				case 55:
					gpio_base[7]=1<<25;
					msleep (600);
					gpio_base[10]=1<<25;
					msleep (200);
					break;
				case 3:
				case 7:
    				case 11:
				case 14:
				case 19:
				case 24:
				case 30:
				case 38:
				case 41:
				case 45:
				case 49:
					msleep (600);
					break;
				case 27:
				case 34:
					msleep (1200);
					break;
			}
		}
		}
	return 1;
}

static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
	int size=0;
	char sushi[]={'s', 'u', 's','h', 'i'};
	if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
		printk(KERN_INFO "sushi : copy_to_user failed\n");
		return -EFAULT;
	}
	size+=sizeof(sushi);
	return size;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};

static int __init init_mod(void)
{
	int retval;
	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}

	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__, MAJOR(dev));
	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n", MAJOR(dev), MINOR(dev));
			return retval;
	}
	
	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.\n");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

	const u32 led = 25;
	const u32 index = led/10;
	const u32 shift = (led%10)*3;
	const u32 mask = ~(0x7 << shift);
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);

	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded.major:%d\n",__FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);

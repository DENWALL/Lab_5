#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>

#define mem_size 1024 //size of memory
///////////блок объявления функций
dev_t dev = 0;
static struct class* dev_class;
static struct cdev cdev_examlple;
uint8_t* kern_buf;

static int __init ex_driver_init(void);
static void __exit ex_driver_exit(void);
static int ex_open(struct inode* inode, struct file* file);
static int ex_release(struct inode* inode, struct file* file);
static ssize_t ex_read(struct file* filp, char __user* buf, size_t len,
loff_t* off);
static ssize_t ex_write(struct file* filp, const char* buf, size_t len,
loff_t* off);

static struct file_operations fops = {
// Тут будет ваш код
.owner = THIS_MODULE,
.read = ex_read,
.write = ex_write,
.open = ex_open,
.release = ex_release
};
///////////
int value = 0;
int notify_param(const char *val, const struct kernel_param *kp)
{
int res = param_set_int(val, kp);

if(res==0) {
printk(KERN_INFO "New value = %d\n", value);
return 0;
}

return -1;
}

const struct kernel_param_ops my_param_ops =
{
.set = &notify_param,
.get = &param_get_int,
};

module_param_cb(value, &my_param_ops, &value, S_IRUGO|S_IWUSR );

static int ex_open(struct inode* inode, struct file* file)
{
printk(KERN_INFO "Driver init\n");
return 0;
}

static int ex_release(struct inode* inode, struct file* file)
{
printk(KERN_INFO "Driver deinit\n");
return 0;
}

static ssize_t ex_read(struct file* filp, char __user* buf, size_t len,
loff_t* off)
{
kern_buf = (uint8_t*)kmalloc(1024, GFP_KERNEL);

if(!kern_buf){
printk(KERN_INFO "ERROR: Kmalloc can`t run\n");
return -1;
}
*kern_buf = (uint8_t)127;

char temp[10] = "";
temp[0] = ((char) value) + 'A';
if( copy_to_user(buf, &temp, sizeof(temp)) > 0) {
printk(KERN_INFO "ERROR: Failed copying\n");
return -1;
}
kfree(kern_buf);
return 0;
}

static ssize_t ex_write(struct file* filp, const char __user* buf, size_t
len, loff_t* off)
{
// Тут будет ваш код
kern_buf = (uint8_t*)kmalloc(1024, GFP_KERNEL);

char* temp = kmalloc(100, GFP_KERNEL);

if( copy_from_user(temp, buf, len ) > 0) {
pr_err("ERROR: Failed copying\n");
return -1;
}

value = (int)(temp[0] - 'A');

kfree(kern_buf);
kfree(temp);
return 0;
}

static int __init ex_driver_init(void)
{
printk(KERN_INFO "Driver Started\n");
alloc_chrdev_region(&dev, 0, 1, "Our_device");
dev_class = class_create(THIS_MODULE,"example_class");
device_create(dev_class,NULL,dev,NULL,"example_device");
cdev_init(&cdev_examlple,&fops);
cdev_add(&cdev_examlple,dev,1);
return 0;
}

static void __exit ex_driver_exit(void)
{
unregister_chrdev_region (dev, 1);
cdev_del(&cdev_examlple);
device_destroy(dev_class,dev);
class_destroy(dev_class);
printk(KERN_INFO "Driver Out\n");
}

// Тут будет ваш код
module_init(ex_driver_init);
module_exit(ex_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kozin Alexey");
MODULE_DESCRIPTION("My first driver");
MODULE_VERSION("1.0");

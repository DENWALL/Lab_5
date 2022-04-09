#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x7ba62dba, "module_layout" },
	{ 0x36a338f0, "param_get_int" },
	{ 0x874ca612, "class_destroy" },
	{ 0x5e856e30, "device_destroy" },
	{ 0xd89d03ae, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x3aa8a9f4, "cdev_add" },
	{ 0xbfd4e3c3, "cdev_init" },
	{ 0x76383e5c, "device_create" },
	{ 0xc400cdf0, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xa532c826, "param_set_int" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x37a0cba, "kfree" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x1ce1ab25, "kmem_cache_alloc_trace" },
	{ 0x3a8870f8, "kmalloc_caches" },
	{ 0x7c32d0f0, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "4969E14238129CC0CC2FE18");

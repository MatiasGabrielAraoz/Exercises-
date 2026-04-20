#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/panic.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mati");
MODULE_DESCRIPTION("Kernel Panic");

static int __init colapso_init(void){
	pr_emerg("Ejecutando kernel panic");
	panic("");
	return 0;
}

static void __exit colapso_exit(void)
{
    // Código inalcanzable
}

module_init(colapso_init);
module_exit(colapso_exit);

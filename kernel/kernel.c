#include <kernel/kernel.h>

static kernel_arch *kernelArch;

static void kernel_test(void);


uint32_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
	PANIC("*Stack check fail");
}

void kernel_init(kernel_arch *arch)
{
    /* TODO: Put vga stuff into a module */
    /* Setup the screen (by clearing it) */
    vga_device_init();

    kernelArch = arch;
    if (!kernelArch)
	    PANIC("No registered architecture.");
    else
    {
        multiboot_init(kernelArch->magic, kernelArch->mboot);
        log_write("# Arch: %s\t\tOK\n", kernelArch->name);
    }
    /* Setup architecture-dep. stuff */
    if (kernelArch->setup)
    {
	    kernelArch->setup();
        log_write("# GDT & IDT\t\tOK\n");
    }

    /* Init the system timer: will be a loadable module */
    timer_init();
    log_write("# Timer/Clock\t\tOK\n");

    /* Init the keyboard: will be a loadable module */
    keyboard_init();
    log_write("# Keyboard (US)\t\tOK\n");

    if (kernelArch->setup_mmu)
    {
	    kernelArch->setup_mmu();
        log_write("# Paging\t\tOK\n");
    }

    vfs_init();
    log_write("# VFS\t\t\tOK\n");

    ramdisk_init(kernelArch->ramdiskc, kernelArch->ramdiskv);
    log_write("# Initrd\t\tOK\n");

    symbol_init();
    log_write("# Kernel symbols\tOK\n");

    if (KERNEL_TEST)
	    kernel_test();

    /* Setup syscalls */
    syscalls_init();
    log_write("# Syscalls\t\tOK\n");

    if (KERNEL_DEBUG) {
	    /* Setup multitasking */
	    tasking_init();
	    log_write("# Multitasking\t\tOK\n");

	    /* Switch to user mode */
      /* TODO: ERROR: Resolve page fault on switching to user mode. */
	    usermode_init();
	    log_write("# Usermode\t\tOK\n");
    }

    /* Init a demo shell: will be a loadable exec. */
    shell_init();
}

static void kernel_test(void)
{
    void *a, *b, *c, *d;
    int8_t temp[1024] = { 0 };

    log_write("# Testing timer........\n");
    sleep(1);

    log_write("# Testing PC speaker...\n");
    beep(440, 0.3);
    beep(494, 0.3);
    beep(554, 0.3);
    beep(587, 0.3);
    beep(659, 0.3);
    beep(740, 0.3);
    beep(831, 0.3);
    beep(880, 0.3);
    beep(880, 0.3);
    beep(831, 0.3);
    beep(740, 0.3);
    beep(659, 0.3);
    beep(587, 0.3);
    beep(554, 0.3);
    beep(494, 0.3);
    beep(440, 0.3);

    /* Check if the system really works */
    log_write("# Testing interrupts...\n");
    __asm__ __volatile__("int $0x0");
    __asm__ __volatile__("int $0x3");
    /* Important! Re-enable interrupt requests */
    kernel_enable_interrupts();

    /* Check if something went wrong with paging and heap setup */
    log_write("# Testing the heap.....\n");
    a = (void *) kmalloc(8);
    b = (void *) kmalloc(8);
    c = (void *) kmalloc(8);
    log_write("a: 0x%x\n", a);
    log_write("b: 0x%x\n", b);
    log_write("c: 0x%x\n", c);
    kfree(c);
    kfree(b);
    d = (void *) kmalloc(12);
    log_write("d: 0x%x\n", d);
    kfree(a);
    kfree(d);

    /* Try to read files from the ramdisk image */
    log_write("# Testing initrd.......\n");
    if (vfs_open("/ramdisk/boot/kernel.sym"))
    {
	    vfs_read("/ramdisk/boot/kernel.sym", 0, 21, temp);
	    vfs_close("/ramdisk/boot/kernel.sym");
	    temp[1023] = 0;
	    log_write("---> Reading /ramdisk/boot/kernel.sym\n");
	    log_write("%s", temp);
	    memclr(temp, 1024);
	    vfs_open("/");
	    vfs_read("/", 0, 1024, temp);
	    vfs_close("/");
	    log_write("---> Reading /\n");
	    log_write("%s", temp);
    }
    else
    {
	    log_write("Couldn't open /ramdisk/boot/kernel.sym\n");
    }
}

void kernel_halt() {
    log_write("\n# System will now halt.\n");
    kernelArch->disable_interrupts();
    kernelArch->halt();
}

void kernel_reboot() {
    log_write("\n# System will now reboot.");
    kernelArch->disable_interrupts();
    kernelArch->reboot();
}

void kernel_disable_interrupts() {
    kernelArch->disable_interrupts();

}

void kernel_enable_interrupts() {
    kernelArch->enable_interrupts();
}

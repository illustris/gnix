ROOTDIR := .
include $(ROOTDIR)/common.mk

# TODO: compile lib/* separately as a library, without static linking
# object files from /src/asm go first when linking!
SRCFILES := $(shell find -L kernel lib -type f -name "*.c")
ASMFILES := $(shell find -L kernel lib -type f -name "*.s")
INCLUDEFILES := $(shell find -L include -type f -name "*.h")
ALLFILES := $(shell find -type f -name "*.*")
OBJFILES := $(patsubst %.s,%.o,$(ASMFILES)) $(patsubst %.c,%.o,$(SRCFILES))
LDFLAGS += -Tlink.ld

.PHONY: help kernel link compile ramdisk install cdrom run-cdrom qemu-x86-cdrom bochs-x86-cdrom clean todo-list notes-list

# [0] make help		Display callable targets.
help:
	@echo "Available options:"
	@grep -oE "\[[0-9]+\] make\s+.*" [Mm]akefile

# [1] make kernel		Compile and link the kernel into an executable.
kernel: link install ramdisk

link: compile $(OBJFILES)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJFILES)

compile:
	#mkdir -p $(SYSROOT)/$(PREFIX)
	mkdir -p $(SYSROOT)/$(BOOTDIR)
	#cp -RTv $(INCLUDEDIR) $(SYSROOT)/$(PREFIX)/$(INCLUDEDIR)
	cd kernel && make
	cd lib && make
	cd mods && make

install: $(KERNEL)
	cp -RTv utils/grub $(SYSROOT)/$(BOOTDIR)/grub
	cp -RTv utils/kernel.sym $(SYSROOT)/$(BOOTDIR)/kernel.sym
	cp -RTv $(KERNEL) $(SYSROOT)/$(BOOTDIR)/$(KERNEL)

ramdisk: $(KERNEL)
	cp -RTv $(SYSROOT) ramdisk/$(SYSROOT)
	cd ramdisk && make
	#cp -RTv $(RAMDISK) $(SYSROOT)/$(BOOTDIR)/$(RAMDISK)
	cp -RTv $(RAMDISK) ramdisk/$(SYSROOT)/$(BOOTDIR)/$(RAMDISK)

# [2] make cdrom		Create a bootable cdrom disk image.
cdrom: $(KERNEL) $(RAMDISK)
	genisoimage -p "$(KERNEL_AUTHOR)" -publisher "$(KERNEL_AUTHOR)" -V "$(KERNEL) kernel" -A "$(KERNEL_DESCRIPTION)" -R -b $(BOOTDIR)/grub/iso9660_stage1_5 -no-emul-boot -boot-load-size 4 -boot-info-table -o $(KERNEL).iso ramdisk/$(SYSROOT)


# [3] make run-cdrom	Boot the cdrom image on the VM emulator.
run-cdrom: $(VM)-$(ARCH)-cdrom

qemu-x86-cdrom:
	qemu-system-i386 -cpu 486 -smp 1,cores=1,threads=1 -m 32 -k it -soundhw pcspk -cdrom $(KERNEL).iso > qemu.log

bochs-x86-cdrom:
	bochs -f bochsrc.txt

# [4] make clean		Clean the environment and remove compiled object files.
clean:
	-@rm -rf $(KERNEL) $(RAMDISK) ramdisk/$(SYSROOT) $(KERNEL).iso $(SYSROOT)
	-@cd kernel && make clean
	-@cd lib && make clean
	-@cd mods && make clean
	-@cd ramdisk && make clean

# [5] make todo-list		Extract TODO: and FIXME:
todo-list:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO: -e FIXME: $$file; done; true

# [6] make notes-list		Extract NOTE:
notes-list:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e NOTE: $$file; done; true

# [7] make error-list		Extract ERROR:
error-list:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e ERROR: $$file; done; true

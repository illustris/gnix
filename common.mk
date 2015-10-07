########## KERNEL CONFIGURATION ##########

# Architecture to build for: x86
ARCH?= x86

# About the kernel
KERNEL_AUTHOR := AAG
KERNEL_NAME := gnix
KERNEL_VERSION := 0.0.1
KERNEL_DESCRIPTION := Educational Kernel

# Just some useful defines...
KERNEL := $(KERNEL_NAME)-$(KERNEL_VERSION)
RAMDISK := initrd-$(KERNEL_VERSION)


########## ARCH-SPECIFIC CONFIGURATION ##########

# Add specific cflags, etc.
include $(ROOTDIR)/$(ARCH).mk

########## DIRECTORY CONFIGURATION ##########
SYSROOT := root
PREFIX := usr
EXEC_PREFIX := $(PREFIX)
BOOTDIR := boot
INCLUDEDIR := include
LIBSDIR := lib
MODULESDIR := mods
########## TOOLS CONFIGURATION ##########

# Common configuration for GCC
CC := $(HOST)-gcc
SRCFILES := $(shell find -L . -maxdepth 1 -type f -name "*.c")
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
WARNINGS := -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Werror
CFLAGS := -g -static -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -ffreestanding -fstrength-reduce -finline-functions -std=c11 $(WARNINGS)

# Assembler
AS := $(HOST)-nasm
ASFLAGS := -felf

# Archive/library manager
AR := $(HOST)-ar
ARFLAGS := rvs

# Linker
LD := $(HOST)-ld

# Virtual machine - emulator: qemu, bochs
VM := qemu

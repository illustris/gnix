## gnix OS
    A simple operating system for learning purposes.
    
    By Ajai V George

## Dependencies

    Cross Compilers
    
    C compiler - GNU i686-elf-gcc 
    Assembler - i686-elf-nasm
    Linker - GNU i686-elf-ld
    GNU Make

    Optional:
    
    Virtualisation - qemu

## Language Used
    C11
    
## Build Instructions

    make kernel		(compile and glue together source files)

    make cdrom		(create a cdrom bootable image)

    make run-cdrom	(boot and test the cdrom image; will need 'qemu')

    gedit common.mk	(edit configuration and options)
    
    ./test.sh           To test the kernel on qemu


## TODO

### General
    * Cleanup code and directory structure
    * Separate libc
    * keyboard Layout fix ups
    * Better file system (FAT32, NTFS??)
    * Implement own C library or/and port Newlib
    * Complete POSIX and C11 libc interface
    * Linux compatibility?
    * port python
    * port busybox


### VFS Layer

    * better design
    * API
    * mounting, unmounting, mount lists
    * caches (vnode, etc.)
    * task-related things

### Multitasking

    * ELF executable & relocatable loading
    * process synchronization (mutexes, semaphores)
    * IPC (pipes etc)
    * priority based scheduling (timeslices?, round robin?, realtime?)
    * tickless kernel?

### Newlib - libc port

    * Basic syscalls
    * UNIX syscalls
    * POSIX syscalls
    
### 

### Drivers

    * driver manager?
    * drivers & modules registration
    * IRQ registration
    * DMA registration
    * I/O request layer (independent of VFS)
    * I/O request queue

### Disk

    * CD-ROM drive support (ATAPI devices)
    * ATA
    * Floppy
    * Block cache system
    * Disk DMA support
    * USBs?
    
### PCI bus

    * PCI configuration
    * PCI bus layer

### Networking

    * TCP/IP stack (Ethernet, ARP, IP, ICMP, UDP, TCP)
    * Card drivers
    * WiFi card drivers
    
### Graphics
    * vesa driver, graphics interface
    * gnome and kde compatibility?
    * Mouse support?
    
### Other

    * port binutils, gcc, nasm
    * port bash shell
    
## Attribution
    TheWorm/microkernel is used as a starting base. Thank you.

## Documents/links

    There is no documentation for this project yet.

    If you're trying to understand the code or thinking about developing your own OS, you may find very useful documentation/tutorials at [OSdev.org](http://wiki.osdev.org/Main_Page).
ROOTDIR := ..
include $(ROOTDIR)/common.mk

.PHONY: all clean

all:
	-@if [ ! -d $(SYSROOT)/$(MODULESDIR)/ ]; then mkdir $(SYSROOT)/$(MODULESDIR)/; fi
	for file in $(shell find -L $(ROOTDIR)/$(MODULESDIR) -type f -name "*.ko"); do \
	    cp $$file $(SYSROOT)/$(MODULESDIR)/; \
	done
	nm $(ROOTDIR)/$(KERNEL) | grep -f $(SYSROOT)/$(BOOTDIR)/kernel.sym > $(SYSROOT)/$(BOOTDIR)/kernel.map
	cd $(SYSROOT)/ && tar -cvf $(RAMDISK) *
	mv $(SYSROOT)/$(RAMDISK) $(ROOTDIR)/

clean:
	-@rm -f $(SYSROOT)/$(MODULESDIR)/*.ko $(SYSROOT)/$(BOOTDIR)/kernel.map

ROOTDIR := ../../..
include $(ROOTDIR)/common.mk
CFLAGS += -I$(ROOTDIR)/include
ASFILES := $(shell ls *.s)

.PHONY: all clean

all: $(ASFILES) $(OBJFILES)
	for sfile in $(ASFILES); do \
	    $(AS) $(ASFLAGS) $$sfile; \
	done
clean:
	-@rm -f *.o

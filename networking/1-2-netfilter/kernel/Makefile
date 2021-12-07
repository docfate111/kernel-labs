obj-m += filter.o

KDIR = ../../../../../pwnkernel/linux-5.8.1
MY_CFLAGS += -g -DDEBUG
ccflags-y += ${MY_CFLAGS}
CC += ${MY_CFLAGS}
all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules EXTRA_CFLAGS="$(MY_CFLAGS)" && cp filter.ko ../../../../fs && make clean

clean:
	rm -rf t *mod *.o *.ko *.mod.* *.symvers *.order

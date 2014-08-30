obj-m += firewall.o
PWD = $(shell pwd)

all:
	cp -r header /usr/src/linux-headers-$(shell uname -r)/include/
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

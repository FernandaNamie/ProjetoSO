CC=$(CROSS_COMPILE)gcc -Wall -Wextra -static -g

$(shell mkdir -p build/initramfs_root)

.PHONY: all clean
all: build/rootfs.gz

clean:
		rm -rf build
		find -name '*.o' -delete

build/rootfs.gz: build/initramfs_root/init build/initramfs_root/stack_pop build/initramfs_root/stack_push build/initramfs_root/simple_arithmetic build/initramfs_root/write_file
		cd build/initramfs_root ; \
		find -type f -print0 | cpio -0 -ov -H newc | gzip -9 > ../rootfs.gz

build/initramfs_root/init: init.o
		$(CC) -o $@ $^

build/initramfs_root/stack_push: stack_push.o
		$(CC) -o $@ $^

build/initramfs_root/stack_pop: stack_pop.o
		$(CC) -o $@ $^


build/initramfs_root/simple_arithmetic: simple_arithmetic.o
		$(CC) -o $@ $^

build/initramfs_root/write_file: write_file.o
		$(CC) -o $@ $^

C_FILES = $(shell find . -type f -name '*.c')
HEADERS = $(shell find . -type f -name '*.h')
ASM_FILES = $(shell find . -type f -name '*.s')
OBJS = ${C_FILES:.c=.o} ${ASM_FILES:.s=.o} 

CC = gcc #Using i686-elf-gcc would be better.
O_LEVEL = 2 #GCC optimization level.

# -m32: compile 32bit code.
# -nostdlib: Do not use the standard system startup files or libraries when linking. 
# -nostdinc: Do not search the standard system directories for header files.
# -ffreestanding: Assert that compilation targets a freestanding environment. 
# -fno-stack-protector: disables stack protection.
# -Wall: This enables all the warnings about constructions that some users consider questionable, \
#  and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros. 
# -Wextra: This enables some extra warning flags that are not enabled by -Wall.
# -Werror: Make all warnings into errors. Removed this flag to be able to build with the GCC that is preinstalled in most of the Linux systems.
# -ggdb :Produce debugging information for use by GDB. 
# -c: compiles source files without linking.

CFLAGS = -m32 -nostdlib -nostdinc -ffreestanding -fno-stack-protector \
		 -Wall -Wextra -ggdb -c -std=gnu11

QEMUFLAGS = -cdrom JupiteerOS.iso

LDFLAGS = -melf_i386 -nostdlib -O${O_LEVEL} -T

JupiteerOS.iso: kernel.elf
	cp kernel.elf iso/boot/
	grub-mkrescue iso -o JupiteerOS.iso

kernel.elf: ${OBJS}
	ld ${LDFLAGS} link.ld -o kernel.elf $^

%.o: %.c ${HEADERS}
	$(CC) -Iinclude -Iinclude/libc $(CFLAGS) $< -o $@

%.o: %.s
	nasm -f elf $< -o $@

run: JupiteerOS.iso
	qemu-system-i386 ${QEMUFLAGS}

bochs: JupiteerOS.iso
	bochs -f bochs.config -q 

clean:
	find . -type f -name '*.o' -delete
	rm -rf kernel.elf iso/boot/kernel.elf JupiteerOS.iso

OBJECTS = loader.o kmain.o Framebuffer.o Cursor.o Io.o SerialPort.o \
	DT/String.o
CC = gcc
CFLAGS = -std=c++20 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Wunused -I.
LDFLAGS = -T Kernel/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf
LIBRARIES = libdt.a
DT_OBJECTS = \
	DT/String.o

all: kernel.elf

kernel.elf: $(OBJECTS) ${LIBRARIES}
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

libdt.a: DT/String.o
	ar rcs DT/libdt.a DT/String.o

DT/%.o: DT/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

dead-os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o dead-os.iso                       \
				iso

run: dead-os.iso
	qemu-system-i386 -enable-kvm -boot d -cdrom dead-os.iso -m 4 -serial stdio

%.o: Kernel/Screen/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: Kernel/Io/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: Kernel/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: Kernel/%.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf dead-os.iso

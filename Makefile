OS_NAME = DeadOS

CC = gcc
CFLAGS = -std=c++2a -m32 -g -O0 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -ffreestanding \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Wunused -I.

LD = ld
LDFLAGS = -T Kernel/link.ld -melf_i386 -Lbuild -ldts

ASM = nasm
ASMFLAGS = -f elf -g

AR = ar
ARFLAGS = rcs

LIBRARIES = libdts.a

SRC_DIR := Kernel
BUILD_DIR = build
DTS_DIR = dts

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CPP_SRC = $(call rwildcard,$(SRC_DIR),*.cpp)
ASM_SRC = $(call rwildcard,$(SRC_DIR),*.s)
DTS_SRC = $(call rwildcard,$(DTS_DIR),*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SRC))
OBJS += $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%_asm.o, $(ASM_SRC))
DTS_OBJS = $(patsubst $(DTS_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(DTS_SRC))


all: setup kernel.elf

kernel.elf: $(OBJS) ${LIBRARIES}
	@echo "Linking kernel..."
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel.elf $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $(notdir $<)..."
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_asm.o: $(SRC_DIR)/%.s
	@echo "Compiling $(notdir $<)..."
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

libdts.a: $(DTS_OBJS)
	@echo "Linking libdts.a static library..."
	$(AR) $(ARFLAGS) $(BUILD_DIR)/$@ $<

$(BUILD_DIR)/%.o: $(DTS_DIR)/%.cpp
	@echo "Compiling $(notdir $<)..."
	$(CC) $(CFLAGS) -c $< -o $@

setup:
	@echo "Creating build directory..."
	@echo $(OBJS)
	@mkdir -p $(BUILD_DIR)


$(OS_NAME).iso: kernel.elf
	cp $(BUILD_DIR)/$^ iso/boot/kernel.elf
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o $@							\
				iso

run: $(OS_NAME).iso
	qemu-system-i386 -enable-kvm -boot d -cdrom $< -m 4 -serial stdio

gdb: $(OS_NAME).iso
	qemu-system-i386 --enable-kvm -boot d -cdrom $< -m 4 -S -s

bochs: $(OS_NAME).iso
	bochs -f bochsrc.txt -q

clean:
	rm -rf *.o kernel.elf $(OS_NAME).iso $(BUILD_DIR)

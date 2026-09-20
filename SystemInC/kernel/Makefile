AS = nasm
LD = ld
CC = gcc

OUT_DIR = outputs
K_DIR = kernel
ISO_DIR = iso/boot

LOADER_FLAGS = -f elf32
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -Iinclude
LINK_FLAGS = -m elf_i386 -T $(K_DIR)/link.ld
GRUB_FLAGS = iso

LOADER_SRC = $(K_DIR)/loader.s
LOADER_OUT = $(OUT_DIR)/loader.o

C_SOURCES = $(wildcard $(K_DIR)/*.c)
C_OBJECTS = $(patsubst $(K_DIR)/%.c, $(OUT_DIR)/%.o, $(C_SOURCES))

LINK_OUT = $(ISO_DIR)/kernel.elf
GRUB_OUT = kernel.iso

all: mk_dirs $(GRUB_OUT)

mk_dirs:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(ISO_DIR)

$(LOADER_OUT): $(LOADER_SRC)
	$(AS) $(LOADER_FLAGS) $< -o $@

$(OUT_DIR)/%.o: $(K_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LINK_OUT): $(LOADER_OUT) $(C_OBJECTS)
	$(LD) $(LINK_FLAGS) $^ -o $@

$(GRUB_OUT): $(LINK_OUT)
	grub-mkrescue -o $@ $(GRUB_FLAGS)

run: all
	qemu-system-i386 -cdrom $(GRUB_OUT)

clean:
	rm -rf $(OUT_DIR) $(GRUB_OUT) $(ISO_DIR)/kernel.elf

.PHONY: all clean run mk_dirs

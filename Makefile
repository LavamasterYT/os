# Directories
SRC_DIR := src
BUILD_DIR := build

# Bootloader and kernel locations
BOOTLOADER_SRC := $(SRC_DIR)/boot/bootloader.asm
BOOTLOADER_BIN := $(BUILD_DIR)/bootloader.bin

# Collect all .c and .asm files in src and subdirectories
C_SOURCES := $(shell find $(SRC_DIR) -name '*.c')
ASM_SOURCES := $(shell find $(SRC_DIR) -name '*.asm')

# Object files (.o) for all C and assembly files, placing them in the build directory
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst $(SRC_DIR)/%.asm,$(BUILD_DIR)/%.o,$(filter-out $(BOOTLOADER_SRC),$(ASM_SOURCES)))

# Kernel binary output
KERNEL_BIN := $(BUILD_DIR)/kernel.bin

# Target: Build the final bootable image
all: boot.img

run:
	qemu-system-x86_64 -fda boot.img -audiodev coreaudio,id=speaker -machine pcspk-audiodev=speaker

# Rule to create boot.img by concatenating bootloader and kernel
boot.img: $(BOOTLOADER_BIN) $(KERNEL_BIN)
	@echo "Creating boot.img..."
	cat $(BOOTLOADER_BIN) $(KERNEL_BIN) > boot.img
	truncate -s 1474560 boot.img
	cp boot.img boot.vfd
	qemu-system-x86_64 -fda boot.img -audiodev coreaudio,id=speaker -machine pcspk-audiodev=speaker

# Rule to create the bootloader binary
$(BOOTLOADER_BIN): $(BOOTLOADER_SRC)
	@mkdir -p $(BUILD_DIR)
	nasm -f bin $< -o $@

# Rule to create kernel binary
$(KERNEL_BIN): $(C_OBJECTS) $(ASM_OBJECTS)
	@echo "Linking kernel..."
	i686-elf-ld -Ttext 0x1000 --oformat binary -o $@ $(ASM_OBJECTS) $(C_OBJECTS)

# Compile all .c files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	i686-elf-gcc -ffreestanding -m32 -c -I $(SRC_DIR)/lib $< -o $@

# Assemble all .asm files except the bootloader
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) boot.img
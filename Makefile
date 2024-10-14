# Define directories
SRC_DIR = src
BUILD_DIR = build

# List of source files (including from subdirectories)
ASM_FILES = $(filter-out $(SRC_DIR)/bootloader.asm $(SRC_DIR)/kernel.asm, $(shell find $(SRC_DIR) -name '*.asm'))
C_FILES = $(shell find $(SRC_DIR) -name '*.c')

# Object files (create a similar directory structure in build)
ASM_OBJ_FILES = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_FILES))
C_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))

# Bootloader, kernel, and final image
BOOTLOADER_BIN = $(BUILD_DIR)/bootloader.bin
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
IMAGE_FILE = boot.img

# Tools
ASM_COMPILER = nasm
C_COMPILER = i686-elf-gcc
LINKER = i686-elf-ld
DD = dd

# Flags
ASM_FLAGS = -f elf32
BOOTLOADER_FLAGS = -f bin
C_FLAGS = -ffreestanding -m32 -c
LD_FLAGS = -Ttext 0x1000 --oformat binary

# Sector size
SECTOR_SIZE = 512

# Default rule
all: $(IMAGE_FILE)

# Rule to generate the final bootable image
$(IMAGE_FILE): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	@echo "Creating bootable image..."
	$(DD) if=$(BOOTLOADER_BIN) of=$(IMAGE_FILE) bs=$(SECTOR_SIZE) count=1 conv=notrunc
	$(DD) if=$(KERNEL_BIN) of=$(IMAGE_FILE) bs=$(SECTOR_SIZE) seek=1 conv=notrunc

# Compile bootloader.asm to binary
$(BOOTLOADER_BIN): $(SRC_DIR)/bootloader.asm | $(BUILD_DIR)
	@echo "Assembling bootloader..."
	$(ASM_COMPILER) $(BOOTLOADER_FLAGS) $< -o $@

# Compile kernel.asm to .o
$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.asm | $(BUILD_DIR)
	@echo "Assembling kernel..."
	$(ASM_COMPILER) $(ASM_FLAGS) $< -o $@

# Compile other .asm files to .o (excluding bootloader.asm and kernel.asm)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	@echo "Assembling $<..."
	$(ASM_COMPILER) $(ASM_FLAGS) $< -o $@

# Compile .c files to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(C_COMPILER) $(C_FLAGS) $< -o $@

# Link kernel, program, and C object files into a single binary
$(KERNEL_BIN): $(BUILD_DIR)/kernel.o $(ASM_OBJ_FILES) $(C_OBJ_FILES)
	@echo "Linking kernel, program, and C code..."
	$(LINKER) $(LD_FLAGS) -o $@ $^

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean build files
clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR)/*.o $(BOOTLOADER_BIN) $(KERNEL_BIN) $(IMAGE_FILE)
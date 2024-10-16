all:
	nasm -f bin src/boot/bootloader.asm -o build/bootloader.bin
	nasm -f elf32 src/boot/kernel.asm -o  build/boot/kernel.o 
	i686-elf-gcc -ffreestanding -m32 -c -I ./src/lib src/boot/main.c -o build/boot/main.o 

	i686-elf-gcc -ffreestanding -m32 -c -I ./src/lib src/lib/kernel/io.c -o build/lib/kernel/io.o 
	i686-elf-gcc -ffreestanding -m32 -c -I ./src/lib src/lib/kernel/vga.c -o build/lib/kernel/vga.o

	i686-elf-gcc -ffreestanding -m32 -c -I ./src/lib src/lib/string.c -o build/lib/string.o

	i686-elf-ld -Ttext 0x1000 --oformat binary -o build/kernel.bin build/lib/kernel/io.o build/lib/kernel/vga.o build/lib/string.o build/boot/kernel.o build/boot/main.o

	wsl cat build/bootloader.bin build/kernel.bin >> boot.img
	qemu-system-x86_64 -fda boot.img -display sdl
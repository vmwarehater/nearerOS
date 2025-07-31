all:
	cd kernel && make
	cd loader && make

build-disk:
	make all
	dd if=/dev/zero of=image.img bs=1k count=1440
	mformat -i image.img -f 1440 ::
	mmd -i image.img ::/EFI
	mmd -i image.img ::/EFI/BOOT
	mmd -i image.img ::/SYSTEM
	mcopy -i image.img loader/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i image.img kernel/kernel.exe ::/SYSTEM
run-disk:
	make build-disk
	qemu-system-x86_64 -bios resources/UEFI/OVMF.fd \
		-m 96M -device usb-ehci -device usb-kbd -display sdl \
		-drive file=image.img,format=raw \
		-serial mon:stdio
run-disk-debug:
	make build-disk
	qemu-system-x86_64 -bios resources/UEFI/OVMF.fd \
		-m 512M -device usb-ehci -device usb-kbd -display sdl \
		-drive file=image.img,format=raw \
		-serial mon:stdio \
		-s -S
clean:
	cd kernel && make clean
	cd loader && make clean

clean-disk:
	make clean
	rm image.img


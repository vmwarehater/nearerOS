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
	mcopy -i image.img loader/BOOTAA64.EFI ::/EFI/BOOT
	mcopy -i image.img kernel/kernel.exe ::/SYSTEM
run-disk:
	make build-disk
	qemu-system-aarch64 -bios resources/UEFI/QEMU_EFI.fd \
		-machine virt -cpu cortex-a57 -m 96M -device ramfb -device usb-ehci -device usb-kbd -display sdl \
		-drive if=none,file=image.img,format=raw,id=hd0 \
  		-device virtio-blk-device,drive=hd0 \
		-serial mon:stdio
run-disk-debug:
	make build-disk
	qemu-system-aarch64 -bios resources/UEFI/QEMU_EFI.fd \
		-machine virt -cpu cortex-a57 -m 512M -device ramfb -device usb-ehci -device usb-kbd -display sdl \
		-drive if=none,file=image.img,format=raw,id=hd0 \
  		-device virtio-blk-device,drive=hd0 \
		-serial mon:stdio \
		-s -S
clean:
	cd kernel && make clean
	cd loader && make clean

clean-disk:
	make clean
	rm image.img


all:
	cd src && cd uefi && make
	cd src && make


clean:
	rm -rf *.o
	cd src && rm -rf *.o
	cd src && cd uefi && rm -rf *.o
	cd src && cd uefi && rm -rf *.a
	rm BOOTAA64.EFI
	rm BOOTAA64.lib
	cd src && rm -rf build
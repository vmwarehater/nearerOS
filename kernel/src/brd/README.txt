
the "brd" directory contains everything that is board specifc, such as UART addresses and how to interact with them with other board
specific stuff

stock stuff will be the QEMU virt platform for AARCH64



I will soon make a driver interface and put all of these stuff into a specific driver so
the kernel can load the specific driver needed for the board we are using
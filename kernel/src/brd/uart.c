#include "uart.h"


/*
    nearerOS UART Board-Specific Abstractions
    Copyright Najib Ahmed, All Rights Reserved



    theres a funny issue where every board has their own way and specific address 
    (or even not an address) to do stuff with the UART. this file was made just to abstract this


    every function here in the end of the day needs to be doing what its supposed to, you can change 
    the implementation (stock is the AARCH64 QEMU VIRT of reading and writing directly to 0x09000000)
    as long as it does what its supposed to do and doesn't break other parts of the kernel.
*/


void brdWriteCharacterIntoUart(char character){
    *(volatile uint8_t*)0x09000000 = character;
}

char brdReadCharacterFromUartWithoutBlocking(){
    return *(volatile uint8_t*)0x09000000;
}

char brdReadCharacterFromUart(){
    while(*(volatile uint8_t*)(0x09000000 + 0x18) & (1 << 4));
    return *(volatile uint8_t*)0x09000000;
}
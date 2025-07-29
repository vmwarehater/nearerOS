#include "uart.h"


/*
    nearerOS UART Board-Specific Abstractions
    Copyright Najib Ahmed, All Rights Reserved
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
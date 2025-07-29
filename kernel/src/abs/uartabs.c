#include "uartabs.h"
#include "../brd/uart.h"



/*
    nearerOS UART Abstractions
    Copyright Najib Ahmed, All Rights Reserved
*/




void absWriteStringIntoUart(char* string){
    while(*string != '\0'){
        brdWriteCharacterIntoUart(*string);
        string++;
    }
}


void absReadUartIntoString(char* string, uint16_t size, bool cleanBuffer){
    if(cleanBuffer == true){
        for(int i = 0; i <= size; i++){
            string[i] = '\0';
        }
    }
    uint16_t curIndex = 0;
    uint16_t sizeCutByTwo = size - 2;
    bool shouldExit;
    while(curIndex < sizeCutByTwo){
        char character = brdReadCharacterFromUart();
        if(character == 13) break;
        // if(character == 127){
        //     string[curIndex] = '\0';
        //     curIndex--;
        //     string[curIndex] = '\0';
        //     brdWriteCharacterIntoUart('\b');
        // }
        brdWriteCharacterIntoUart(character);
        string[curIndex] = character;
        curIndex++;
    }
    string[curIndex] = '\0';
    brdWriteCharacterIntoUart('\n');
}
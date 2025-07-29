#include <stdint.h>
#include "brd/uart.h"
#include "abs/uartabs.h"
#include "arch/exceptions.h"


/*
    nearerOS Kernel Entrypoint
    Copyright Najib Ahmed, All Rights Reserved
*/


// needed stuff for clang
void __chkstk(){};


void kEntry(){
    absWriteStringIntoUart("Successfully entered nearerOS kernel\n");
    arSetupExceptions();

    brdWriteCharacterIntoUart('\n');
    absWriteStringIntoUart("\n\nnearerOS UART Shell\nCopyright Najib Ahmed, All Rights Reserved\n\n");

    while(1){
        absWriteStringIntoUart("Test Shell> ");
        char buffer[512];
        absReadUartIntoString(buffer, 512, true);
        absWriteStringIntoUart(buffer);
        brdWriteCharacterIntoUart('\n');
    }
}

#include <stdint.h>
#include "brd/uart.h"
#include "abs/uartabs.h"
#include "arch/exceptions.h"
#include "rt/runtime.h"
#include "ert/exruntime.h"
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
        char first[256];
        char second[256];
        absReadUartIntoString(buffer, 512, true);
        ertPrintStatusIntoUART("Current time in RTC is", *(volatile uint64_t*)0x09010000);
        rtSplitStringInTwo(buffer, first, 256, second, 256, ' ');
        absWriteStringIntoUart(first);
        absWriteStringIntoUart("\n=========\n");
        absWriteStringIntoUart(second);
        brdWriteCharacterIntoUart('\n');
    }
}

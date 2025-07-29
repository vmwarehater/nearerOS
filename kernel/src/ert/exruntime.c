#include "exruntime.h"
#include "../rt/runtime.h"
#include "../abs/uartabs.h"
#include "../brd/uart.h"

/*
    nearerOS External Runtime Functions
    Copyright Najib Ahmed, All Rights Reserved


    All of these functions were made purely for conversions, 
    string manipulation, memory manipulation and status printing
    that would be tedious to do over and over and over again. 
    that also depend on other modules for their work.


    If you are making a function that isn't using any other modules,
    please use the rt module.

*/



void ertPrintStatusIntoUART(char* message, uint64_t status){
    char string[256];
    rtUnsignedIntegerToString(status, string, 255);
    absWriteStringIntoUart(message);
    absWriteStringIntoUart(": ");
    absWriteStringIntoUart(string);
    brdWriteCharacterIntoUart('\n');
}
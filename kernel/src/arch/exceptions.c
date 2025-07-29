#include "exceptions.h"
#include "../brd/uart.h"
#include "../abs/uartabs.h"




/*
    nearerOS Exception Handler
    Copyright Najib Ahmed, All Rights Reserved
*/

typedef void (*VectorFunction)();
extern void arLoadExceptions();


void arUnimplemented(){
    brdWriteCharacterIntoUart('w');
    while(1){continue;}
}

void arSetupExceptions(){
    absWriteStringIntoUart("Loading Exception Vector into VBAR_EL1\n");
    arLoadExceptions();
    absWriteStringIntoUart("Loaded Exception Vector\n");
}
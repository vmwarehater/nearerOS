#include "exceptions.h"
#include "../abs/uartabs.h"




/*
    nearerOS Exception Handler
    Copyright Najib Ahmed, All Rights Reserved


    Exceptions are loaded in VBAR_EL1, if you want to edit the exception vector 
    table, go to exceptions.S
*/

typedef void (*VectorFunction)();
extern void arLoadExceptions();


void arUnimplemented(){
    absWriteStringIntoUart("An unimplemented exception has occured");
    while(1){continue;}
}

void arSetupExceptions(){
    absWriteStringIntoUart("Loading Exception Vector into VBAR_EL1\n");
    arLoadExceptions();
    absWriteStringIntoUart("Loaded Exception Vector\n");
}
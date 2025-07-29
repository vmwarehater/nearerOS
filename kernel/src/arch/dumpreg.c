#include "dumpreg.h"
#include "../ert/exruntime.h"
#include "../abs/uartabs.h"


extern void arBeginDumpingOfRegisters();


void arPrintDumpedRegisters(KSYSTEMREGSTATE* regstate){
    ertPrintHexadecimalStatusIntoUART("x0", (uint64_t)regstate->x0);
    ertPrintHexadecimalStatusIntoUART("x1", regstate->x1);
    ertPrintHexadecimalStatusIntoUART("x2", regstate->x2);
    ertPrintHexadecimalStatusIntoUART("x3", regstate->x3);
    ertPrintHexadecimalStatusIntoUART("x4", regstate->x4);
    ertPrintHexadecimalStatusIntoUART("x5", regstate->x5);
    ertPrintHexadecimalStatusIntoUART("x6", regstate->x6);
    ertPrintHexadecimalStatusIntoUART("x7", regstate->x7);
    ertPrintHexadecimalStatusIntoUART("x8", regstate->x8);
    ertPrintHexadecimalStatusIntoUART("x9", regstate->x9);
    ertPrintHexadecimalStatusIntoUART("x10", regstate->x10);
    ertPrintHexadecimalStatusIntoUART("x11", regstate->x11);
    ertPrintHexadecimalStatusIntoUART("x12", regstate->x12);
    ertPrintHexadecimalStatusIntoUART("x13", regstate->x13);
    ertPrintHexadecimalStatusIntoUART("x14", regstate->x14);
    ertPrintHexadecimalStatusIntoUART("x15", regstate->x15);
    ertPrintHexadecimalStatusIntoUART("x16", regstate->x16);
    ertPrintHexadecimalStatusIntoUART("x17", regstate->x17);
    ertPrintHexadecimalStatusIntoUART("x18", regstate->x18);
    ertPrintHexadecimalStatusIntoUART("fp", regstate->fp);
    ertPrintHexadecimalStatusIntoUART("lr", regstate->lr);
    ertPrintHexadecimalStatusIntoUART("xzr", regstate->xzr);
    ertPrintHexadecimalStatusIntoUART("esr", regstate->esr);
    ertPrintHexadecimalStatusIntoUART("far", regstate->far);
}

void arDumpSystemRegisters(){
    absWriteStringIntoUart("\n\nBeginning Dump of System Registers....\n");
    absWriteStringIntoUart("\n--------------------------------------------\n");
    arBeginDumpingOfRegisters();
    absWriteStringIntoUart("--------------------------------------------\n");
}
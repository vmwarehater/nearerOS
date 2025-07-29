#ifndef EXRUNTIME_H_INCLUDED
#define EXRUNTIME_H_INCLUDED







#include <stdint.h>





void ertPrintStatusIntoUART(char* message, uint64_t status);
void ertPrintHexadecimalStatusIntoUART(char* message, uint64_t status);
void ertCheckEveryBitOfTheHexadecimal(uint64_t hexadecimal);




#endif
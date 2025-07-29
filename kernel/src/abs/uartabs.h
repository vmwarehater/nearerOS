#ifndef UARTABS_H_INCLUDED
#define UARTABS_H_INCLUDED






#include <stdint.h>
#include <stdbool.h>



void absWriteStringIntoUart(char* string);
void absReadUartIntoString(char* string, uint16_t size, bool cleanBuffer);






#endif
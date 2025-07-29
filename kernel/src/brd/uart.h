#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED









#include <stdint.h>




void brdWriteCharacterIntoUart(char character);
char brdReadCharacterFromUartWithoutBlocking();
char brdReadCharacterFromUart();










#endif
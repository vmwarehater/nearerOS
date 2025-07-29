#ifndef RUNTIME_H_INCLUDED
#define RUNTIME_H_INCLUDED







#include <stdint.h>
#include <stdbool.h>




bool rtSplitStringInTwo(const char* initialString, char* firstHalf, uint16_t firstHalfSize, 
                        char* secondHalf, uint16_t secondHalfSize, char deliminter);
uint64_t rtCalculatePower(uint64_t number, uint64_t power);
uint64_t rtStringToUnsignedInteger(const char* string);
bool rtUnsignedIntegerToString(uint64_t integer, char* string, uint16_t size);



#endif
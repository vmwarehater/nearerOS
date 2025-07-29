#include "runtime.h"
#include <stdint.h>


/*
    nearerOS Runtime Functions
    Copyright Najib Ahmed, All Rights Reserved


    All of these functions were made purely for conversions, 
    string manipulation, and memory manipulation that would be tedious
    to do over and over and over again.


    This module can NOT be dependent on ANYTHING ELSE, it should purely be
    for stuff that were listed above. Functions within this module can use
    each other however.

    If you need stuff conversion related that also needs external functions from other 
    modules like brd, abs, arch etc, please use the ert module

*/


bool rtSplitStringInTwo(const char* initialString, char* firstHalf, uint16_t firstHalfSize, 
                        char* secondHalf, uint16_t secondHalfSize, char deliminter)
{   
    bool switchToSecondHalf = false;
    int index = 0;
    while(*initialString != '\0'){
        if(switchToSecondHalf == false){
            if(index >= firstHalfSize - 2 || *initialString == deliminter){
                firstHalf[index] = '\0';
                index = 0;
                switchToSecondHalf = true;
                if(index >= firstHalfSize - 2) continue;
                else goto INCREMENT;
            }
            firstHalf[index] = *initialString;
            index++;
        } else {
            if(index >= secondHalfSize - 2){
                secondHalf[index] = '\0';
                return true;
            }
            secondHalf[index] = *initialString;
            index++;
        }
        INCREMENT:
        initialString++;
    }
    secondHalf[index] = '\0';
    return true;
}

uint64_t rtCalculatePower(uint64_t number, uint64_t power){
    uint64_t result = 1;
    for(int i = 0; i < power; i++){
        result *= number;
    }
    return result;
}


uint64_t rtStringToUnsignedInteger(const char* string){
    uint64_t result = 0;

    while(*string != '\0'){
        if(*string >= 48 && *string <= 57){
            result *= 10;
            result += (*string - 48);
        }
        string++;
    }
    return result;
}

bool rtUnsignedIntegerToString(uint64_t integer, char* string, uint16_t size){
    if(integer == 0){
        if(size <= 2){
            return false;
        }
        string[0] = '0';
        string[1] = '\0';
        return true;
    }
    uint64_t temp = integer;
    uint16_t digits = 0;
    while(temp > 0){
        temp /= 10;
        digits++;
    }
    temp = integer;
    uint64_t index = 0;
    for(int i = digits - 1; i >= 0; i--){
        if(index >= size - 1){
            break;
        }
        uint64_t div = rtCalculatePower(10, i);
        uint64_t singleDigit = temp / div;
        string[index] = 48 + singleDigit;
        index++;
        temp %= div;
    }
    string[index] = '\0';
    return true;
}
#ifndef GOP_H_INCLUDED
#define GOP_H_INCLUDED






#include "uefi/uefi.h"






typedef struct _LDRGOPINFORMATION {
    uint8_t error;
    uint64_t horResX;
    uint64_t verResY;
    uint64_t pixelPerScanLine;
    uint64_t pixelFormat;
    uint64_t framebufferBase;
    uint64_t framebufferSize;
} LDRGOPINFORMATION;

LDRGOPINFORMATION ldrSetupGOP();



#endif
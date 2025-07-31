
/*
    nearerOS Kernel Entrypoint
    Copyright Najib Ahmed, All Rights Reserved
*/
#include <stdint.h>

typedef struct _LDRGOPINFORMATION {
    uint8_t error;
    uint64_t horResX;
    uint64_t verResY;
    uint64_t pixelPerScanLine;
    uint64_t pixelFormat;
    uint64_t framebufferBase;
    uint64_t framebufferSize;
} LDRGOPINFORMATION;

// needed stuff for clang
void __chkstk(){};

void kEntry(LDRGOPINFORMATION* gop){
    volatile uint64_t* fAddr = (volatile uint64_t*)gop->framebufferBase;
    for(int i = 0; i < gop->horResX; i++){
        for(int j = 0; j < gop->verResY; j++){
            fAddr[j * (gop->pixelPerScanLine) + i] = 0xFFFFFFFF;
        }
    }
    while(1){continue;};
}

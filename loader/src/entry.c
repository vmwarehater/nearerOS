#include "uefi/uefi.h"
#include <stdbool.h>
#include "peloader.h"
#define _LOADERBUILD 0

// Thanks for POSIX-UEFI for making it so developing a UEFI loader not be a headache =D

int main(int argc, char **argv) {
    ST->ConIn->Reset(ST->ConIn, true);
    ST->ConOut->Reset(ST->ConOut, true);
    printf("nearerOS UEFI Bootloader\nCopyright Najib Ahmed, All Rights Reserved\n\n");
    int8_t result = ldrLoadPortableExecutableFile("SYSTEM\\kernel.exe");
    if(result != 0){
        printf("ldrLoadPortableExecutableFile failed with result of %d", result);
    }
    while(1){continue;}
    return 0;
}
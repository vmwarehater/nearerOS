#include "uefi/uefi.h"
#include <stdbool.h>
#include "peloader.h"
#include "gop.h"
#define _LOADERBUILD 0

// Thanks for POSIX-UEFI for making it so developing a UEFI loader not be a headache =D

int main(int argc, char **argv) {
    
    LDRGOPINFORMATION gop = ldrSetupGOP();
    if(gop.error == 1){
        printf("The bootloader couldn't set up the graphics output protocal\n");
        printf("Please restart your computer\n");
        while(1){continue;}
    }
    ST->ConIn->Reset(ST->ConIn, true);
    ST->ConOut->Reset(ST->ConOut, true);
    printf("nearerOS UEFI Bootloader\nCopyright Najib Ahmed, All Rights Reserved\n\n");
    int8_t result = ldrLoadPortableExecutableFile(gop, "SYSTEM\\kernel.exe");
    if(result != 0){
        printf("ldrLoadPortableExecutableFile failed with result of %d", result);
    }
    while(1){continue;}
    return 0;
}
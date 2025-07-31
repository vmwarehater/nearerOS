#include "gop.h"

/*
    nearerOS loader GOP setup
    Copyright Najib Ahmed, All Rights Reserved



    thanks to a POSIX-UEFI example to get me started =)
    https://gitlab.com/bztsrc/posix-uefi/-/blob/master/examples/09_vidmodes/vidmodes.c

*/







LDRGOPINFORMATION ldrSetupGOP(){
    efi_guid_t guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    efi_gop_mode_info_t* info = NULL;
    uint64_t infoSize = sizeof(efi_gop_mode_info_t);
    LDRGOPINFORMATION error = {
        .error = 1
    };

    efi_status_t status = BS->LocateProtocol(&guid, NULL, (void**)&gop);
    if(EFI_ERROR(status)){
        return error;
    }
    uint64_t mode = 0;
    if(!gop->Mode){
        mode = 0;
    } else mode = gop->Mode->Mode;
    status = gop->QueryMode(gop, mode, &infoSize, &info);
    if(EFI_ERROR(status)){
        return error;
    }
    if(status == EFI_NOT_STARTED || !gop->Mode) gop->SetMode(gop, 0);
    mode = gop->Mode->Mode;
    printf("GOP mode is %d\n", mode);
    return (LDRGOPINFORMATION){
        .error = 0,
        .horResX = gop->Mode->Information->HorizontalResolution,
        .verResY =  gop->Mode->Information->VerticalResolution,
        .pixelPerScanLine =  gop->Mode->Information->PixelsPerScanLine,
        .pixelFormat =  gop->Mode->Information->PixelFormat,
        .framebufferBase = gop->Mode->FrameBufferBase,
        .framebufferSize = gop->Mode->FrameBufferSize
    };
}
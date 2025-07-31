#ifndef PELOADER_H_INCLUDED
#define PELOADER_H_INCLUDED











#include "uefi/uefi.h"
#include "gop.h"





int8_t ldrLoadPortableExecutableFile(LDRGOPINFORMATION gopInfo, const char* path);











#endif
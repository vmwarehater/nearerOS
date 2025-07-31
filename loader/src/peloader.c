#include "peloader.h"


/*
    nearerOS PE Loader
    Copyright Najib Ahmed, All Rights Reserved


    thanks to https://0xrick.github.io/win-internals/pe3/ for
    the resources!
*/

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;
typedef unsigned char BYTE;
typedef uint64_t ULONGLONG;
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16
#define IMAGE_SIZEOF_SHORT_NAME 8
typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
    WORD   e_magic;                     // Magic number
    WORD   e_cblp;                      // Bytes on last page of file
    WORD   e_cp;                        // Pages in file
    WORD   e_crlc;                      // Relocations
    WORD   e_cparhdr;                   // Size of header in paragraphs
    WORD   e_minalloc;                  // Minimum extra paragraphs needed
    WORD   e_maxalloc;                  // Maximum extra paragraphs needed
    WORD   e_ss;                        // Initial (relative) SS value
    WORD   e_sp;                        // Initial SP value
    WORD   e_csum;                      // Checksum
    WORD   e_ip;                        // Initial IP value
    WORD   e_cs;                        // Initial (relative) CS value
    WORD   e_lfarlc;                    // File address of relocation table
    WORD   e_ovno;                      // Overlay number
    WORD   e_res[4];                    // Reserved words
    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    WORD   e_oeminfo;                   // OEM information; e_oemid specific
    WORD   e_res2[10];                  // Reserved words
    LONG   e_lfanew;                    // File address of new exe header
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER {
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
  DWORD VirtualAddress;
  DWORD Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_OPTIONAL_HEADER64 {
  WORD                 Magic;
  BYTE                 MajorLinkerVersion;
  BYTE                 MinorLinkerVersion;
  DWORD                SizeOfCode;
  DWORD                SizeOfInitializedData;
  DWORD                SizeOfUninitializedData;
  DWORD                AddressOfEntryPoint;
  DWORD                BaseOfCode;
  ULONGLONG            ImageBase;
  DWORD                SectionAlignment;
  DWORD                FileAlignment;
  WORD                 MajorOperatingSystemVersion;
  WORD                 MinorOperatingSystemVersion;
  WORD                 MajorImageVersion;
  WORD                 MinorImageVersion;
  WORD                 MajorSubsystemVersion;
  WORD                 MinorSubsystemVersion;
  DWORD                Win32VersionValue;
  DWORD                SizeOfImage;
  DWORD                SizeOfHeaders;
  DWORD                CheckSum;
  WORD                 Subsystem;
  WORD                 DllCharacteristics;
  ULONGLONG            SizeOfStackReserve;
  ULONGLONG            SizeOfStackCommit;
  ULONGLONG            SizeOfHeapReserve;
  ULONGLONG            SizeOfHeapCommit;
  DWORD                LoaderFlags;
  DWORD                NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

typedef struct _IMAGE_NT_HEADERS64 {
    DWORD Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_SECTION_HEADER {
    BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
    union {
            DWORD   PhysicalAddress;
            DWORD   VirtualSize;
    } Misc;
    DWORD   VirtualAddress;
    DWORD   SizeOfRawData;
    DWORD   PointerToRawData;
    DWORD   PointerToRelocations;
    DWORD   PointerToLinenumbers;
    WORD    NumberOfRelocations;
    WORD    NumberOfLinenumbers;
    DWORD   Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

#define FIELD_OFFSET(type, field) ((unsigned long long) __builtin_offsetof(type, field))
#define GetFirstSectionOfImage(h) ((PIMAGE_SECTION_HEADER) ((unsigned long)h+FIELD_OFFSET(IMAGE_NT_HEADERS64,OptionalHeader)+((PIMAGE_NT_HEADERS64)(h))->FileHeader.SizeOfOptionalHeader))



int8_t ldrLoadPortableExecutableFile(LDRGOPINFORMATION gopInfo, const char* path){
    FILE* filep = fopen(path, "r");
    if(filep == NULL) return -1;
    fseek(filep, 0, SEEK_END);
    long size = ftell(filep);
    fseek(filep, 0, SEEK_SET);
    char* file = malloc(size + 10);
    fread((void*)file, size, 1, filep);
    fclose(filep);
    PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)file;
    PIMAGE_NT_HEADERS64 ntheader = (PIMAGE_NT_HEADERS64)(file + dosheader->e_lfanew);
    if(memcmp(ntheader, "PE\0\0", 4) != 0){
        printf("This is not a PE Executable\n");
        return -2;
    }
    printf("Valid PE Executable!\n");
    uint64_t imageBase = ntheader->OptionalHeader.ImageBase;
    uint64_t imageSize = ntheader->OptionalHeader.SizeOfImage;
    uint64_t pages = (imageSize + 0xFFF) / 0x1000;
    printf("Image Base is %p, Image Size is %d, Pages for Allocation is %d\n", imageBase, imageSize, pages);
    efi_status_t efiStatus = BS->AllocatePages(AllocateAddress, 
        EfiLoaderCode, pages, &imageBase);
    if(efiStatus != EFI_SUCCESS){
        printf("BS->AllocatePages failed with EFISTATUS of %d", efiStatus);
        return -3;
    }
    PIMAGE_SECTION_HEADER sectionHeader;
    sectionHeader = GetFirstSectionOfImage(ntheader);
    for(int i = 0; i < ntheader->FileHeader.NumberOfSections; i++){
        printf("%s -> %p\n", sectionHeader->Name, (imageBase + sectionHeader->VirtualAddress));
        if(strcmp((char*)sectionHeader->Name, ".gopD") == 0){
            memcpy((void*)(imageBase + sectionHeader->VirtualAddress), 
                (void*)(&gopInfo), sizeof(LDRGOPINFORMATION));
        } else {
            memcpy((void*)(imageBase + sectionHeader->VirtualAddress), 
                (void*)(file + sectionHeader->PointerToRawData), sectionHeader->SizeOfRawData);
        }
        sectionHeader++;

    }
    void* entry = (void*)(imageBase + ntheader->OptionalHeader.AddressOfEntryPoint);
    printf("Entrypoint Location: %p\n", entry);
    void(*EntryPoint)() = (void (*)())entry;
    free(file);
    printf("Exiting UEFI Boot Services and jumping to the nearerOS Kernel!\n");
    sleep(1);
    ST->ConIn->Reset(ST->ConIn, 1);
    ST->ConOut->Reset(ST->ConOut, 1);
    exit_bs();
    EntryPoint();
    return 0;
} 
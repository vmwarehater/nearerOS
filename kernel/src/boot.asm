section .bss
    align 16
stackBottom:
    resb 256000
stackTop:

section .gopD
    align 8
gopInfoBottom:
    resb 10000 ; size is 48 but i added 2 extra bytes


section .text

extern kEntry
global kLoaderEntry
kLoaderEntry:
    mov rsp, stackTop
    mov rcx, gopInfoBottom
    call kEntry
loop:
    jmp loop


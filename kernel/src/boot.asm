section .bss
    align 16
stack_bottom:
    resb 256000
stack_top:



section .text

extern kEntry
global kLoaderEntry
kLoaderEntry:
    mov rsp, stack_top
    call kEntry
loop:
    jmp loop




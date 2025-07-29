.global kLoaderEntry





kLoaderEntry:
    ldr x7, =kstackend
    mov sp, x7
    bl kEntry
    b .
    ret


.section bss
.align 16
kstack:
    .space 40960
kstackend:




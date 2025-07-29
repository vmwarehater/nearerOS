
.global arLoadExceptions


arLoadExceptions:
    sub sp, sp, #16
    ldr x0, =ExceptionVector
    msr VBAR_EL1, x0
    add sp, sp, 16
    ret

ExceptionVector:
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
.balign 0x80
    b arUnimplemented
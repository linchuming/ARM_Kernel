.globl init_start
.text
.arm

init_start:
    ldr	sp, =0x80000000
    movs	fp, sp
    bl	main
    mov r0, #0x100
    swi 0x100

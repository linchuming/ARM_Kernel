/*
	kernel.S
	Author: cmlin
	Email: 13307130255@fudan.edu.cn
 */

.globl kernel_bootasm

.text
.arm

kernel_bootasm:
	ldr	sp, =0x20000000
	movs	fp, sp
	bl	main


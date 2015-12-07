/*
	kernel.S
	Author: cmlin
	Email: 13307130255@fudan.edu.cn
*/
.globl vector_table
.globl vector_end
.equ  stubs_offset,  0x0
.globl kernel_bootasm


.globl SWI_handler
.globl IRQ_handler
.globl PrefetchAbortHandler
.globl DataAbortHandler
.text
.arm


vector_table:
	NOP
	NOP //Undefined
	b SWI_handler + stubs_offset //SWI interrupt
	b PrefetchAbortHandler + stubs_offset //PrefetchAbortHandler
	b DataAbortHandler + stubs_offset //DataAbortHandler
	NOP
	b  IRQ_handler + stubs_offset  //IRQ interrupt
	NOP //FIQ interrupt
vector_end:

SWI_handler:
    stmfd sp!,{r0-r12,lr}
    ldr r0, [lr, #-4]
    bic r0, r0, #0xFF000000 //Get the SWI interrupt id
    mov r12, sp

    bl SWI_interrupt

    ldmfd sp!, {r0-r12,pc}^

IRQ_handler:
    stmfd sp!, {r0-r12, lr}

    bl IRQ_interrupt

    ldmfd sp!, {r0-r12, pc}^

PrefetchAbortHandler:
    stmfd sp!, {r0-r12, lr}

    bl PrefetchAbort_interrupt

    ldmfd sp!, {r0-r12, pc}^

DataAbortHandler:
    stmfd sp!, {r0-r12, lr}

    bl DataAbortHandler_interrupt

    ldmfd sp!, {r0-r12, pc}^

kernel_bootasm:
	ldr	sp, =0x20000000
	movs	fp, sp
	bl	main

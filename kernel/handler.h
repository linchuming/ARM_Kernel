/*
    headler.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _HEADLER_H
#define _HEADLER_H
#include "kernel.h"
#include "memory.h"

void interrupt_init()
{
    /*
    asm volatile(
        "mrc p15, 0, r0, c1, c0, 0\n\t"
        "orr r0, #0x2000\n\t"
        "mcr p15, 0, r0, c1, c0, 0\n\t"
        "isb\n\t"
        ::: "r0"
    );
    */
    /* copy the vector table to the address 0x0 */
    irq_mask_open();
    extern char vector_table[],vector_end[];
    memcpy((void*)0,vector_table,vector_table-vector_end);

}
uint cpsr = 0;
void read_cpsr()
{
    uart_spin_puts("The cpsr is ");
    asm volatile(
        "mrs r0,cpsr\n\t"
        "ldr r1, =cpsr\n\t"
        "str r0,[r1]\n\t"
    );
    puts_uint(cpsr);
    uart_spin_puts("\r\n");
}
void SWI_interrupt(uint num)
{
    switch(num) {
        case 1:
            uart_spin_puts("You are in the SWI handler.\r\n");
            break;

    }
}

void IRQ_interrupt()
{
    uart_spin_puts("You are in the IRQ handler.\r\n");
    uart_spin_getbyte();

}

void PrefetchAbort_interrupt()
{
    uart_spin_puts("You are in the PrefetchAbort handler.\r\n");
    uart_spin_getbyte();
}

void DataAbortHandler_interrupt()
{
    uart_spin_puts("You are in the DataAbort handler.\r\n");
    uart_spin_getbyte();
}
#endif // _HEADLER_H

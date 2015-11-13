/*
    kernel.c
    Author: cmlin
*/

#include "kernel.h"
#include "mmu.h"
#include "memory.h"

uint new_pc = 0;
void test()
{
    uart_spin_puts("The new pc is ");
    asm(
        "ldr r0, =new_pc\n\t"
        "str pc, [r0]\n\t"
    );
    puts_uint(new_pc);
    uart_spin_puts("\r\n");
}

int main()
{
	/* Wait for UART fifo to flush */
	sleep(1);
    /* Initialize and enable UART */
	uart_init();
	uart_enable();

    uart_spin_puts("Welcome to the kernel on ARM cmlin!\r\n");
    uart_spin_puts("write page success and ready to enable mmu.\r\n");
    /* enable mmu */
    enable_mmu();
    uart_spin_puts("enable mmu success.\r\n");

    /* update pc value to pc+KERN_BASE */
    asm volatile(
        "ldr r0, =KERN_BASE\n\t"
        "ldr r1, [r0]\n\t"
        "add pc, pc, r1\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
    );


    //uint new_pc = old_pc + KERN_BASE;
    //sleep(1);
    test();
    /* Initialize the memory calloc */

    mem_init();

    char * addr1 = kalloc(10);
    puts_uint((uint)addr1);

    char * addr2 = kalloc(1);
    puts_uint((uint)addr2);

    char* addr3 = kalloc_align(16);
    puts_uint((uint)addr3);

    return 0;
}

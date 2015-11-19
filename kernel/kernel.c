/*
    kernel.c
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#include "kernel.h"
#include "mmu.h"
#include "memory.h"

uint new_pc = 0;
void test_pc()
{
    uart_spin_puts("The new pc is ");
    asm volatile(
        "ldr r0, =new_pc\n\t"
        "str pc, [r0]\n\t"
    );
    puts_uint(new_pc);
    uart_spin_puts("\r\n");
}
uint sp = 0;
void test_sp()
{
    uart_spin_puts("The sp is ");
    asm volatile(
        "ldr r0, =sp\n\t"
        "str sp, [r0]\n\t"
    );
    puts_uint(sp);
    uart_spin_puts("\r\n");
}

void test_mem()
{
    char * addr1 = kalloc(1);
    puts_uint((uint)addr1);

    char * addr2 = kalloc(1);
    puts_uint((uint)addr2);

    char* addr3 = kalloc_align(4);
    puts_uint((uint)addr3);

    kfree(addr2,1);

    uart_spin_puts("show the free memory:\r\n");
    showFreememory();
}
int main()
{
	/* Wait for UART fifo to flush */
	sleep(1);
    /* Initialize and enable UART */
	uart_init();
	uart_enable();

    uart_spin_puts("Welcome to the kernel on ARM cmlin!\r\n");
    uart_spin_puts("ready to enable mmu.\r\n");
    /* enable mmu */
    enable_mmu();
    uart_spin_puts("enable mmu success.\r\n");

    /* Update pc value to pc+KERN_BASE */
    asm volatile(
        "ldr r0, =KERN_BASE\n\t"
        "ldr r1, [r0]\n\t"
        "add pc, pc, r1\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
    );
    /* */

    test_pc();

    /* Update sp value */
    test_sp();
    asm volatile(
        "ldr r0, =KERN_BASE\n\t"
        "ldr r1, [r0]\n\t"
        "add sp, sp, r1\n\t"
    );
    test_sp();

    /* Initialize the memory calloc */
    mem_init();
    /* */
    test_mem();

    return 0;
}

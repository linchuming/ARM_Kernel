#include "kernel.h"
#include "mmu.h"
void test();

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
    uart_spin_puts("Welcome to the kernel on the ARM!\r\n");
    uart_spin_puts("write page success and ready to enable mmu.\r\n");
    //enable mmu
    enable_mmu();
    uart_spin_puts("enable mmu success.\r\n");

    //update pc value to pc+KERN_BASE
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
    test();

    return 0;
}

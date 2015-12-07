/*
    kernel.c
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#include "kernel.h"
#include "mmu.h"
#include "pool.h"
#include "memory.h"
#include "handler.h"
#include "l2_page.h"
uint addr;

uint new_pc = 0;
void read_pc()
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
void read_sp()
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
    kfree(addr1,1);
    kfree(addr3,4);
}


void debug()
{
    pkb_num = 0;
    char* ttb = new_ttb();
    struct mem_list * list = (struct mem_list*)kalloc(1);
    list->addr = (uint)kalloc(1);
    puts_uint(list->addr);
    struct mem_list * p = list;
    p = p + 4;
    p->addr = (uint)kalloc(1);
    puts_uint(p->addr);
    p = p + 4;
    p->addr = 0;
    write_process_page(ttb,0x400000,list);
    free_process_memory(ttb);
    uart_spin_getbyte();
}

/* main() the kernel entry */
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
    update_pc();
    uart_spin_puts("update the pc value.\r\n");
    /* */
    /* Update sp value */
    update_sp();
    uart_spin_puts("update the sp value.\r\n");

    /* Initialize Interrupt*/
    interrupt_init();
    uart_spin_puts("Initialize Interrupt success.\r\n");
    /* remove map of the lower address 0x0~0x800000 */
    remove_lower_address();
    uart_spin_puts("remove the lower address.\r\n");
    /* Initialize the memory calloc */
    mem_init();
    uart_spin_puts("Initialize memory allocation.\r\n");

    debug();

    asm volatile(
        "ldr r0, =1000\n\t"
        "swi 0x1\n\t"
        "isb\n\t"
        ::: "r0"
    );

    uart_spin_puts("Kernel Ends.\r\n");


    /* Holding the kernel */
    while(1) ;
    return 0;
}

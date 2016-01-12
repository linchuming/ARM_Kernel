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
#include "cpu1.h"
#include "process.h"
#include "load_init.h"
#include "filesystem.h"

void test_mem()
{
    char * addr1 = kalloc(1);
    puts_uint((uint)addr1);

    char * addr2 = kalloc(1);
    puts_uint((uint)addr2);

    char* addr3 = kalloc_align(4);
    puts_uint((uint)addr3);
    showFreememory();
    uart_spin_getbyte();

    kfree(addr2,1);
    kfree(addr1,1);
    kfree(addr3,4);
    addr1 = new_kb();
    puts_uint((uint)addr1);
    showFreememory();
    uart_spin_getbyte();

}


void debug()
{
    uart_spin_puts("debug\r\n");
    pkb_num = 0;
    char* ttb = new_ttb();
    struct mem_list * list = (struct mem_list*)kalloc(1);
    list->addr = (uint)kalloc(1) - KERN_BASE;
    puts_uint(list->addr);
    struct mem_list * p = list;
    p = p + 4;
    p->addr = (uint)kalloc(1) - KERN_BASE;
    puts_uint(p->addr);
    p = p + 4;
    p->addr = 0;
    write_process_page(ttb,0x400000,list);
    free_process_memory(ttb);
    uart_spin_puts("free memory\r\n");
    kfree((char*)list,1);
    showFreememory();
    uart_spin_getbyte();
}

/* kernel_main() the kernel entry */
int kernel_main()
{
	/* Wait for UART fifo to flush */
	sleep(1);
    /* Initialize and enable UART */
	uart_init();
	uart_enable();
    /* Initialize SDHCI interface */
	sd_init();
	uart_spin_puts("FW: SD Controller initialized.\r\n");

	/* Initialize SD card */
	uint ret = sd_spin_init_mem_card();

	if (ret == 0) uart_spin_puts("FW: SD Card initialized.\r\n");
	else if (ret == 1) uart_spin_puts("FW: SDHC Card initialized.\r\n");
	else {
		uart_spin_puts("FW: Card initialization failed.\r\n");
	}


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
    invalidate_TLB();
    enable_cache();
    /* Initialize Interrupt*/
    interrupt_init();
    uart_spin_puts("Initialize Interrupt success.\r\n");

    /* Initialize the memory calloc */
    mem_init();
    pkb_num = 0; slab_num = 0;
    spinlock_init(&pool_lock);
    uart_spin_puts("Initialize memory allocation.\r\n");
    //test_mem();
    ICC_init(0xF0);
    ICD_init();
    proc_init();
    schedule_init();
    uart_spin_puts("Initialize schedule.\r\n");
    load_init();
    create_init();

    file_system_init();
    /* Start the cpu1 */
    cpu1_start();

    timer_init(10);
    timer_start();
    read_cpsr();
    uart_spin_puts("timer init.\r\n");
    enter_schedule();
    //debug();
    //uart_spin_puts("Kernel is running.\r\n");
    /* Holding the kernel */
    while(1);
    return 0;
}

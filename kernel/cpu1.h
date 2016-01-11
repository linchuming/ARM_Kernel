/*
    cpu1.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _CPU1_H
#define _CPU1_H

#include "kernel.h"
#include "mmu.h"
#include "memory.h"
#include "mode.h"
#include "handler.h"
#include "timer.h"
#include "process.h"

void cpu1_init();

void cpu1_start()
{
    out32(0xFFFFFFF0,(uint)cpu1_init);
    asm volatile(
        "isb\n\t"
        "sev\n\t"
    );
    uart_spin_puts("CPU1 start!\r\n");
}

void enable_cpu1_mmu()
{
    /* Set the TTB */
    asm volatile(
        "mov r0, %0\n\t"
        "mcr p15,0,r0,c2,c0,0\n\t"
        ::"r"(KERN_CPU1_TTB)
    );
    /* Set the DOMAIN */
    asm volatile(
        "ldr r0, =0x7\n\t"
        "mcr p15,0,r0,c3,c0,0\n\t"
    );
    invalidate_TLB();
    /* Enable MMU */
    asm volatile(
        "mrc p15,0,r0,c1,c0,0\n\t"
        "orr r0,r0,#0x1\n\t"
        "mcr p15,0,r0,c1,c0,0\n\t"
        "isb\n\t"
    );

    invalidate_TLB();

    /* Enable SCU */
    out32(SCU_CONTROL,0x3);
}

void cpu1_init()
{
    //setting the sp value of some modes
    svc_enable();
    asm volatile(
        "mov sp,%0\n\t"
        ::"r"(KERN_BASE+CPU1_SVC_SP_ADDR)
    );
    irq_enable();
    asm volatile(
        "mov sp,%0\n\t"
        ::"r"(KERN_BASE+CPU1_IRQ_SP_ADDR)
    );
    sys_enable();
    asm volatile(
        "mov sp,%0\n\t"
        ::"r"(CPU1_SP_ADDR)
    );
    //copy the page of CPU0 TTB
    memcpy((void*)KERN_CPU1_TTB,(void*)KERN_TTB,4096*4);
    enable_cpu1_mmu();
    enable_cache();
    update_sp();
    update_pc();
    invalidate_TLB();

    /* set the vector address by c12 */
    asm volatile(
        "ldr r0, =vector_table\n\t"
        "movs r1, %0\n\t"
        "add r0, r0, r1\n\t"
        "mcr p15, 0, r0, c12, c0, 0\n\t"
        "isb\n\t"
        :: "r"(KERN_BASE)
        : "r0","r1"
    );
    irq_mask_open();

    ICC_init(0xE0);
    ICD_init();
    proc_init();
    timer_init(10);
    timer_start();
    enter_schedule();
    while(1){
        sleep(1);

        //uart_spin_puts("cpu1:hhhh\r\n");
    }


}

#endif

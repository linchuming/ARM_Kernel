/*
    headler.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _HEADLER_H
#define _HEADLER_H
#include "kernel.h"
#include "memory.h"
#include "syscall.h"
#include "schedule.h"

#define ICCIAR      0xF8F0010C
#define IRQ_ID_MASK 0x3FF
#define ICCICR      0xF8F00100
#define ICDSGIR     0xF8F01F00
#define ICCPMR      0xF8F00104
#define ICCEOIR     0xF8F00110

#define ICDDCR      0xF8F01000
#define ICDICFR     0xF8F01C00 //ICDICFR[5:0]
#define ICDIPR      0xF8F01400 //ICDIPR[23:0]
#define ICDIPTR     0xF8F01800 //ICDIPTR[23:0]
#define ICDISER     0xF8F01100 //ICDISER[2:0]
#define ICDICPR     0xF8F01280 //ICDICPR[2:0]
//ICDISER0 is banked for each connected processor.

#define TIMER_IRQ   0x1d
void ICD_init()
{
    //out32(ICDIPR,0x0); //set priority
    //out32(ICDIPTR,0xFFFFFFFF); //set CPU ID
    //out32(ICDISER,0xFFFFFFFF); //set interrupt id enable
    uint id;
    uint cpuID = 0x03;
    cpuID |= cpuID << 8;
    cpuID |= cpuID << 16;
    /*
    for(id=0;id<95;id+=16) {
        out32(ICDICFR+(id>>2),0x0);
    }
    */
    for(id=0;id<95;id+=4) {
        out32(ICDIPR+id,0xa0a0a0a0);
    }
    for(id=0;id<95;id+=4) {
        out32(ICDIPTR+id,cpuID);
    }
    for(id=0;id<95;id+=32) {
        out32(ICDISER+(id>>3),0xFFFFFFFF);
    }

    out32(ICDDCR,0x1);
}

void ICC_init(uint priority)
{
    out32(ICCPMR,priority); //set CPU priority
    out32(ICCICR,0x1);

}



extern char vector_table[];
void interrupt_init()
{
    svc_enable();
    asm volatile(
        "mov sp, %0\n\t"
        ::"r"(KERN_BASE+SVC_SP_ADDR)
    );
    irq_enable();
    asm volatile(
        "mov sp, %0\n\t"
        ::"r"(KERN_BASE+IRQ_SP_ADDR)
    );
    sys_enable();
    irq_mask_open();
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
    spinlock_init(&syscall_lock);

}
void SWI_interrupt(uint num,uint *reg)
{
    //uart_spin_puts("You are in the SWI handler.\r\n");
    //puts_uint(reg[12]);
    //puts_uint(num);
    switch(num) {
        case 0x1:
            puts_uint((uint)reg);
            read_cpsr();
            break;
        case 0x2:
            reset_schedule(reg);
            break;

        case 0x100:
        {
            syscall_handler(reg);
            break;
        }


    }
}

void IRQ_interrupt(uint *reg)
{
    //uart_spin_puts("You are in the IRQ handler.\r\n");
    uint id = in32(ICCIAR) & IRQ_ID_MASK;
    switch (id) {
        case TIMER_IRQ:
            //uart_spin_puts("timer!!\r\n");
            //puts_uint(proc[getCPUId()].state);
            if(proc[getCPUId()].state==RUNNING) {
                //uart_spin_puts("timer interrupt\r\n");
                //puts_uint(getCPUId());
                timer_schedule(reg);
            }
            out32(0xF8F0060C,1);
            out32(ICDICPR,1<<0x1d);
        break;
    }
    out32(ICCEOIR,(in32(ICCEOIR) & ~(IRQ_ID_MASK))|id );
    //uart_spin_getbyte();

}

void PrefetchAbort_interrupt(uint * reg)
{
    uart_spin_puts("You are in the PrefetchAbort handler.\r\n");
    puts_uint(reg[12]);
    puts_uint(getCPUId());
    uart_spin_getbyte();
}

void DataAbortHandler_interrupt(uint * reg)
{
    uart_spin_puts("You are in the DataAbort handler.\r\n");
    puts_uint(reg[12]);
    puts_uint(getCPUId());
    uart_spin_getbyte();
}
#endif // _HEADLER_H

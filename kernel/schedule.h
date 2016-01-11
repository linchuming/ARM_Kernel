/*
    schedule.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "kernel.h"
#include "mmu.h"
#include "process.h"

static spinlock_t schedule_lock;
static uint pcb_counter;

void schedule_init()
{
    spinlock_init(&schedule_lock);
    pcb_init();
    pcb_counter = 0;
}

static inline void enter_schedule()
{
    asm volatile( "swi 0x2" );
}

struct processor * schedule()
{
    struct processor * res;
    while(1) {
        spin_lock(&schedule_lock);
        for(uint i=0;i<MAX_NUM_PROCESS;i++) {
            if(pcb[pcb_counter].state == RUNABLE) {
                pcb[pcb_counter].state = RUNNING;
                res = &(pcb[pcb_counter]);
                //uart_spin_puts("schedule:"); puts_uint((uint)res);
                pcb_counter++;
                if(pcb_counter>=MAX_NUM_PROCESS) pcb_counter = 0;
                release_lock(&schedule_lock);
                return res;
            }
            pcb_counter++;
            if(pcb_counter>=MAX_NUM_PROCESS) pcb_counter = 0;
        }
        release_lock(&schedule_lock);
    }
}

void timer_schedule(uint * reg)
{
    struct processor * m_proc = &proc[getCPUId()];
    //puts_uint((uint)m_proc);
    //puts_uint(m_proc->ttb_addr);
    m_proc->state = UNUSE;
    asm volatile(
        "mrs r0, spsr\n\t"
        "str r0, [%0]\n\t"
        :: "r"((&m_proc->context.spsr))
        : "r0"
    );
    sys_enable();
    asm volatile(
        "str lr,[%0]\n\t"
        "str sp,[%1]\n\t"
        :: "r"((&m_proc->context.lr)),"r"((&m_proc->context.sp))
        : "lr","sp"
    );
    irq_enable();
    uint i = 0;
    for(i = 0;i<13;i++) {
        m_proc->context.r[i] = reg[i];
    }
    m_proc->context.pc = reg[13];
    copyproc(&pcb[m_proc->pcb_id],m_proc,RUNABLE);
    //uart_spin_puts("copyproc\r\n");
    struct processor * m_new = schedule();
    //uart_spin_puts("schedule:"); puts_uint((uint)m_new);
    m_proc->pcb_id = m_new->pcb_id;
    copyproc(m_proc,m_new,RUNNING);
    sys_enable();
    asm volatile(
        "mov lr, %0\n\t"
        "mov sp, %1\n\t"
        :: "r"(m_proc->context.lr),"r"(m_proc->context.sp)
        : "lr","sp"
    );
    irq_enable();
    for(i = 0;i<13;i++) {
        //puts_uint(i);
        reg[i] = m_proc->context.r[i];
    }
    reg[13] = m_proc->context.pc;
    invalidate_TLB();
    asm volatile(
        "isb\n\t"
        "mov r0, %0\n\t"
        "mcr p15,0,r0,c2,c0,0\n\t"
        "isb\n\t"
        ::"r"(m_proc->ttb_addr)
        : "r0"
    );
    //irq_enable();
    asm volatile(
        "msr spsr, %0\n\t"
        :: "r"(m_proc->context.spsr)
    );
    //uart_spin_puts("schedule.\r\n");
    //puts_uint(m_proc->context.pc);
    //puts_uint(proc[getCPUId()].state);

}

void reset_schedule(uint * reg)
{
    struct processor * m_proc = &proc[getCPUId()] ;
    m_proc->state = UNUSE;
    //uart_spin_puts("CPU:"); puts_uint(getCPUId());
    struct processor * m_new = schedule();
    //uart_spin_puts("get:"); puts_uint(m_new->pcb_id);
    //puts_uint(m_new->ttb_addr);
    m_proc->pcb_id = m_new->pcb_id;
    copyproc(m_proc,m_new,RUNNING);

    sys_enable();
    asm volatile(
        "mov lr, %0\n\t"
        "mov sp, %1\n\t"
        :: "r"(m_proc->context.lr),"r"(m_proc->context.sp)
        : "lr","sp"
    );
    svc_enable();
    for(uint i = 0;i<13;i++) {
        reg[i] = m_proc->context.r[i];
    }
    reg[13] = m_proc->context.pc;

    invalidate_TLB();
    asm volatile(
        "isb\n\t"
        "mov r0, %0\n\t"
        "mcr p15,0,r0,c2,c0,0\n\t"
        "isb\n\t"
        :: "r"(m_proc->ttb_addr)
        : "r0"
    );
    //invalidate_TLB();
    //puts_uint(m_proc->context.sp);
    //puts_uint(m_proc->context.pc);
    //puts_uint(m_proc->context.spsr);

    /*
    uart_spin_puts("TTB changed.\r\n");
    puts_uint(m_proc->context.pc);
    for(uint i =0;i<30;i++) {
        puts_uint(in32(m_proc->context.pc + 4*i));
    }

    for(uint i= 0;i<13;i++) {
        puts_uint(reg[i]);
    }
    */
    asm volatile(
        "msr spsr, %0\n\t"
        :: "r"(m_proc->context.spsr)
    );
}

#endif

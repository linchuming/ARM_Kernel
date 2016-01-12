/*
    process.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _PROCESS_H
#define _PROCESS_H

#include "kernel.h"

#define UNUSE 0
#define RUNABLE 1
#define RUNNING 2
#define EXIT    3

#define CPU_NUM 2
#define MAX_NUM_PROCESS 128

struct proc_context {
    uint r[13]; //r0-r12
    uint sp,lr,spsr,pc;
};

struct processor {
    uint state;
    uint ttb_addr;
    uint pcb_id;
    uint pid;
    char name[24];
    struct proc_context context;
};

static struct processor proc[CPU_NUM];
static struct processor pcb[MAX_NUM_PROCESS];
static uint pid_num = 1000;
uint getCPUId();

uint usr_cpsr;

void proc_init()
{
    uint id = getCPUId();
    proc[id].state = UNUSE;
}

void pcb_init()
{
    uint i;
    for(i=0; i<MAX_NUM_PROCESS; i++) {
        pcb[i].state = UNUSE;
        pcb[i].pcb_id = i;
    }
    asm volatile(
        "mrs r0, cpsr\n\t"
        "str r0, [%0]\n\t"
        :: "r"(&usr_cpsr)
        : "r0"
    );
    usr_cpsr = usr_cpsr & 0xFFFFFFF0; //get the usr mode cpsr
    pid_num = 1000;
}

void copyproc(struct processor * pnew,struct processor * pold,uint state)
{
    /*
    if(getCPUId()==1) {
        uart_spin_puts("copyproc");
        puts_uint((uint)pnew);
        puts_uint((uint)pold);
    }
    */
    pnew->pid = pold->pid;
    pnew->ttb_addr = pold->ttb_addr;
    pnew->context.sp = pold->context.sp;
    pnew->context.lr = pold->context.lr;
    pnew->context.pc = pold->context.pc;
    pnew->context.spsr = pold->context.spsr;
    for(uint i=0;i<13;i++) {
        pnew->context.r[i] = pold->context.r[i];
    }
    pnew->state = state;
}

int findEmptyPcb()
{
    for(uint i=0;i<MAX_NUM_PROCESS;i++) {
        if(pcb[i].state == UNUSE) return i;
    }
    return -1;
}

uint getCPUId()
{
    if(in32(0xF8F00104)==0xF0) {
        return 0;
    } else {
        return 1;
    }
}

#endif

/*
    fork.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _FORK_H
#define _FORK_H

#include "kernel.h"
#include "process.h"
#include "schedule.h"
#include "memory.h"
#include "pool.h"
#include "l2_page.h"

void _fork(uint* reg,uint* tmp) //only copy 1 page text and 1 page stack
{
    //uint text_page_num = 1;
    uint start_addr  = 0x400000;
    uint end_sp = KERN_BASE - PAGESIZE;
    uint i;
    uint cpu_id = getCPUId();
    int pcb_id = findEmptyPcb();
    char * ttb = new_ttb();
    pid_num++;
    pcb[pcb_id].pid = pid_num;
    pcb[pcb_id].ttb_addr = (uint)ttb - KERN_BASE;
    for(i=1;i<13;i++) {
        pcb[pcb_id].context.r[i] = reg[i];
    }
    pcb[pcb_id].context.lr = tmp[0];
    pcb[pcb_id].context.sp = tmp[1];
    //uart_spin_puts("sp:");puts_uint(tmp[1]);
    pcb[pcb_id].context.pc = reg[13];
    pcb[pcb_id].context.spsr = proc[cpu_id].context.spsr;
    pcb[pcb_id].context.r[0] = 0;
    reg[0] = pid_num;

    struct mem_list * list = (struct mem_list*)kalloc(1);
    struct mem_list * p = list;
    char * addr = kalloc(1);
    memcpy(addr,(char*)start_addr,PAGESIZE);
    p->addr = (uint)addr - KERN_BASE;
    p = (struct mem_list *)((uint)p + NEXT_LIST);
    p->addr = 0;

    write_process_page(ttb,start_addr,list);
    p = list;
    addr = kalloc(1);
    memcpy(addr,(char*)end_sp,PAGESIZE);
    p->addr = (uint)addr - KERN_BASE;
    p = (struct mem_list *)((uint)p + NEXT_LIST);
    p->addr = 0;
    
    write_process_page(ttb,end_sp,list);
    kfree((char*)list,1);

    pcb[pcb_id].state = RUNABLE;

}

#endif

/*
    load_init.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _LOAD_INIT_H
#define _LOAD_INIT_H

#include "kernel.h"
#include "memory.h"
#include "pool.h"
#include "l2_page.h"
#include "process.h"

static char * buf;
void load_init()
{
    buf = kalloc(1);
    //puts_uint((uint)buf);
    sd_dma_spin_read((uint)buf - KERN_BASE, 1, 0);
    //puts_uint(in32((uint)buf));
    char * addr = (char*)(buf+0x1D6);
    uint part2_offset = addr[0] + (addr[1]<<8) + (addr[2]<<16) + (addr[3]<<24);
    //puts_uint(part2_offset);
    sd_dma_spin_read((uint)buf - KERN_BASE,1,part2_offset+10000);
    uart_spin_puts("init:");
    //puts_uint(in32((uint)buf));
}

void create_init()
{
    uart_spin_puts("create init process.\r\n");
    int pcb_id = findEmptyPcb();
    char * ttb = new_ttb();
    pcb[pcb_id].ttb_addr = (uint)ttb - KERN_BASE;
    pcb[pcb_id].context.pc = 0x400000;
    pcb[pcb_id].context.sp = 0x80000000;
    pcb[pcb_id].context.spsr = usr_cpsr;
    pcb[pcb_id].pid = 1000;
    pcb[pcb_id].state = RUNABLE;

    struct mem_list * list = (struct mem_list*)kalloc(1);
    struct mem_list * p = list;
    char * addr = kalloc(1);
    memcpy(addr,buf,PAGESIZE);
    p->addr = (uint)addr - KERN_BASE;
    p = (struct mem_list *)((uint)p + NEXT_LIST);
    p->addr = 0;
    write_process_page(ttb,0x400000,list);
    kfree((char*)list,1);
    addr = kalloc(1);
    list = (struct mem_list*)kalloc(1);
    p = list;
    p->addr = (uint)addr - KERN_BASE;
    //puts_uint(p->addr);
    p = (struct mem_list *)((uint)p + NEXT_LIST);
    p->addr = 0;
    write_process_page(ttb,0x80000000-PAGESIZE,list);
    kfree((char*)list,1);
    uart_spin_puts("create init process success.\r\n");

}

#endif

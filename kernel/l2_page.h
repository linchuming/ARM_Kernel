/*
	l2_page.h
	Author: cmlin
	Email: 13307130255@fudan.edu.cn
*/
#ifndef _L2PAGE_H
#define _L2PAGE_H

#include "kernel.h"
#include "mmu.h"
#include "memory.h"
#include "pool.h"

#define NEXT_LIST 4

struct mem_list {
    uint addr;
};
// if addr == 0 , means the end of mem_list

char* new_ttb()
{
    char * ttb =  kalloc_align(4);

    memset(ttb,0,4*4096);
    char* kernel_ttb = (char*)(KERN_TTB+KERN_BASE);

    memcpy(ttb+2*4096,kernel_ttb+2*4096,2*4096);

    return ttb;
}

int write_process_page(char* ttb_addr,uint start_va,struct mem_list* list)
{
    struct mem_list * p = list;
    uint va = start_va;
    uint counter = 0;
    while(p->addr) {
        char * l1_addr = (char*) ((uint)ttb_addr + ((va>>20)<<2));

        if(in32((uint)l1_addr) == 0) {
            char* new_l2 = new_kb();
            if(new_l2 == NULL) {
                uart_spin_puts("new kb failed.\r\n");
                return 0;
            }
            memset(new_l2,0,KBSIZE);
            out32((uint)l1_addr,((uint)new_l2 - KERN_BASE) | TTB_DOMAIN(DOMAIN_USER) | TTB_TYPE_PTE);
        }
        char * l2_addr = (char*)( (in32((uint)l1_addr) & PTE_L2ADDR_MASK) + ( ((va<<12)>>24)<<2) ) ;
        //puts_uint((uint)l2_addr);
        out32((uint)l2_addr + KERN_BASE,p->addr | PTE_SMALL_BUFFERABLE | PTE_TYPE_SMALL);
        va+=PAGESIZE;
        p = (struct mem_list *)((uint)p + NEXT_LIST);
        counter++;
        if(counter == 1024) break;
    }
    return 1;
}

void free_process_memory(char* ttb_addr)
{

    uint ttb = (uint)ttb_addr;
    for(uint i=0; i < 2*PAGESIZE; i+=4) {
        if(in32(ttb+i)) {
            uint l2_addr = (in32(ttb+i) & PTE_L2ADDR_MASK) + KERN_BASE;
            //uart_spin_puts("l2 addr:");
            //puts_uint(l2_addr);
            for(uint j=0; j < KBSIZE; j+=4) {
                if(in32(l2_addr+j)) {
                    uint pa = (in32(l2_addr+j) & PTE_PA_MASK) + KERN_BASE;
                    //puts_uint(pa);
                    kfree( (char*) pa, 1);
                    /*
                    uart_spin_puts("free ok.\r\n");
                    showFreememory();
                    uart_spin_puts("show end.\r\n");
                    */
                }
            }
            free_kb((char*)l2_addr);
        }
    }
    //puts_uint(ttb);
    kfree(ttb_addr,4);
}

#endif

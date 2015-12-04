/*
    mmu.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _MMU_H
#define _MMU_H

#include "kernel.h"
#define TTB_FLAG 0x5E2
#define FRIST_TTB_VAL 0x155E6
#define SP_ADDR 0x20000000
#define SP_TOP 0x1F000000

#define L2CACHE_CONTROL 0xF8F02100
#define SCU_CONTROL 0xF8F00000
void write_page(uint va,uint pa,uint table_addr)
{
    uint t = va >> 20;
    table_addr += (t<<2);
    out32(table_addr,((pa>>20)<<20) + TTB_FLAG);
    /*
    AP = 10;
    domain = 1111;
    1:0 = 10
    */
}

uint section_range = 0x100000;
void remove_lower_address()
{
    for(uint i=0;i<invalid_addr;i+=section_range) {
        uint t = i >> 20;
        out32(table_addr+(t<<2),0);
    }
    invalidate_TLB();
}

void create_first_page()
{
    uint count = 0;
    for(uint i=0;count<4096;i+=section_range) {
        write_page(i,i,table_addr);
        count++;
    }
    for(uint i=0;i<invalid_addr;i+=section_range) {
        write_page(i+KERN_BASE,i,table_addr);
    }

    for(uint i=SP_TOP;i<SP_ADDR;i+=section_range) {
        write_page(i+KERN_BASE,i,table_addr);
    }


    out32(table_addr,FRIST_TTB_VAL);

}
void enable_mmu()
{
    create_first_page();
    /* Set the TTB */
    asm volatile(
        "ldr r1, =table_addr\n\t"
        "ldr r0, [r1]\n\t"
        "mcr p15,0,r0,c2,c0,0\n\t"
    );
    /* Set the DOMAIN */
    asm volatile(
        "ldr r0, =0x55555555\n\t"
        "mcr p15,0,r0,c3,c0,0\n\t"
    );

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

    /*
        Enable data cache, instruction caches, prediction
        Enable data cache, set the c1 bit[2] to 1
        Enable instruction caches, set the c1 bit[12] to 1
        Enable branch prediction, set the c1 bit[11] to 1
    */
    asm volatile(
        "ldr r1, =0x1804\n\t"
        "mrc p15,0,r0,c1,c0,0\n\t"
        "orr r0,r0,r1\n\t"
        "mcr p15,0,r0,c1,c0,0\n\t"
        "isb\n\t"
    );

    /* Enable L2 cache */
    out32(L2CACHE_CONTROL,0X1);

}

#endif


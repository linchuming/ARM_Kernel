/*
    mmu.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _MMU_H
#define _MMU_H

#include "kernel.h"
#define DOMAIN_KERN 1
#define DOMAIN_USER 0
#define DOMAIN_FAIL 15
/*
  level 1 descriptor
*/
#define TTB_TYPE_PTE 0x1
#define TTB_TYPE_SECT 0x2
#define TTB_SECT_BUFFERABLE (1<<2)
#define TTB_SECT_CACHEABLE (1<<3)
#define TTB_SECT_XN (1<<4)
#define TTB_DOMAIN(x) ((x) << 5)
#define TTB_SECT_AP (1<<10)
#define TTB_FLAG (TTB_TYPE_SECT|TTB_SECT_BUFFERABLE|TTB_DOMAIN(DOMAIN_KERN)|TTB_SECT_AP)
/*
  level 2 descriptor
*/
#define PTE_TYPE_SMALL 0x2
#define PTE_TYPE_EXT 0x3
#define PTE_SMALL_BUFFERABLE (1<<2)
#define PTE_SMALL_CAHCEABLE (1<<3)
#define PTE_L2ADDR_MASK 0xFFFFFC00
#define PTE_PA_MASK 0xFFFFF000

#define SP_ADDR 0x20000000
#define SP_TOP 0x1F000000

#define L2CACHE_CONTROL 0xF8F02100
#define SCU_CONTROL 0xF8F00000
void write_page(uint va,uint pa,uint table_addr)
{
    uint t = va >> 20;
    table_addr += (t<<2);
    out32(table_addr,((pa>>20)<<20) | TTB_FLAG);
    /*
    AP[11:10] = 01;
    domain[8:5] = 0001;
    bit[1:0] = 10
    */
}

uint section_range = 0x100000;
void remove_lower_address()
{
    for(uint i=0;i<invalid_addr;i+=section_range) {
        uint t = i >> 20;
        out32(KERN_TTB+(t<<2)+KERN_BASE,TTB_FLAG|TTB_SECT_XN);
    }
    invalidate_TLB();
}

void create_first_page()
{
    uint count = 0;
    for(uint i=0;count<4096;i+=section_range) {
        write_page(i,i,KERN_TTB);
        count++;
    }
    for(uint i=0;i<invalid_addr;i+=section_range) {
        write_page(i+KERN_BASE,i,KERN_TTB);
    }

    for(uint i=SP_TOP;i<SP_ADDR;i+=section_range) {
        write_page(i+KERN_BASE,i,KERN_TTB);
    }

}
void enable_mmu()
{
    create_first_page();
    /* Set the TTB */
    asm volatile(
        "ldr r0, =0x00014000\n\t"
        "mcr p15,0,r0,c2,c0,0\n\t"
    );
    /* Set the DOMAIN */
    asm volatile(
        "ldr r0, =0x7\n\t"
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

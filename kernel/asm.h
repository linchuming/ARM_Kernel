/*
    asm.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _ASM_H
#define _ASM_H

#include "kernel.h"

static inline void invalidate_TLB()
{
    asm volatile(
        "isb\n\t"
        "dsb\n\t"
        "mov r0, #0\n\t"
        /*
        "mcr p15,0,r0,c8,c5,0\n\t"
        "mcr p15,0,r0,c8,c6,0\n\t"
        "mcr p15,0,r0,c8,c7,0\n\t"
        "mcr p15, 0, r0, c7, c5, 6\n\t" //flush BTAC/BTB
        "mcr p15, 0, r0, c7, c10, 4\n\t" //drain write buffer
        */
        "mcr p15, 0, r0, c8, c7, 0\n\t"

        "dsb\n\t"
        "isb\n\t"
        ::: "r0"
    );
}

static inline void update_pc()
{
    asm volatile(
        "mov r0, %0\n\t"
        "add pc, pc, r0\n\t"
        "isb\n\t"
        ::"r"(KERN_BASE)
        :"r0"
    );
}

static inline void update_sp()
{
    asm volatile(
        "mov r0, %0\n\t"
        "add sp, sp, r0\n\t"
        "isb\n\t"
        ::"r"(KERN_BASE)
        :"r0"
    );
}




#endif // _ASM_H

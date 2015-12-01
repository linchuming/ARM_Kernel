/*
    asm.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _ASM_H
#define _ASM_H

void invalidate_TLB()
{
    asm volatile(
        "mov r0, #0\n\t"
        "mcr p15,0,r0,c8,c5,0\n\t"
        "isb\n\t"
        "mcr p15,0,r0,c8,c6,0\n\t"
        "isb\n\t"
        "mcr p15,0,r0,c8,c7,0\n\t"
        "isb\n\t"
    );
}




#endif // _ASM_H

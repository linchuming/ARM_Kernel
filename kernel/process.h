/*
    process.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _PROCESS_H
#define _PROCESS_H

#include "kernel.h"

struct proc_context {
    uint r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11;
    uint sp,pc;
    uint spsr;
};

#endif

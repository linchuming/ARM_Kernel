/*
    ps.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _PS_H
#define _PS_H

#include "kernel.h"
#include "process.h"

void _ps()
{
    uart_spin_puts("NAME\tPID\r\n");
    uint i = 0;
    for(i=0;i<MAX_NUM_PROCESS;i++) {
        if(pcb[i].state==RUNNING||pcb[i].state==RUNABLE) {
            uart_spin_puts(pcb[i].name);
            uart_spin_puts("\t");
            puts_uint(pcb[i].pid);
        }
    }
}

#endif

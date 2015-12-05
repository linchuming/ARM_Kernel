/*
    syscall.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _SYSCALL_H
#define _SYSCALL_H

#include "kernel.h"

/*
    Define the system call interface:
    reg[0] : Function Id
    other: Function Parameter
*/

#define PUTS 0x10

void syscall_handler(uint* reg)
{
    uart_spin_puts("You are in the system call.\r\n");
    switch(reg[0]) {
        case PUTS:
        {
            uint* addr = (uint*)reg[0];
            char* p = (char*)*addr;
            uart_spin_puts(p);
        }
            break;
        default:
            break;
    }
}

#endif // _SYSCALL_H


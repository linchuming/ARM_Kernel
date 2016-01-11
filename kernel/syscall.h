/*
    syscall.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _SYSCALL_H
#define _SYSCALL_H

#include "kernel.h"
#include "fork.h"
#include "getline.h"

/*
    Define the system call interface:
    reg[0] : Function Id
    other: Function Parameter
*/

#define PUTS 0x10
#define FORK 0x20
#define GETLINE 0x30
#define PUTS_UINT 0x40

static uint tmp[10];
static spinlock_t syscall_lock;

void syscall_handler(uint* reg)
{
    //uart_spin_puts("You are in the system call.\r\n");
    //puts_uint(reg[0]);
    //puts_uint(proc[getCPUId()].pid);

    //puts_uint(reg[1]);
    //irq_mask_open();
    switch(reg[0]) {
        case PUTS:
        {
            char* addr = (char*)reg[1];
            uart_spin_puts(addr);
            //uart_spin_puts("\r\n");
            break;
        }
        case FORK:
        {
            spin_lock(&syscall_lock);
            sys_enable();
            asm volatile(
                "str lr, [%0]\n\t"
                "str sp, [%1]\n\t"
                :: "r"(&tmp[0]),"r"(&tmp[1])
            );
            svc_enable();
            _fork(reg,tmp);
            release_lock(&syscall_lock);
            break;
        }
        case GETLINE:
        {
            //irq_mask_close();
            _getline((char*)reg[1]);
            //irq_mask_open();
            break;
        }
        case PUTS_UINT:
        {
            puts_uint(reg[1]);
            break;
        }
        default:
            break;
    }
    //irq_mask_close();
    //svc_enable();
}

#endif // _SYSCALL_H

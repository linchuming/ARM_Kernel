/*
    wait.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _WAIT_H
#define _WAIT_H

#include "kernel.h"
#include "process.h"
#include "l2_page.h"

void _exit(uint * reg)
{
    //uart_spin_puts("exit");
    proc[getCPUId()].state = EXIT;
    reset_schedule(reg);
}

void _wait(uint pid)
{
    uint i;
    //puts_uint(pid);
    for(i = 0;i<MAX_NUM_PROCESS;i++) {
        if(pcb[i].pid == pid) break;
    }
    //puts_uint(i);
    while(pcb[i].state != EXIT) usleep(10);
    free_process_memory((char*)pcb[i].ttb_addr + KERN_BASE);
    //uart_spin_puts("wait over\r\n");

}

#endif

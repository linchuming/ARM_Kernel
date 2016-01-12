/*
    ls.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _LS_H
#define _LS_H

#include "kernel.h"
#include "filesystem.h"

void _ls()
{
    uint i = 0;
    for(i=0;i<file_num;i++) {
        uart_spin_puts(content[i].filename);
        uart_spin_puts(" ");
    }
    uart_spin_puts("\r\n");
}

#endif

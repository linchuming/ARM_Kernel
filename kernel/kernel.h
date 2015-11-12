#ifndef _KERNEL_H
#define _KERNEL_H

#include "device/type.h"
#include "device/io.h"
#include "device/config.h"
#include "device/uart.h"
#include "device/sd-zynq7000.h"
typedef unsigned int uint;


uint KERN_BASE = 0x80000000;
uint table_addr = 0x4000; //first kernel page
uint kernel_addr = 0x200000;
uint firmware_addr = 0x1ff00000;
uint invalid_addr = 0x800000;

void puts_uint(u32 num)
{
    int i;
    const char table[] = "0123456789ABCDEF";
    char buf[11] = "00000000\r\n";
    for (i = 28; i >= 0; i -= 4){
        buf[(28 - i) >> 2] = table[(num >> i) & 0xF];
    }
    uart_spin_puts(buf);
}

#endif

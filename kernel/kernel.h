/*
    kernel.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _KERNEL_H
#define _KERNEL_H

#define NULL (void*)0

#include "device/type.h"
#include "device/io.h"
#include "device/config.h"
#include "device/uart.h"
#include "device/sd-zynq7000.h"

#include "asm.h"

typedef unsigned int uint;


uint KERN_BASE = 0x80000000;
uint table_addr = 0x00014000; //first kernel page
uint kernel_addr = 0x00200000;
uint invalid_addr = 0x00800000;

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

uint ilog2(uint x)
{
    uint p1,p2,p3,p4,m1,m2,m3,m4,m5;
    x = x>>1;
    x = x | (x>>1);
    x = x | (x>>2);
    x = x | (x>>4);
    x = x | (x>>8);
    x = x | (x>>16);
    // 先将x右移一位，从左边第一个1开始后面全部改为1 。（Ex 00001010 -> 00000111）。最后bitcount 。
    p1 = 0x55;
    m1 = (p1<<24) + (p1<<16) + (p1<<8) + p1;
    x = (x & m1) + ((x>>1) & m1);
    p2 = 0x33;
    m2 = (p2<<24) + (p2<<16) + (p2<<8) + p2;
    x = (x & m2) + ((x>>2) & m2);
    p3 = 0x0f;
    m3 = (p3<<24) + (p3<<16) + (p3<<8) + p3;
    x = (x + (x>>4)) & m3;
    p4 = 0xff;
    m4 = (p4<<16) + p4;
    x = (x + (x>>8)) & m4;
    m5 = (p4<<8) + p4;
    return (x+(x>>16)) & m5;
}

#endif

/*
    timer.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _TIMER_H
#define _TIMER_H

#include "kernel.h"

#define TIMER_LOAD      0xF8F00600
#define TIMER_COUNTER   0xF8F00604
#define TIMER_CONTROL   0xF8F00608
#define TIMER_ISR       0xF8F0060C

#define TIMER_FREQ      333

void timer_init(uint ms)
{
    out32(TIMER_LOAD,ms*TIMER_FREQ*1000-1);
    out32(TIMER_COUNTER,ms*TIMER_FREQ*1000-1);
    asm volatile("isb");
    out32(TIMER_CONTROL,0x2);
}

void timer_start()
{
    out32(TIMER_CONTROL,0x7);
}

void timer_close()
{
    out32(TIMER_CONTROL,0x2);
}



#endif

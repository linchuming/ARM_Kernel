/*
    getline.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _GETLINE_H
#define _GETLINE_H

#include "kernel.h"

#define RES_STR 13

void _getline(char * str)
{
    int count = 0;
    char c;
    char buf[128];
    buf[0] = '\0';
    //puts_uint((uint)str);
    while(1)
    {
        c = uart_spin_getbyte();
        //puts_uint((uint)str);
        if(c=='\b') {
            if(count==0) continue;
            uart_spin_putbyte('\b');
            uart_spin_putbyte(' ');
            uart_spin_putbyte('\b');
            count--;
            continue;
        }
        if(c==RES_STR) {
            //str[count] = '\0';
            buf[count] =  '\0';
            uart_spin_putbyte('\r');
            uart_spin_putbyte('\n');
            //uart_spin_puts(str);
            //puts_uint(count);
            break;
        } else {
            if(c>=33 && c<=126) {
                buf[count++] = c;
            }
        }
        uart_spin_putbyte(c);
    }
    strcpy(str,buf);
}

#endif

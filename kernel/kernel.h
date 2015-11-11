#ifndef _KERNEL_H
#define _KERNEL_H
typedef unsigned int uint;

int (*uart_spin_puts)(const char *) = (void *)0x1ff0000c;
void (*puts_uint)(uint) = (void*)0x1ff00010;
int (*sd_dma_spin_read)(uint,uint,uint) = (void*)0x1ff00014;

uint KERN_BASE = 0x80000000;
uint table_addr = 0x4000; //first kernel page
uint kernel_addr = 0x200000;
uint firmware_addr = 0x1ff00000;
uint invalid_addr = 0x800000;
#endif

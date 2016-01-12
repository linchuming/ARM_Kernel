/*
    filesystem.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include "kernel.h"
struct file_index {
    char filename[128];
    uint start_sector;
    uint end_sector;
};
#define FILE_NUM     10
static struct file_index content[FILE_NUM];
static uint file_num;
static uint part2_offset;


void file_system_init()
{
    file_num = 3;
    strcpy(content[0].filename,"console");
    content[0].start_sector = 12000;
    content[0].end_sector = 12099;
    strcpy(content[1].filename,"ls");
    content[1].start_sector = 12100;
    content[1].end_sector = 12199;
    strcpy(content[2].filename,"ps");
    content[2].start_sector = 12200;
    content[2].end_sector = 12299;
    char* buf = kalloc(1);
    //puts_uint((uint)buf);
    sd_dma_spin_read((uint)buf - KERN_BASE, 1, 0);
    //puts_uint(in32((uint)buf));
    char * addr = (char*)(buf+0x1D6);
    part2_offset = addr[0] + (addr[1]<<8) + (addr[2]<<16) + (addr[3]<<24);
    kfree(buf,1);
}

#endif

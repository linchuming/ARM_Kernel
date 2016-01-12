/*
    exec.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#ifndef _EXEC_H
#define _EXEC_H

#include "kernel.h"
#include "memory.h"
#include "schedule.h"
#include "filesystem.h"

void _exec(uint*reg,char* str)
{
    uint elf_start_sector = 0,elf_end_sector = 0;
    uint i;
    for(i=0;i<file_num;i++) {
        if(strcmp(content[i].filename,str) == 0) {
            elf_start_sector = content[i].start_sector;
            elf_end_sector = content[i].end_sector;
            break;
        }
    }
    if(elf_start_sector == 0) {
        reg[0] = 1;
        return;
    }
    uint cpuid = getCPUId();
    strcpy(pcb[proc[cpuid].pcb_id].name,str);
    //uart_spin_puts(str);
    uint sector_size = elf_end_sector - elf_start_sector;
    uint buf_size = ((sector_size * 512) >> 12) + 1;
    //puts_uint(buf_size);
    char* buf_addr = kalloc(buf_size);
    //puts_uint((uint)buf_addr);
    for(i=0;i<elf_end_sector-elf_start_sector;i++) {
        sd_dma_spin_read((uint)buf_addr + i*512 - KERN_BASE,1,part2_offset+elf_start_sector+i);
    }
    elf32hdr_t * hd = (elf32hdr_t *)buf_addr;
    reg[13] = hd->e_entry;
    //puts_uint(hd->e_entry);
    uint ph_offset = hd->e_phoff;
    elf32_phdr_t * ph = (elf32_phdr_t *)((uint)buf_addr + ph_offset);
    memcpy((char*)ph->p_vaddr,buf_addr+ph->p_offset,ph->p_memsz);

    //puts_uint(ph->p_memsz);
    kfree(buf_addr,buf_size);

}

#endif

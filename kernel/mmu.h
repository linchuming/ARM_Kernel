#include "kernel.h"
void write_page(uint va,uint pa,uint table_addr)
{
    uint t = va >> 20;
    table_addr += (t<<2);
    *(uint*)table_addr = ((pa>>20)<<20) + 0x5E2;
    /*
    AP = 10;
    domain = 1111;
    1:0 = 10
    */
}
uint section_range = 0x100000;
void create_first_page()
{
    uint count = 0;
    for(uint i=0;count<4096;i+=section_range) {
        write_page(i,i,table_addr);
        count++;
    }
    for(uint i=0;i<invalid_addr;i+=section_range) {
        write_page(i+KERN_BASE,i,table_addr);
    }
    write_page(firmware_addr+KERN_BASE,firmware_addr,table_addr);
    *(uint*)table_addr = 0x155E6;

}
void enable_mmu()
{
    create_first_page();

    asm(
        "ldr r1, =table_addr\n\t"
        "ldr r0, [r1]\n\t"
        "mcr p15,0,r0,c2,c0,0\n\t" //set the TTB
    );

    asm(
        "ldr r0, =0x55555555\n\t"
        "mcr p15,0,r0,c3,c0,0\n\t" //set the DOMAIN
    );

    asm(
        "mov r0, #0\n\t"
        "mcr p15,0,r0,c8,c7,0\n\t" //enable the TLB
    );

    asm(
        "mrc p15,0,r0,c1,c0,0\n\t"
        "orr r0,r0,#0x1\n\t"
        "mcr p15,0,r0,c1,c0,0\n\t" //enable MMU
    );

}

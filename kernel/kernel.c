typedef unsigned int uint;

int (*uart_spin_puts)(const char *) = (void *)0x1ff0000c;

uint KERN_BASE = 0x80000000;
uint table_addr = 0x4000;
uint kernel_addr = 0x200000;
uint device_addr = 0x1ff00000;

void write_page(uint va,uint pa,uint table_addr)
{
    uint t = va >> 20;
    table_addr += (t<<2);
    *(uint*)table_addr = ((pa>>20)<<20) + 0xDE2;
}
void enable_mmu()
{
    uart_spin_puts("begin to create the first-level page.\r\n");
    //write_page(device_addr + KERN_BASE,device_addr,table_addr);
    //write_page(kernel_addr+ KERN_BASE,kernel_addr,table_addr);
    uint count = 0;
    for(uint i=0;count<4096;i+=0x100000) {
        write_page(i,i,table_addr);
        count++;
    }
    *(uint*)table_addr = 0x15DE6;
    uart_spin_puts("write page success and ready to enable mmu.\r\n");
    //uart_spin_puts = (void *)(0x1ff0000c + KERN_BASE);

    /*
    asm(
        "LDR r0,0x4000\n\t"
        "MCR p15,0,r0,c2,c0,0\n\t"
    );
    */
    asm("ldr r0, =0x4000\n\t"
        "mcr p15,0,r0,c2,c0,0\n\t"
    );
    //asm("mcr p15,0,r0,c2,c0,0");

    uart_spin_puts("change c2 register.\r\n");

    asm(
        "ldr r0, =0x55555555\n\t"
        "mcr p15,0,r0,c3,c0,0\n\t"
    );

    asm(
        "mrc p15,0,r0,c1,c0,0\n\t"
        "orr r0,r0,#0x1\n\t"
        "mcr p15,0,r0,c1,c0,0\n\t"
    );
    uart_spin_puts("enable mmu success.\r\n");
}
void main()
{
    uart_spin_puts("Welcome to the kernel on the Arm!\r\n");
    //uart_spin_puts("Waiting for the next programming!\r\n")
    enable_mmu();

}

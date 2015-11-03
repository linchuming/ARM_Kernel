typedef unsigned int uint;
void start()
{
    int (*uart_spin_puts)(const char *) = (void *)0x1ff0000c;
    void (*puts_uint)(uint) = (void*)0x1ff00010;
    int (*sd_dma_spin_read)(uint,uint,uint) = (void*)0x1ff00014;
    //The function from the firmware.bin

    uint * part2_offset = (uint*)0x1001D6;
    //unsigned int part2_offset = addr[0] + (addr[1]<<8) + (addr[2]<<16) + (addr[3]<<24);
    char * part2 = (char*)0x110000;

    sd_dma_spin_read((uint)part2,1,*part2_offset); //read ELF header
    uint entry_addr = *(uint*)(part2+24);
    //puts_uint(entry_addr);
    uint ph_offset = *(uint*)(part2+28);
    uint _size = *(uint*)(part2+32);
    uint len = (_size >> 9) + 1;

    for(int i = 1;i<len;i++) {
        sd_dma_spin_read((uint)part2 + (i << 9),1,(*part2_offset) + i);
        //puts_uint((uint)part2 + (i << 9));
    } //read ELF file to memory

    uint p_offset = *(uint*)(part2+ph_offset+4);
    uint memsz = *(uint*)(part2+ph_offset+20);
    puts_uint(memsz);
    char * p_data = part2 + p_offset;
    char * entry_data = (char*)entry_addr;
    for(int i = 0;i<memsz;i++) {
        entry_data[i] = p_data[i];
        //puts_uint(entry_data[i]);
    } //copy the program code to memory

    void (*entry)() = (void*)(entry_addr);
    entry();

}

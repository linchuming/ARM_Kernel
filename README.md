# ARM_Kernel
Simple ARM_Kernel

基于ARM架构的操作系统

## 代码使用环境
该OS运行在基于ARMv7a的ZYNQ7000的开发板上

请先用gcc编译出具有ARMv7a的交叉编译器

## OS实现的功能
该OS只是为了了解一个简单的底层OS的实现原理

目前实现的功能有:

1. Memory Management Unit(MMU)

2. Memory allocation(first fit algorithm)

3. Two level page table

4. Interrupt & Vector table (can handle IRQ&SWI Interrupt)

5. Timer Interrupt

6. Start CPU1 & Spinlock

7. Processes schedule(round-robin algorithm)

8. init process & console

9. Simple file management

10. Some system calls such as fork(),exec(),puts(),getline(),ls(),ps(),wait()

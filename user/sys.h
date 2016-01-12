/*
    sys.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _SYS_H
#define _SYS_H

#define PUTS        0x10
#define FORK        0x20
#define GETLINE     0x30
#define PUTS_UINT   0x40
#define EXEC        0x50
#define LS          0x60
#define PS          0x70
#define WAIT        0x80

void puts(char * str)
{
    asm volatile(
        "mov r0, %0\n\t"
        "mov r1, %1\n\t"
        "swi 0x100\n\t"
        :: "r"(PUTS),"r"(str)
        : "r0","r1"
    );
}

void puts_uint(unsigned int num)
{
    asm volatile(
        "mov r0, %0\n\t"
        "mov r1, %1\n\t"
        "swi 0x100\n\t"
        :: "r"(PUTS_UINT),"r"(num)
        : "r0","r1"
    );
}

int fork()
{
    int res;
    asm volatile(
        "mov r0, %0\n\t"
        "swi 0x100\n\t"
        "isb\n\t"
        :: "r"(FORK)
        : "r0"
    );
    asm volatile(
        "mov %0, r0\n\t"
        :"=&r"(res):
        : "r0"
    );
    return res;
}

void getline(char * str)
{
    asm volatile(
        "mov r0, %0\n\t"
        "mov r1, %1\n\t"
        "swi 0x100\n\t"
        "isb\n\t"
        :: "r"(GETLINE),"r"(str)
        : "r0","r1"
    );
}

int exec(char * str)
{
    int res;
    asm volatile(
        "mov r0, %0\n\t"
        "mov r1, %1\n\t"
        "swi 0x100\n\t"
        "isb\n\t"
        :: "r"(EXEC),"r"(str)
        : "r0","r1"
    );
    asm volatile(
        "mov %0, r0\n\t"
        :"=&r"(res):
        : "r0"
    );
    return res;
}

void ls()
{
    asm volatile(
        "mov r0, %0\n\t"
        "swi 0x100\n\t"
        "isb\n\t"
        :: "r"(LS)
        : "r0"
    );
}

void ps()
{
    asm volatile(
        "mov r0, %0\n\t"
        "swi 0x100\n\t"
        "isb\n\t"
        :: "r"(PS)
        : "r0"
    );
}

void wait(unsigned int pid)
{
    asm volatile(
        "mov r0, %0\n\t"
        "mov r1, %1\n\t"
        "swi 0x100\n\t"
        :: "r"(WAIT),"r"(pid)
        : "r0","r1"
    );
}

#endif

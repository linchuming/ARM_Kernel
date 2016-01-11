/*
    spinlock.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _SPINLOCK_H
#define _SPINLOCK_H

typedef struct{
    volatile unsigned int lock;
} spinlock_t;

static inline void spinlock_init(spinlock_t * lock)
{
    lock->lock = 0;
}

static void spin_lock(spinlock_t * lock)
{
    unsigned int tmp;
    asm volatile(
        "1: ldrex %0,[%1]\n\t"
        "teq %0,#0\n\t"
        "strexeq %0, %2,[%1]\n\t"
        "teqeq %0 ,#0\n\t"
        "bne 1b\n\t"
        : "=&r"(tmp)
        : "r"(&lock->lock),"r"(1)
        : "cc"
    );
}

static inline void release_lock(spinlock_t * lock)
{
    lock->lock = 0;
}

#endif

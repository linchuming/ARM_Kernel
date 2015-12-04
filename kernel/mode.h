/*;d
    mode.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _MODE_H
#define _MODE_H

#define IRQ_vector 0x18
#define ICCICR 0xF8F00100
#define ICDSGIR 0xF8F01F00
#include "kernel.h"

static inline void usr_enable()
{
    /* user mode cpsr[4:0] = 10000 */
    asm volatile(
        "ldr r1, =0xFFFFFFF0\n\t"
        "mrs r0, cpsr\n\t"
        "and r0, r0, r1\n\t"
        "msr cpsr, r0\n\t"
        "isb\n\t"
        ::: "r0","r1"
    );
}

static inline void svc_enable()
{
    /* user mode cpsr[4:0] = 10011 */
    asm volatile(
        "ldr r1, =0xFFFFFFF0\n\t"
        "mrs r0, cpsr\n\t"
        "and r0, r0, r1\n\t"
        "orr r0, r0, #3\n\t"
        "msr cpsr, r0\n\t"
        "isb\n\t"
        ::: "r0","r1"
    );
}

static inline void irq_mask_open()
{
	asm volatile(
		"mrs r0, cpsr\n\t"
		"bic r0, r0, #0x80\n\t"
		"msr cpsr, r0\n\t"
		"isb\n\t"
		::: "r0"
	);
}

static inline void irq_mask_close()
{
	asm volatile(
		"mrs r0, cpsr\n\t"
		"orr r0, r0, #0x80\n\t"
		"msr cpsr, r0\n\t"
		"isb\n\t"
		::: "r0"
	);
}


static inline void irq_enable()
{
    /* IRQ mode cpsr[4:0] = 10010 */
    asm volatile(
        "ldr r1, =0xFFFFFFF0\n\t"
        "mrs r0, cpsr\n\t"
        "and r0, r0, r1\n\t"
        "orr r0, r0, #2\n\t"
        "msr cpsr, r0\n\t"
        "isb\n\t"
        ::: "r0","r1"
    );
}

static inline void iccicr_enable()
{
    out32(ICCICR,0x1);
}

static inline void iccicr_disable()
{
    out32(ICCICR,0x0);
}

#endif // _MODE_H



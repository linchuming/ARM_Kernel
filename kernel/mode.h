/*;d
    mode.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _MODE_H
#define _MODE_H

#include "kernel.h"


static inline void usr_enable()
{
    /* user mode cpsr[4:0] = 10000 */
    asm volatile(
        "ldr r1, =0xFFFFFFF0\n\t"
        "mrs r0, cpsr\n\t"
        "and r0, r0, r1\n\t"
        "msr cpsr, r0\n\t"
        ::: "r0","r1"
    );
}

static inline void svc_enable()
{
    /* user mode cpsr[4:0] = 10011 */

    asm volatile(
        "isb\n\t"
        "ldr r1, =0xFFFFFFF0\n\t"
        "mrs r0, cpsr\n\t"
        "and r0, r0, r1\n\t"
        "orr r0, r0, #3\n\t"
        "msr cpsr, r0\n\t"
        ::: "r0","r1"
    );
    /*
    asm volatile(
        "msr cpsr_c, #0xd3\n\t"
        "isb\n\t"
    );
    */
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
        "isb\n\t"
        "ldr r1, =0xFFFFFFF0\n\t"
        "mrs r0, cpsr\n\t"
        "and r0, r0, r1\n\t"
        "orr r0, r0, #2\n\t"
        "msr cpsr, r0\n\t"
        ::: "r0","r1"
    );
    /*
    asm volatile(
        "msr cpsr_c, #0xd2\n\t"
        "isb\n\t"
    );
    */
}

static inline void sys_enable()
{

    asm volatile(
        "isb\n\t"
        "mov r0, #0xF\n\t"
    	"mrs r1, cpsr\n\t"
    	"orr r1, r1, r0\n\t"
    	"msr cpsr, r1\n\t"
        ::: "r0","r1"
    );

    /*
    asm volatile(
        "msr cpsr_c, #0xdf\n\t"
        "isb\n\t"
    );
    */

}


#endif // _MODE_H

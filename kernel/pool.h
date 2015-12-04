/*
	pool.h
	Author: cmlin
	Email: 13307130255@fudan.edu.cn
 */
#ifndef _POOL_H
#define _POOL_H

#include "kernel.h"
#include "memory.h"
/*
    We define a slap size is 64Bytes.
*/
#define SLABSIZE 64

struct slab {
    struct slab* next;
};

char* pool_addr = NULL;
uint p_num = 0;

struct slab* pool_header;
uint max_num = 0;

void init_pool(uint _num)
{
    pool_addr = kalloc(_num);
    p_num = _num;

    pool_header = (struct slab*)pool_addr;
    max_num = _num << 6; // (_num << 12) >> (ilog2(SLABSIZE))

    struct slab* p = pool_header;
    for(uint i=0;i<max_num-1;i++) {
        p->next = (struct slab*) ((int)p + SLABSIZE);
        p = p->next;
    }
    p->next = NULL;

}

void free_pool()
{
    kfree(pool_addr,p_num);
}

char* new_slab()
{
    if(pool_header==NULL) return NULL;

    struct slab* res = pool_header;
    pool_header = pool_header->next;
    return (char*)res;
}

void free_slab(char* addr)
{
    struct slab* p = (struct slab*)addr;
    if(pool_header==NULL||p < pool_header) {
        p->next = pool_header;
        pool_header = p;
    } else {
        struct slab* q = pool_header;
        while(p > q->next && q->next!=NULL) {
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
    }
}




#endif // _POOL_H

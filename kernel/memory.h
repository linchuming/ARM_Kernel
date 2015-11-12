/*
    memory.h
    Author: cmlin
*/

#ifndef _MEMORY_H
#define _MEMORY_H
#include "kernel.h"

#define START_ADDR  0x00800000
#define END_ADDR  0x1FF00000
#define _Ksize  1024

struct run {
    uint size;
    struct run * next;
};

struct run * free_head = NULL;

void mem_init()
{
    free_head = (struct run*)START_ADDR;
    free_head->size = END_ADDR - START_ADDR;
    free_head->next = NULL;
}

/*
    The memory calloc unit is 1KB
    The count means you want the number of 1KB
*/
char * kcalloc(uint count)
{
    if(count == 0) return NULL;
    uint size = count * _Ksize;
    char * res = NULL;
    struct run * r = free_head;
    struct run * pre;

    while(r) {
        if(r->size < size) {
            pre = r;
            r = r->next;
        } else if(r->size > size) {
            res = (char*)r;
            uint n_size = r->size - size;
            uint addr = (uint)r + size;
            struct run * n = (void*)addr;
            n->size = n_size;
            n->next = r->next;
            if(r==free_head) {
                free_head = n;
            } else {
                pre->next = n;
            }
            break;
        } else {
            res = (char*)r;
            if(r==free_head) {
                free_head = r->next;
            } else {
                pre->next = r->next;
            }
            break;
        }
    }
    return res;
}

#endif // _MEMORY_H


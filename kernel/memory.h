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
    char * kalloc(uint)
    The memory calloc unit is 1KB
    The count means you want the number of 1KB
*/
char * kalloc(uint count)
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

/*
    int kfree(char*,uint)
*/
int kfree(char * addr,uint count)
{
    if(count==0) return -1;
    struct run * r = free_head;
    uint size = count * _Ksize;
    struct run * n =  (void*)addr;
    n->size = size;
    if(n < free_head) {
        n->next = free_head;
        if(n + n->size >= n->next) {
            n->size = n->next->size + (uint)n->next - (uint)n;
            n->next = n->next->next;
        }
        free_head = n;
    } else {
        struct run * pre = NULL;
        while(r < n && r!=NULL) {
            pre = r;
            r = r->next;
        }
        n->next = r;
        if(r!=NULL && n+n->size >= r) {
            n->size = n->next->size + (uint)n->next - (uint)n;
            n->next = n->next->next;
        }

        if(pre + pre->size == n) {
            pre->next = n->next;
            pre->size += n->size;
        } else {
            pre->next = n;
        }
    }
    return 0;
}

/*
    char* kalloc_align(uint)
*/
char * kalloc_align(uint count)
{
    uint n = (count<<1)-1;
    char * addr = kalloc(n);
    if(addr==NULL) return addr;
    uint i = 0;
    while((uint) (addr+i*_Ksize) - ((uint) (addr+i*_Ksize) >>10) ) i++;
    if(i) {
        kfree(addr,i);
    }
    if(i+count<n) {
        char * paddr =  addr + (i+count) * _Ksize;
        kfree(paddr,n-count-i);
    }

    return addr+i*_Ksize;
}

#endif // _MEMORY_H


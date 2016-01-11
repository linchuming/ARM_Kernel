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
    The pool can alloc SLABSIZE Bytes and KBSIZE Bytes memory.
*/
#define SLABSIZE 128
#define KBSIZE 1024
#define PAGESIZE 4096

struct slab {
    struct slab* next;
};

struct pkb {
    struct pkb* next;
};
static uint pkb_num = 0;
static uint slab_num = 0;
static spinlock_t pool_lock;

static struct pkb* kb_header;
static struct slab* slab_header;

/*
    slab(64Bytes) memory allocation
*/

int slab_init()
{
    char* new_page = kalloc(1);
    if(new_page == NULL) return 0;
    slab_header = NULL;
    struct slab* pre;
    for(uint i = 0; i < PAGESIZE; i+= SLABSIZE) {
        pre = slab_header;
        slab_header = (struct slab*)((uint)new_page+i);
        slab_header->next = pre;
        slab_num++;
    }
    return 1;
}

char* new_slab()
{
    if(slab_num==0) {
        if(!slab_init()) return NULL;
    }
    char* res = (char*)slab_header;
    slab_header = slab_header->next;
    slab_num--;
    return res;
}

void free_slab(char* addr)
{
    struct slab* pre;
    pre = slab_header;
    slab_header = (struct slab*)addr;
    slab_header->next = pre;
    slab_num++;
}
/*
    1KB memory allocation
*/

int pkb_init()
{
    char* new_page = kalloc(1);
    if(new_page == NULL) return 0;
    kb_header = NULL;
    struct pkb* pre;
    for(uint i = 0; i < PAGESIZE; i+= KBSIZE) {
        pre = kb_header;
        kb_header = (struct pkb*)((uint)new_page+i);
        kb_header->next = pre;
        pkb_num++;
    }
    return 1;
}

char* new_kb()
{
    spin_lock(&pool_lock);
    if(pkb_num==0) {
        if(!pkb_init()) return NULL;
    }
    char* res = (char*)kb_header;
    kb_header = kb_header->next;
    pkb_num--;
    release_lock(&pool_lock);
    return res;
}

void free_kb(char* addr)
{
    spin_lock(&pool_lock);
    struct pkb* pre;
    pre = kb_header;
    kb_header = (struct pkb*)addr;
    kb_header->next = pre;
    pkb_num++;
    release_lock(&pool_lock);
}



#endif // _POOL_H
